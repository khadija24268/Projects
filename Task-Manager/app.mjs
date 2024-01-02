// app.mjs
import express from 'express';
//import {resolve, dirname} from 'path';
import {readFile, readdir} from 'fs';
import {fileURLToPath} from 'url';
import * as path from 'path';
import {Task} from './task.mjs';

//const tasks = [];
const taskList = [];

const app = express();
// set hbs engine
app.set('view engine', 'hbs');


const __dirname = path.dirname(fileURLToPath(import.meta.url));

app.use(express.static(path.join(__dirname, 'public'))); //static files

app.use(express.urlencoded({extended: false})); 

app.use((req, res, next) => {
  // Log the method, path, query, and body of the request
  console.log(`Method: ${req.method}`);
  console.log(`Path: ${req.path}`);
  console.log(`Query: ${JSON.stringify(req.query)}`);
  console.log(`Body: ${JSON.stringify(req.body)}`);
  console.log('---'); // Separator for better readability in the console
  next(); // Pass the request to the next middleware or route handler
});




// TODO: use middleware to serve static files from public
// make sure to calculate the absolute path to the directory
// with import.meta.url

// TODO: use middleware required for reading body

// The global list to store all tasks to be rendered



// The reading path
const readingPath = path.resolve(__dirname, './saved-tasks');
// Read files from the specified directory (readingPath)
readdir(readingPath, (err, files) => {
  if (err) {
    console.log(err); // Handle any error that occurred while reading the directory
  } else {
    files.forEach((file) => { // Iterate over the list of files obtained from the directory
      readFile(path.join(readingPath, file), (err, data) => { // Read the content of the current file
        if (err) {
          console.log(err);
        } else {
          try {

            const task = new Task(JSON.parse(data));  // Parse the content of the file as JSON and create a Task object
            taskList.push(task); // Add the Task object to the taskList array
            //console.log(taskList);
          } catch (error) {
            console.error(`Error parsing JSON in file ${file}:`, error);
          }
        }
      });
    });
  }
});






/**
 * This function sort tasks by the give criteria "sort-by" and "sort-order"
 * @param {Request} req query should contain "sort-by" and "sort-order"
 * @param {[Task]} l the array of tasks to be sorted
 * @return {[Task]} sorted array of tasks by the given criteria
 */
function sortTasks(req, l) {
  if (req.query['sort-by'] && req.query['sort-order']) {
    const newL = [...l];
    const crit = req.query['sort-by'];
    const ord = req.query['sort-order'];
    newL.sort((a, b)=>{
      if (ord === 'asc') {
        switch (crit) {
          case 'due-date': {
            const a1 = new Date(a[crit]);
            const b1 = new Date(b[crit]);
            if (a1 === b1) { return 0; }
            return a1 > b1 ? 1 : -1;
          }
          case 'priority': {
            return a[crit] - b[crit];
          }
          default: {
            return 0;
          }
        }
      } else if (ord === 'desc') {
        switch (crit) {
          case 'due-date': {
            const a1 = new Date(a[crit]);
            const b1 = new Date(b[crit]);
            if (a1 === b1) { return 0; }
            return a1 < b1 ? 1 : -1;
          }
          case 'priority': {
            return b[crit] - a[crit];
          }
          default: {
            return 0;
          }
        }
      } else {
        return [];
      }
    });
    return newL;
  } else {
    return l;
  }
}

/**
 * This function sort tasks by whether they are pinned or not
 * @param {[Task]} l the array of tasks to be sorted
 * @return {[Task]} sorted array of tasks, with pinned tasks first
 */
function pinnedTasks(l) {
  return [...l].sort((a, b)=>b.pinned-a.pinned);
}


app.get('/', function(req, res){
  let task1 = [...taskList];
  const titleQuery = req.query['title']; // Get query parameters from the request object
  const tagQuery = req.query['tag'];

  task1 = taskList.filter(task => {
    const hasMatchingTitle = !titleQuery || task.title.toLowerCase().includes(titleQuery.toLowerCase()); // Check if the task's title matches the titleQuery 
    const hasMatchingTag = !tagQuery || task.hasTag(tagQuery);  // Check if the task has the specified tag using the hasTag method 
    return hasMatchingTitle && hasMatchingTag;  // Return true if the task's title and tag match the query parameters, false otherwise
});

  task1 = sortTasks(req,task1);
  task1 = pinnedTasks(task1);

	res.render('home' , {"tasks" : task1 , 'url' : "http://localhost:3000" ,titleQuery, tagQuery });
});

app.get('/add', (req, res) => {
  
  res.render('add');
});

app.post('/add', (req, res) => {
  

  // Convert pinned from string to Boolean
  const isPinned = req.body.pinned === 'true';
  // Convert strong of tags to array of tags 
  const tagsArray = req.body.tags.split(',').map(tag => tag.trim());
  // Convert string of priority number to an integer
  const priorityNumber = parseInt(req.body.priority, 10);


  // Create a new task object
  req.body.priority = priorityNumber;
  // Modify the pinned property directly in the newTask object
  req.body.pinned = isPinned; // Set the pinned property based on the conversion
  req.body.tags = tagsArray;
  const newTask = new Task(req.body);

  taskList.push(newTask); // Add the modified newTask object to the taskList
  // Redirect to the home/main page to display the updated task list
  res.redirect('/');

});



app.listen(3000);
console.log('Started server on port 3000');
