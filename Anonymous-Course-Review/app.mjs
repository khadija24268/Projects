
import './config.mjs';
import express from 'express';
import session from 'express-session';
const app = express();
import './db.mjs';

import Review from './db.mjs';


// set up express static
import url from 'url';
import path from 'path';
const __dirname = path.dirname(url.fileURLToPath(import.meta.url));
app.use(express.static(path.join(__dirname, 'public')));

// configure templating to hbs
app.set('view engine', 'hbs');

// body parser (req.body)
app.use(express.urlencoded({ extended: false }));

const sessionOptions = { 
	secret: process.env.secret, 
	saveUninitialized: false, 
	resave: false 
};
app.use(session(sessionOptions));

app.use(function(req, res, next){
  if(!req.session.count){
    req.session.count = 1;
  }
  else{
    req.session.count+=1;
  }
  res.locals.count = req.session.count;
  
  next();
});


app.get('/', (req, res) => {
  const semesterQ = req.query['semester'];
  const yearQ = req.query['year'];
  const profQ = req.query['professor'];

  const query = {};

  if (semesterQ && semesterQ.trim() !== '') {
    query['semester'] = new RegExp(semesterQ, 'i'); // 'i' flag for case-insensitive search
  }

  if (yearQ && yearQ.trim() !== '') {
    query['year'] = yearQ; // Assuming year is not case-sensitive
  }

  if (profQ && profQ.trim() !== '') {
    query['professor'] = new RegExp(profQ, 'i'); // 'i' flag for case-insensitive search
  }

  Review.find(query)
    .then(founddata => {
      res.render('home', {'Review': founddata});
    })
    .catch(err => res.status(500).send('server error', err));
});


app.get('/reviews/add', (req, res) => {
  
  res.render('add');
});

app.post('/reviews/add', (req, res) => {

  
  Review.create(req.body)
    .then(createdReview => {
      if (!req.session.mine){
        req.session.mine = [];
        req.session.mine.push(req.body);
      }
      else{
        req.session.mine.push(req.body);
      }
      console.log('Review created successfully:', createdReview);
      res.redirect('/');
    })
    .catch(error => {
      console.error('Error creating review:', error);
      res.redirect('/');
    });
  

});

app.get('/reviews/mine' , (req,res)=>{
  console.log('START');
  console.log(req.session.mine);
  res.render('myreviews' , {'mine' : req.session.mine});
});

app.listen(process.env.PORT || 3000);
