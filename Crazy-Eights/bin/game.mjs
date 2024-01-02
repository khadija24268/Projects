// game.mjs


//Declaring all the global variable used through out the game
let comphand = [];
let playerhand = [];
let carddeck = []; 
let discard = [];
let strdisplay = " ";

let nextcard = {};





//importing the functions created in cards.mjs and the necessary module for reading the JSON file
import {
    generateDeck,
    shuffle,
    draw,
    deal,
    handToString,
    matchesAnyProperty,
    drawUntilPlayable} from "../lib/cards.mjs";
import {question} from 'readline-sync';
//import clear from 'clear';
//import {readFile} from 'fs';
//import * as os from 'os';
import fs from 'fs';

//function to display the options to the player when the card they have played as a rank of '8'
function playedEight(){
    let ans = " ";
    ans = question(`CRAZY EIGHTS! You played an 8 - choose a suit \n 1: ♠️ \n 2: ❤️ \n 3: ♣️ \n 4: ♦️\n`); //displays the question and waits for the player to enter the ans
    return ans; //returns the answer so it can be used in the other functions 
}

//function to read data from the JSON file
function readJSON(callback) {
    const jsonFilePath = process.argv[2]; //variable to store the file path 
    fs.readFile(jsonFilePath, (err, data) => {
        if (err) {throw err;} //if there are any errors during the process of reading the file, it throws those erros 
        const outputdata = JSON.parse(data); //parses the data obtained from the file into an object

        // calling the callback with data
        callback(outputdata);
    });
}

//in the case that a JSON file is not provided, this function sets the cards and decks for the game
function gameSetup(){

    carddeck = generateDeck(); //uses generate function to create a deck
    carddeck = shuffle(carddeck); //shuffles the deck

    const dealcards = deal(carddeck,2,5); //gives out standard 5 cards to player and computer each

    //separates the decks in terms of carddeck, deck of player, deck of computer
    carddeck = dealcards.deck; 
    comphand = dealcards.hands[0];
    playerhand = dealcards.hands[1];

    //draws card from card deck for the starter card
    let drawset = [];
    //keeps drawing from the deck if card of rank '8' is drawn
    do{
        drawset = draw(carddeck , 1);
    }while(drawset[1].rank === '8');

    discard = drawset[1]; //sets the discard pile
    carddeck = drawset[0]; //updates the card deck after drawing acrds from it 

    nextcard = discard[discard.length-1]; //the next card to play is set



   
}

//displays the main game screen
function gameStart(){
    //converts player and computer cards to strings for display
    const compcards = handToString(comphand);
    const playercards = handToString(playerhand);


    console.log("              CR🤪ZY 8's\n");
    console.log("-----------------------------------------------\n");
    console.log("Next suit/rank to play: ➡️ " , nextcard.rank , nextcard.suit , " ⬅️\n");
    console.log("-----------------------------------------------\n");
    console.log("Top of discard pile:" , discard[discard.length-1].rank , discard[discard.length-1].suit , "\n");
    console.log("Number of cards left in deck:" , carddeck.length, "\n");
    console.log("-----------------------------------------------\n");
    console.log("🤖✋ (computer hand):" , compcards , "\n");
    console.log("😊✋ (player hand):" , playercards , "\n");
    console.log("-----------------------------------------------\n");

}

//function checks if the player or computer has the card that has to be played next in their hands
function turnCheck(arr){
    let ans = false; //default ans is false
    for(let i = 0 ; i<arr.length ; i++){
        ans = matchesAnyProperty(nextcard , arr[i] ); //uses predefined function to match the next card with the cards of player/computer on loop
        if (ans === true){
            break; //if they have even one matching, the answer is yes (true)
        }
    }
    return ans;
}

