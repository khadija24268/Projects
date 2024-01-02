// add your code here!
import './config.mjs';
import mongoose from 'mongoose';
// Uncomment following line to debug value of database connectoin string
console.log(process.env.DSN);



// define the data in our collection
const ReviewSchema = new mongoose.Schema({
	courseNumber: {type: String, required: true},
	courseName: {type: String, required: true},
    semester: {type: String, required: true},
    year: {type: Number, required: true},
    professor: {type: String, required: true},
    review: {type: String, required: true}
});

// "register" it so that mongoose knows about it
const Review = mongoose.model('Review', ReviewSchema);

mongoose.connect(process.env.DSN);

export default Review;