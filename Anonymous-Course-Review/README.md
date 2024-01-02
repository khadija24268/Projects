# Anonymous Course Review Web App

## Overview

This project is an anonymous course review web app that allows users to post reviews for courses. I completed this as part of Homework #4, focusing on storing and retrieving data in MongoDB, integrating it with an Express web application using Mongoose, and implementing session-based features.

## Features

- **Display All Reviews:** The app supports a route (`/`) to display all course reviews. It retrieves and showcases reviews from the MongoDB database.

- **Add Reviews:** Users can add anonymous reviews for courses using the `/reviews/add` route. A form is provided to input course details and the review.

- **Filtering:** Implemented a filter feature allowing users to filter reviews by semester, year, and professor's name. This is achieved through a form on the main page (`/`), submitting which filters the displayed reviews accordingly.

- **Pages Visited (by session):** Utilized express-session middleware to track the number of pages a user has visited during a session. The total page visits are displayed on all pages.

- **Reviews Added (by session):** Added a page (`/reviews/mine`) to display reviews added by the user during their session. Users can navigate to this page to view their submitted reviews.


## Page Details

### 1. Home Page (`/`)

- Displays all course reviews.
- Supports filtering by semester, year, and professor's name.
- Shows the total number of pages visited during the session.

### 2. Add Review Page (`/reviews/add`)

- Allows users to submit anonymous reviews.
- Form includes fields for course number, course name, semester, year, professor's name, and the review text.

### 3. My Reviews Page (`/reviews/mine`)

- Displays reviews added by the user during their session.

## Notes

- Made use of the Mongoose library to interact with MongoDB for seamless data storage and retrieval.
- Ensured a clean and structured codebase with regular commits, maintaining readability and ease of collaboration.
- Implemented responsive styles for an improved user experience.

Feel free to explore the app, add reviews, and see the session-based features in action. If you have any questions or suggestions, please don't hesitate to reach out!