//Displays the player turn
function playerTurn(){
    const has = turnCheck(playerhand); //checks if player has matching card or an 8
    const carddisplay = handToString(playerhand , "\n" , true); //converts player cards to string for display 
    let reply;
    let num1;

    let drawuntillplay = [];

    if(has === true){ //for the case that the player does have matching suits or ranks or an 8
        console.log("😊 Player's turn...\n"); 
        console.log("Enter the number of the card you would like to play\n");//displays the choices to the player
        console.log(carddisplay , "\n");
        reply = question(""); //gets input from the player
        num1 = parseInt(reply); //converts from string to integer
        nextcard = playerhand[num1-1]; //changes the value of the next card to the card played by player

        const remove = num1;
        
        //in case the player chooses a card with rank 8
        if(nextcard.rank === '8'){
            reply = playedEight(); //displays options to player for choosing a suit
            num1 = parseInt(reply); 
            nextcard.rank = '8';
            //matches the suit chosen and sets the next card's suit to that
            if(num1 === 1){
                nextcard = {...nextcard , 'suit' : '♠️'};
                
            }
            else if(num1===2){
                nextcard = {...nextcard , 'suit' : '❤️'};
                
            }
            else if(num1===3){
                nextcard = {...nextcard , 'suit' : '♣️'};
                
            }
            else if(num1===4){
                nextcard = {...nextcard , 'suit' : '♦️'};
                
            }
            console.log("SUCCESS");

        }

        discard.push(playerhand[remove-1]); // pushes the card played onto the discard pile
        playerhand.splice(remove-1 , 1); //removes that card from the hands of the player



    }
    //for the case that the player does not have a matching card
    else if(has === false){
        console.log("😊 Player's turn...\n");
        console.log("😔 You have no playable cards\n");
        reply = question(`Press ENTER to draw cards until matching: ${discard[discard.length-1].rank} ${discard[discard.length-1].suit} 8`);//prompts player to press ENTER to draw cards

        drawuntillplay = drawUntilPlayable(carddeck , nextcard); //uses predefined function to draw cards from card deck untill a crd is drawn which matches the nextcard
        strdisplay = handToString(drawuntillplay[1]); //converts to string for displaying
        console.log("Cards drawn:" , strdisplay, "\n");
        console.log("Card played:" , drawuntillplay[1][drawuntillplay[1].length-1].rank ,drawuntillplay[1][drawuntillplay[1].length-1].suit , "\n" );
        
        //iterates over the drawn pile of cards and adds it to the player's hand
        for(let i = 0 ; i < drawuntillplay[1].length ; i++){
            playerhand.push(drawuntillplay[1][i]);
        
        }
        discard.push(playerhand[playerhand.length-1]);
        nextcard = playerhand[playerhand.length-1];//sets the next card to the one played by player, which is the most recently drawn card
        
        //console.log("Before: " , playerhand);
        playerhand.pop(); //removes that card from the player's hand
        //console.log("After: " , playerhand);
        carddeck = drawuntillplay[0]; //updates the card deck after drawing out the cards

        //again, if the card drawn has a rank of '8', it takes user input for which suit to be set for next card
        if(nextcard.rank === '8'){
            reply = playedEight();
            num1 = parseInt(reply);
            nextcard.rank = '8';
            if(num1 === 1){
                nextcard = {...nextcard , 'suit' : '♠️'};
                
            }
            else if(num1===2){
                nextcard = {...nextcard , 'suit' : '❤️'};
                
            }
            else if(num1===3){
                nextcard = {...nextcard , 'suit' : '♣️'};
                
            }
            else if(num1===4){
                nextcard = {...nextcard , 'suit' : '♦️'};
                
            }

        }
        
        
        
        //waits for player's response to move on to the computer's turn
        reply = question(`Press ENTER to continue`);

        

    }
}

//displays the computer's turn
function computerTurn(){
    const has = turnCheck(comphand);//checks if the computer has cards in hand which match the next play
    let played = {};
    

    console.log("😊 Computer's turn...\n");

    if(has === true){ //if computer has a matching card
        for(let i = 0 ; i< comphand.length ; i++){ //iterates over the cards in computer's hand and plays the first card that matches
            played = comphand[i];
            if(played.rank === nextcard.rank || played.suit === nextcard.suit || played.rank === '8'){//if matched
                discard.push(comphand[i]); //adds the matches card to the discarded pile 
                comphand.splice(i , 1); //removes it from computer's hand
                break;
            }
        }
        if(played.rank === '8'){ //if a eight is played, make the decision for the computer and choose heart as the suit
            nextcard.suit = '❤️ ';
            nextcard.rank = '8';
        }
        else{
            nextcard = played;
        }
        console.log("Card Played: " , nextcard.rank , nextcard.suit , "\n");
    }

    else if (has === false){ //if computer does not have matching card
        const drawuntillplay = drawUntilPlayable(carddeck , nextcard); //uses predefined function to draw cardsuntill matching card found
        strdisplay = handToString(drawuntillplay[1]);
        console.log("Cards drawn:" , strdisplay, "\n");
        console.log("Card played:" , drawuntillplay[1][drawuntillplay[1].length-1].rank ,drawuntillplay[1][drawuntillplay[1].length-1].suit , "\n" );
        

        for(let i = 0 ; i < drawuntillplay[1].length ; i++){
            comphand.push(drawuntillplay[1][i]); //pushes the drawn cards to the computer's hands
        
        }

        nextcard = comphand[comphand.length-1]; //sets the next card to the recently played card by computer
        discard.push(comphand[comphand.length-1]); //adds it to the discard pile
       
        comphand.pop(); //removes that played card from the computer's hands
     
        carddeck = drawuntillplay[0]; //updates deck


        if(nextcard.rank === '8'){ //sets the suit to spades
            nextcard.suit = '♠️';
        }
    }

    question(`Press ENTER to continue`); //waits for player to press enter to see final screen


}


if (process.argv.length === 3) {
    // Pass a callback function to readJSON
    readJSON((fileData) => {
        carddeck = fileData.deck;
        playerhand = fileData.playerHand;
        comphand = fileData.computerHand;
        discard = fileData.discardPile;
        nextcard = fileData.nextPlay;
        //console.log(nextcard);
        gameStart();
        playerTurn();
        console.clear();

        gameStart();
        computerTurn();
        console.clear();
        gameStart();

    });

    //console.log(fileData.deck);
}
else {
    gameSetup();
    gameStart();
    playerTurn();
    console.clear();

    gameStart();
    computerTurn();
    console.clear();
    gameStart();
}








// gameSetup();
// gameStart();
// playerTurn();
// console.clear();

// gameStart();
// computerTurn();
// console.clear();
// gameStart();


