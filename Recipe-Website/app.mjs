import './config.mjs';
import express from 'express';
import session from 'express-session';
import path from 'path';
import { fileURLToPath } from 'url';
import bodyParser from 'body-parser';
import passport from 'passport';
import { Strategy as LocalStrategy } from 'passport-local';
import mongoose from 'mongoose';
import bcrypt from 'bcryptjs';
import flash from 'connect-flash'; 
import multer from 'multer';
import fs from 'fs';


const app = express();
app.use(bodyParser.urlencoded({ extended: true }));

import {Recipes, Users, Ingredients} from './db.mjs'


const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);


app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'hbs');
app.use(express.static('public'));

app.use(session({
  secret: process.env.secret,
  resave: false,
  saveUninitialized: false,
}));
app.use(passport.initialize());
app.use(passport.session());
app.use(flash());

// Define storage for uploaded images using multer
const storage = multer.diskStorage({
  destination: (req, file, cb) => {
    cb(null, 'uploads/'); // Specify the directory where uploaded files will be stored
  },
  filename: (req, file, cb) => {
    // Generate a unique filename for each uploaded file
    cb(null, file.fieldname + '-' + Date.now() + path.extname(file.originalname));
  }
});

const upload = multer({ storage: storage });


// Passport Configuration
passport.use(new LocalStrategy(async (username, password, done) => {

  try {
    const user = await Users.findOne({ username: username });
    if (!user) {
      return done(null, false, { message: 'Incorrect username.' });
    }



    const passwordMatch = await bcrypt.compare(password, user.password);
    if (passwordMatch) {
      return done(null, user);
    } else {
      return done(null, false, { message: 'Incorrect password.' });
    }
  } catch (error) {
    return done(error);
  }
}));

// Add a middleware to serve the uploaded images statically
app.use('/uploads', express.static(path.join(__dirname, 'uploads')));




passport.serializeUser((user, done) => {
  done(null, user.id);
});

passport.deserializeUser(async (id, done) => {
  try {
    const user = await Users.findById(id);
    done(null, user);
  } catch (error) {
    done(error, null);
  }
});



app.get('/signup', (req, res) => {
  res.render('signup', { errorMessage: null });
});

app.post('/signup', async (req, res) => {
  const { username, password, email } = req.body;

  try {
    // Check if the username already exists
    const existingUser = await Users.findOne({ username });

    if (existingUser) {
      // Username already exists, render signup page with error message
      return res.render('signup', { errorMessage: 'Username already exists. Please choose a different username.' });
    }

    const hashedPassword = await bcrypt.hash(password, 10);

    const newUser = await Users.create({
      username,
      password: hashedPassword,
      email,
    });

    // Redirect to the login page after successful sign-up
    res.redirect('/login');
  } catch (error) {
    console.error(error);
    res.status(500).send('Error creating user');
  }
});

app.post('/login',
  passport.authenticate('local', {
    successRedirect: '/',
    failureRedirect: '/login',
    failureFlash: true
  })
);

app.get('/login', (req, res) => {
  res.render('login', { message: req.flash('error') });
});




app.get('/', async (req, res) => {
  try {
    const allRecipes = await Recipes.find().populate('ingredients').exec();
    res.render('home', { recipes: allRecipes });
  } catch (error) {
    console.error(error);
    res.status(500).send('Error fetching recipes');
  }
});

app.get('/myrecipes', isAuthenticated, async (req, res) => {
  try {
    const user = await Users.findById(req.user.id).populate('recipes').exec();
    if (!user) {
      console.error('User not found');
      return res.status(404).send('User not found');
    }
    

    res.render('myrecipes', { recipes: user.recipes , isMyRecipesActive: true, isAddActive: false});
  } catch (error) {
    console.error(error);
    res.status(500).send('Error fetching user recipes');
  }
});



function isAuthenticated(req, res, next) {
  if (req.isAuthenticated()) {
    return next(); // If the user is authenticated, continue with the request handling
  }
  res.redirect('/login'); // If not authenticated, redirect to the login page
}


app.get('/add', isAuthenticated,(req, res) => {
  res.render('add' , { isMyRecipesActive: false, isAddActive: true }); 
});



