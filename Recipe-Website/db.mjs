// db.mjs
import mongoose from 'mongoose';
const { Schema } = mongoose;
import bcrypt from 'bcryptjs';

const userSchema = new Schema({
  username: { type: String, required: true },
  password: { type: String, required: true },
  email: { type: String, required: true },
  recipes: [{ type: Schema.Types.ObjectId, ref: 'Recipes' }]
});

const ingredientSchema = new Schema({
  name: { type: String, required: true },
  quantity: { type: Number, required: true },
  unit: { type: String, required: true },
});

const recipeSchema = new Schema({
  name: { type: String, required: true },
  description: { type: String },
  ingredients: [{ type: Schema.Types.ObjectId, ref: 'Ingredients' }],
  instructions: [{ 
    stepNumber: { type: Number, required: true },
    description: { type: String, required: true }
  }],
  tags: [{ type: String }],
  photos: [{
    dataUrl: { type: String, required: true }
  }],
  comments: [String], // Change here to make comments an array of strings
});

const Users = mongoose.model('Users', userSchema);
const Recipes = mongoose.model('Recipes', recipeSchema);
const Ingredients = mongoose.model('Ingredients', ingredientSchema);

mongoose.connect(process.env.DSN);

export {
  Users,
  Recipes,
  Ingredients
};
