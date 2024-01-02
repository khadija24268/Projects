# Task Manager Web App

## Overview

Task Manager is a web application designed for managing and organizing tasks. It provides essential functionalities such as displaying, sorting, and filtering tasks. The application consists of two main pages:

1. **Home Page (/):**
   - Displays a list of tasks stored locally on the server.
   - Supports sorting tasks by due date, priority, and pinned status.
   - Enables filtering tasks by title and tags.
   - Pinned tasks are shown at the top of the list.

2. **Add Task Page (/add):**
   - Allows users to submit new tasks using a POST form.
   - Form includes fields for title, description, priority, due date, pinned status, tags, and progress.

## Key Features

- **HTML and CSS Styling:**
  - Utilizes HTML for structuring pages and CSS for styling.
  - Responsive design for an optimal user experience.

- **Server and Routes:**
  - Express.js is used to create a basic server in app.mjs.
  - Static files (CSS, images) are served using express.static middleware.

- **Middleware and Logging:**
  - Custom middleware logs request details, providing valuable information for debugging.

- **Handlebars Templating:**
  - Handlebars (hbs) templating engine is employed for rendering dynamic content.

- **Task Management:**
  - Task class defined in task.mjs to store task details.
  - Tasks are read from static files and displayed in a table on the home page.
  - Sorting functionality sorts tasks by due date, priority, and pinned status.

- **Filtering:**
  - Home page includes a form for filtering tasks by title and tags.

- **Add New Task:**
  - The /add page allows users to submit new tasks via a POST form.
  - New tasks are added to the in-memory store and displayed on the home page.