app.post('/add', isAuthenticated, upload.array('photos', 5), async (req, res) => {
  const { name, description, ingredients, instructions, tags } = req.body;
  const userId = req.user.id; // Get the authenticated user's ID

  // Parse ingredients from the form data
  const parsedIngredients = ingredients.name.map((_, index) => ({
    name: ingredients.name[index],
    quantity: ingredients.quantity[index],
    unit: ingredients.unit[index]
  }));

  try {
    // Create and save Ingredient objects in the database
    const ingredientIds = await Promise.all(parsedIngredients.map(async ingredient => {
      const newIngredient = await Ingredients.create(ingredient);
      return newIngredient._id;
    }));

    // Create and save a new recipe with the created ingredient IDs and photos
    const recipe = await Recipes.create({
      name,
      description,
      ingredients: ingredientIds,
      instructions: Array.isArray(instructions.number)
        ? instructions.number.map((number, index) => ({
            stepNumber: parseInt(number),
            description: instructions.details[index]
          }))
        : [],
      tags: tags.split(',').map(tag => tag.trim()),
      photos: req.files.map(file => ({
        dataUrl: `uploads/${file.filename}` // Adjust the path based on your setup
      })),
    });

    // Associate the recipe with the authenticated user by updating the user's recipes array
    await Users.findByIdAndUpdate(userId, {
      $push: { recipes: recipe._id }
    });

    // Redirect to a success page or any other appropriate page
    res.redirect('/');
  } catch (error) {
    // Handle errors, e.g., render an error page
    console.error(error);
    res.status(500).send('Error adding recipe');
  }
});


app.get('/recipe/:name', async (req, res) => {
  try {
    // Assuming you have a recipe name in the URL parameter
    const recipeName = req.params.name;
    res.locals.baseUrl = `${req.protocol}://${req.get('host')}`;

    // Fetch the recipe details along with populated references (ingredients and instructions)
    const recipe = await Recipes.findOne({ name: recipeName })
      .populate('ingredients')
      .exec();
    
    if (!recipe) {
      // Handle case where the recipe is not found
      return res.status(404).send('Recipe not found');
    }

    // Render the 'recipe' template and pass the recipe data
    res.render('recipe', { recipe });
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});



// Handle comment submission
app.post('/recipe/:name/comment', async (req, res) => {
  try {
      const recipeName = req.params.name;
      const { commentText } = req.body;

      // Find the recipe by name
      const recipe = await Recipes.findOne({ name: recipeName });

      if (!recipe) {
          return res.status(404).send('Recipe not found');
      }

      // Add the new comment to the recipe's comments array
      recipe.comments.push(commentText);

      // Save the updated recipe with the new comment
      await recipe.save();

      // Redirect back to the recipe page
      res.redirect(`/recipe/${recipeName}`);
  } catch (error) {
      console.error(error);
      res.status(500).send('Internal Server Error');
  }
});


app.get('/edit/:name',isAuthenticated, async (req, res) => {
  const recipeName = req.params.name;
  
  try {
    // Find the recipe by name
    const recipe = await Recipes.findOne({ name: recipeName }).populate('ingredients').exec();
    if (!recipe) {
      // Handle the case where the recipe is not found
      return res.status(404).send('Recipe not found');
    }
    // Render the edit form with the found recipe data
    res.render('edit', { recipe: recipe , formattedTags: recipe.tags.join(', ') });
  } catch (err) {
    // Handle any errors that occur during the database operation
    console.error(err);
    res.status(500).send('Internal Server Error');
  }
});

app.post('/edit/:name',isAuthenticated, async (req, res) => {
  const recipeName = req.params.name;
  const { name, description, ingredients, instructions ,tags} = req.body;
  //console.log('Instructions received:', instructions);

  try {
    // Create new Ingredients and Recipe objects based on request data
    const ingredientObjects = [];

    //console.log('Ingredients received:', ingredients);

    for (let i=0;i<ingredients.length;i+=3) {
      let name=ingredients[i];
      let quantity=ingredients[i+1];
      let unit=ingredients[i+2];
      const newIngredient = new Ingredients({ name, quantity, unit });
      const savedIngredient = await newIngredient.save();
      ingredientObjects.push(savedIngredient._id);
    }

    const updatedTags = tags.split(',').map(tag => tag.trim());

    // Find the existing recipe by name and update its properties
    const updatedRecipe = await Recipes.findOneAndUpdate(
      { name: recipeName },
      {
        name,
        description,
        ingredients: ingredientObjects,
        instructions: instructions,
        tags: updatedTags,
      },
      { new: true }
    );

    if (!updatedRecipe) {
      // Handle the case where the recipe is not found
      return res.status(404).send('Recipe not found');
    }

    // Redirect to the recipe details page after successful update
    res.redirect('/');
  } catch (err) {
    // Handle any errors that occur during the database operation
    console.error(err);
    res.status(500).send('Internal Server Error');
  }
});




app.listen(process.env.PORT || 3000);
