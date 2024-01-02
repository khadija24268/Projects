// main.js


let deck = [];
// Initialize arrays for the computer and user hands
const computerHand = [];
const userHand = [];


function displayCard(card, handDiv, isFaceDown = true) {
    const cardDiv = document.createElement('div');
    cardDiv.classList.add('card');
  
    if (card) {
      const { value, suit } = card;
      const valueSpan = document.createElement('span');
      valueSpan.textContent = value;
      cardDiv.appendChild(valueSpan);
      
      const suitSpan = document.createElement('span');
      suitSpan.textContent = `${suit}`;
      cardDiv.appendChild(suitSpan);
    } else if (isFaceDown) {
      const valueSpan = document.createElement('span');
      valueSpan.textContent = '?';
      cardDiv.appendChild(valueSpan);
  
      cardDiv.classList.add('face-down');
    }
  
    handDiv.appendChild(cardDiv);
  }

  function displayHand(player, cards, gameDiv) {
    const playerDiv = document.createElement('div');
    playerDiv.classList.add(player.toLowerCase());
    playerDiv.classList.add('hand');
  
    // Display cards
    for (let i = 0; i < cards.length; i++) {
      const isFaceDown = player.toLowerCase() === 'computer' && i > 0;
      displayCard(cards[i], playerDiv, isFaceDown);
    }
  
    // Create and append total element
    const totalElement = document.createElement('div');
    totalElement.classList.add('total');
    //totalElement.textContent = `${player} total: ?`;
    playerDiv.appendChild(totalElement);
  
    gameDiv.appendChild(playerDiv);
  }

function calculateTotal(hand) {
    let total = 0;
    let aceCount = 0;

    for (const card of hand) {

        const value = card.value;

        if (value === 'A') {
            aceCount++;
            total += 11; // Assume A as 11 initially
        } else if (['K', 'Q', 'J'].includes(value)) {
            total += 10;
        } else {
            total += parseInt(value, 10);
        }
    }

    // Handle aces to optimize the total value
    while (total > 21 && aceCount > 0) {
        total -= 10; // Change the value of an Ace from 11 to 1
        aceCount--;
    }

    

    return total;
}


function calculateAndUpdateTotals(computerHand, userHand, gameDiv, show=false) {
    let computerTotalElement = document.querySelector('.computer.total');
    let userTotalElement = document.querySelector('.user.total');

    // Create total elements if they don't exist
    if (!computerTotalElement) {
        computerTotalElement = document.createElement('div');
        computerTotalElement.classList.add('total');
        document.querySelector('.computer').appendChild(computerTotalElement);
    }

    if (!userTotalElement) {
        userTotalElement = document.createElement('div');
        userTotalElement.classList.add('total');
        document.querySelector('.user').appendChild(userTotalElement);
    }

    const computerTotal = calculateTotal(computerHand);
    const userTotal = calculateTotal(userHand);

   if(show===true){
    computerTotalElement.textContent = `Computer total: ${computerTotal.toString()}`;
   }
   else if(show===false){
    computerTotalElement.textContent = "Computer total: ?";
   }

    //computerTotalElement.textContent = computerTotal === null ? '?' : computerTotal.toString();
    userTotalElement.textContent = `Player total: ${userTotal.toString()}`;

    return [computerTotal,userTotal];
}


function drawCard(deck) {
    return deck.pop();
}

function endGame(result) {
    console.log('im here');
    const gameDiv = document.querySelector('.game');
    const resultDiv = document.createElement('div');
    resultDiv.classList.add('result');
    resultDiv.textContent = result;
    gameDiv.appendChild(resultDiv);

    // Disable Hit and Stand buttons after the game ends
    const hitButton = document.getElementById('hitButton');
    const standButton = document.getElementById('standButton');
    console.log(standButton);
    hitButton.disabled = true;
    standButton.disabled = true;
}


function handleStand() {
    const gameDiv = document.querySelector('.game');

    const computerhand = document.querySelector('.computer.hand');

    let [computerTotal,userTotal] = calculateAndUpdateTotals(computerHand, userHand, gameDiv, true);
    // Computer's strategy (simple): Hit if below 18, Stand if 18 or above
    while (computerTotal < 18) {
        const newCard = drawCard(deck);
        computerHand.push(newCard); // Add the new card to the player's hand
        displayCard(newCard, computerhand);
        [computerTotal,userTotal] = calculateAndUpdateTotals(computerHand, userHand, gameDiv,true);
    }

    updateDisplay(true, true);
    if (computerTotal > 21 || (userTotal <= 21 && userTotal > computerTotal)) {
        console.log('1');
        endGame('User wins!');
    } else if (computerTotal === userTotal) {
        console.log('2');
        endGame('It\'s a tie!');
    } else {
        console.log('3');
        endGame('Computer wins!');
    }

}


