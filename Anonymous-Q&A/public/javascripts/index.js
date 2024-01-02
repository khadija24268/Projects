// helper function for creating elements (usage optional)
function createElement(type, attrs, ...children) {
  const ele = document.createElement(type);

  // add element attributes
  for (const prop in attrs) {
    if (attrs.hasOwnProperty(prop)) {
      ele.setAttribute(prop, attrs[prop]);
    }
  }

  // add child nodes to element
  children.forEach(c => ele.appendChild(typeof c === 'string' ? document.createTextNode(c) : c));

  return ele;
}

// Handle the modal visibility for showing/hiding
function toggleModal(modalId, isOpen) {
  const modal = document.getElementById(modalId);
  if (isOpen) {
    modal.classList.add('open');
  } else {
    modal.classList.remove('open');
  }
}

// Function to handle questions and answers
// Function to handle questions and answers
function handleQuestions(questions) {
  const mainElement = document.querySelector('main');

  questions.forEach(question => {
    const questionElement = createElement('div', { class: 'question' },
      createElement('h2', {}, question.question),
      createElement('ul', {}, ...question.answers.map(answer => createElement('li', {}, answer))),
      createElement('button', { class: 'answer-button', 'data-question-id': question._id }, 'Add Answer')
    );

    mainElement.appendChild(questionElement);

    // Add event listener for the answer button in the current question
    const answerButton = questionElement.querySelector('.answer-button');
    answerButton.addEventListener('click', event => {
      const questionId = event.target.getAttribute('data-question-id');
      document.getElementById('question-id').value = questionId;
      toggleModal('modal-answer', true);
    });
  });
}


// Add event listener for Ask a Question button
document.getElementById('btn-show-modal-question').addEventListener('click', () => {
  toggleModal('modal-question', true);
});

// Add event listener for Cancel button in Ask a Question modal
document.querySelector('#modal-question .close').addEventListener('click', () => {
  toggleModal('modal-question', false);
});

// Add event listener for Cancel button in Answer modal
document.querySelector('#modal-answer .close').addEventListener('click', () => {
  toggleModal('modal-answer', false);
});

// Fetch questions on page load
document.addEventListener('DOMContentLoaded', () => {
  fetch('/questions/')
    .then(response => {
      if (!response.ok) {
        throw new Error(`Network response was not ok: ${response.status}`);
      }
      return response.json();
    })
    .then(questions => {
      // Handle the questions and answers here
      handleQuestions(questions);
    })
    .catch(error => {
      console.error('Error fetching questions:', error.message);
      // You can add more robust error handling here, like displaying a friendly error message in the DOM
    });
});
// Add event listener for Ask a Question button
document.getElementById('btn-show-modal-question').addEventListener('click', () => {
  document.getElementById('modal-question').classList.add('open');
});

// Add event listener for Submit button in Ask a Question modal
document.getElementById('create-question').addEventListener('click', () => {
  const questionText = document.getElementById('question-text').value;

  // Make an AJAX POST request to send the question text to the server
  fetch('/questions/', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ question: questionText }),
  })
    .then(response => {
      if (!response.ok) {
        throw new Error(`Network response was not ok: ${response.status}`);
      }
      return response.json();
    })
    .then(result => {
      // On successful result, add the question to the page
      if (!result.error && result._id) {
        addQuestionToPage(result);
        // Close the modal and clear all fields
        toggleModal('modal-question', false);
        document.getElementById('question-text').value = '';
      } else {
        // Log the error message to the console
        console.error('Error:', result.error || 'Unexpected response from the server');
      }
    })
    .catch(error => {
      // Log the error message to the console or add a message in the modal
      console.error('Error:', error.message);
      // You can also add an error message to the modal if needed
    });
});

// Function to add the question to the page
function addQuestionToPage(question) {
  const mainElement = document.querySelector('main');

  const questionElement = createElement('div', { class: 'question' },
    createElement('h2', {}, question.question),
    createElement('ul', { id: question._id },),
    createElement('button', { class: 'answer-button', 'data-question-id': question._id }, 'Add Answer')
  );

  mainElement.appendChild(questionElement);
}

// Function to add "Add Answer" button for the question
function addAnswerButton(questionId) {
  const questionElement = document.querySelector(`[data-question-id="${questionId}"]`);
  const answerButton = createElement('button', { class: 'answer-button', 'data-question-id': questionId }, 'Add Answer');

  // Directly call showAnswerModal when the button is clicked
  answerButton.addEventListener('click', () => {
    const questionId = answerButton.getAttribute('data-question-id');
    document.getElementById('question-id').value = questionId;
    toggleModal('modal-answer', true);
  });

  questionElement.appendChild(answerButton);
}

// Add event listener for Submit button in Answer modal
document.getElementById('create-answer').addEventListener('click', () => {
  const answerText = document.getElementById('answer-text').value;
  const questionId = document.getElementById('question-id').value;

  // Make an AJAX POST request to send the answer text to the server
  fetch(`/questions/${questionId}/answers/`, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({ answer: answerText }),
  })
    .then(response => {
      if (!response.ok) {
        throw new Error(`Network response was not ok: ${response.status}`);
      }
      return response.json();
    })
    .then(result => {
      // On successful result, you might handle it as needed
      console.log(result.success);

      // Close the modal and clear all fields
      toggleModal('modal-answer', false);
      document.getElementById('answer-text').value = '';
    })
    .catch(error => {
      // Log the error message to the console or add a message in the modal
      console.error('Error:', error.message);
      // You can also add an error message to the modal if needed
    });
});



