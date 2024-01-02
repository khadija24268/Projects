# Homework #7 - ANONYMOUS Q&A Web App (AJAX)


### Implementation Highlights

- **Express Application Setup**
  - Created an Express application served on port 3000.
  - Configured necessary files and directories.

- **Server-Side Implementation (app.mjs)**
  - Set up routes to handle API requests for retrieving and adding questions.
  - Configured database connection with a mongoose model.
  - Created route handlers for GET `/questions/` and POST `/questions/`.

- **Client-Side Implementation (index.js)**
  - Utilized AJAX calls (`fetch`) for background requests to the API.
  - Dynamically generated HTML elements for questions and answers.
  - Implemented the Ask a Question functionality with a modal form.
  - Handled AJAX POST to add new questions to the server.

- **Database Management (.env and db.mjs)**
  - Created a `.env` file with a DSN variable for database connection.
  - Set up the data model for questions in `db.mjs`.
  - Added sample questions to the MongoDB database.

- **Overall Structure**
  - Followed the provided directory structure.
  - Ensured proper separation of server-side and client-side code.


## Implementation Details

- **Getting Existing Questions (Reading Data)**
  - Configured the `GET /questions/` route to provide JSON data.
  - Used `fetch` on the client side to retrieve questions and display them dynamically.

- **Modals Implementation**
  - Manually created modal dialog boxes.
  - Implemented the Ask a Question functionality with a modal.

- **Asking New Questions (Adding Data)**
  - Implemented the `POST /questions/` route to add new questions to the database.
  - Added an on-click handler to the "Ask a Question" button for user interaction.
  - Successfully handled AJAX POST requests for adding new questions.

- **Adding New Answers (Optional)**
  - Partially implemented `POST /questions/:id/answers/`.
  - Added an on-click handler to the "Add Your Answer" button for submitting answers.


### Note:
- The provided code serves as a foundation, and additional enhancements can be made for a more feature-rich Q&A application.
- For detailed code snippets, refer to the individual files in the repository.