function handleHit() {
    const gameDiv = document.querySelector('.game');

    
    const newCard = drawCard(deck);

    //const computerhand = document.querySelector('.computer.hand');
    // Display the computer's hand with only the first card visible
    displayHand('Computer', [computerHand[0], null], gameDiv);

    // Display the user's full hand
    displayHand('User', userHand, gameDiv);

    userHand.push(newCard); // Add the new card to the player's hand

    const [computerTotal,userTotal] = calculateAndUpdateTotals(computerHand, userHand, gameDiv, true);
 
    console.log(userTotal, computerTotal);

    updateDisplay();

    if (userTotal > 21) {

        handleStand();
    }

}

function displayButtons() {
    const buttonsDiv = document.createElement('div');
    buttonsDiv.classList.add('buttons');

    const hitButton = document.createElement('button');
    hitButton.id = 'hitButton';
    hitButton.textContent = 'Hit';
    hitButton.addEventListener('click', handleHit);

    const standButton = document.createElement('button');
    standButton.id = 'standButton';
    standButton.textContent = 'Stand';
    standButton.addEventListener('click', handleStand);

    buttonsDiv.appendChild(hitButton);
    buttonsDiv.appendChild(standButton);

    const gameDiv = document.querySelector('.game');
    gameDiv.appendChild(buttonsDiv);
}

function updateDisplay(show=false, score=false) {
    const gameDiv = document.querySelector('.game');

    // Clear any existing content in the game div
    gameDiv.innerHTML = '';

    if(show===false){
        // Display the computer's hand with only the first card visible
        displayHand('Computer', [computerHand[0], null], gameDiv);
    }
    else if(show===true){
        // Display the computer's hand with all card visible
        displayHand('Computer', computerHand, gameDiv);
    }


    // Display the user's full hand
    displayHand('User', userHand, gameDiv);

    // Display Hit and Stand buttons
    displayButtons();

    // Calculate and update totals for both hands
    calculateAndUpdateTotals(computerHand, userHand, gameDiv,score);
}

  

function shuffle(deck) {
    return deck.sort(() => Math.random() - 0.5);
}

function buildDeck() {
    const values = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'];
    const suits = ['♥', '♦', '♣', '♠'];
    const deck = [];

    for (const value of values) {
        for (const suit of suits) {
            deck.push({ value, suit });
        }
    }

    return shuffle(deck);
}




function handleFormSubmit(event) {
    // Prevent the default form submission
    event.preventDefault();

    // Get start values from the input field and clean up the input
    const startValuesInput = document.getElementById('startValues');
    const startValues = startValuesInput.value.split(',').map(value => value.trim());


    // Clear any existing content in the game div
    const gameDiv = document.querySelector('.game');
    gameDiv.innerHTML = '';

    // Hide the form
    const form = document.querySelector('form');
    form.style.display = 'none';

    // Draw cards for the computer and user, alternating turns
    for (let i = startValues.length-1; i >=0; i--) {
        const cardValue = startValues[i];

        for (let j = 0; j < deck.length; j++) {
            const deckCard = deck[j];

            if (cardValue === deckCard.value) {
                deck.push(deckCard);
                // Remove the selected card from the deck
                deck.splice(j, 1);
                break; // Break the loop once the card is found and dealt
            }
        }
    }

    for(let i = 0; i < 4; i++){
        if (i % 2 === 0) {
            computerHand.push(deck.pop());
        } else {
            userHand.push(deck.pop());
        }
    }

    // Display the computer's hand with only the first card visible
    displayHand('Computer', [computerHand[0], null], gameDiv);

    // Display the user's full hand
    displayHand('User', userHand, gameDiv);

    // Display Hit and Stand buttons
    displayButtons();

    // Calculate and update totals for both hands
    calculateAndUpdateTotals(computerHand, userHand, gameDiv);

    updateDisplay();
}


deck = buildDeck();

function main() {
    const form = document.querySelector('form');
    form.addEventListener('submit', handleFormSubmit);

    const hitButton = document.getElementById('hitButton');
    hitButton.addEventListener('click', handleHit);

    const standButton = document.getElementById('standButton');
    standButton.addEventListener('click', handleStand);

    updateDisplay();
}

document.addEventListener('DOMContentLoaded', function () {
    const form = document.querySelector('form');
    form.addEventListener('submit', handleFormSubmit);
    main();

});

