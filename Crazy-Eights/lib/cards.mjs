// cards.mjs

import { match } from "assert";

const suits = {SPADES: '♠️', HEARTS: '❤️', CLUBS: '♣️', DIAMONDS: '♦️'};
const ranks = ['A' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , '10' , 'J' , 'Q' , 'K']; //creates an array of all the ranks


function range(...arg){
    const arr=[];
    let start, inc, end;

    if(arg.length === 1){ //if only end value is given then set start and inc on our own
        start = 0;
        inc = 1;
        end = arg[0];
    }

    else if(arg.length === 2){ //if start and end are given, set inc on our own
        start = arg[0];
        end = arg[1];
        inc = 1;

    }

    else if (arg.length === 3){ //set all three according to the arguments passed
        start = arg[0];
        end = arg[1];
        inc = arg[2];
    }

    for(let i = 0 ; start < end ; i++){ //iterates over the range and adds those numbers
        arr.push(start);
        start+= inc; 
    }
    return arr;

}

function generateDeck(){
    const arr = [];

    for(const suit in suits){ //iterates over the objects of suits
        for(let i = 0 ; i < ranks.length ; i++){ //iterates over the array of ranks
            arr.push({'suit' : suits[suit] , 'rank' : ranks[i]});  //creates objects and adds them to the final array of cards
        }
    }
    return arr;
}


function shuffle (array) {
    //link to the refernce function : https://www.slingacademy.com/article/ways-to-shuffle-an-array-in-javascript/#:~:text=3%20Using%20Lodash-,Using%20Sort()%20Function,sort(()%20%3D%3E%20Math.
    // create a copy of the array so that the original array is not mutated
    const newArray = [...array];
    for (let i = newArray.length - 1; i > 0; i--) {
      const j = Math.floor(Math.random() * (i + 1));
      [newArray[i], newArray[j]] = [newArray[j], newArray[i]];
    }
    return newArray;
  }

  function draw(...arg){
    const cardsArray = arg[0];
    let n = 1;

    const newarr = [...cardsArray]; //copies
    const drawn = [];
    const finalarr = [];

    if(arg.length === 2){ //checking for number of arguments passed
        n = arg[1];
    }

    for(let i = 1 ; i <= n ; i++){
        drawn.push(newarr[newarr.length-1]); //iterates as per the number specified and adds drawn cards to new array
        newarr.pop(); //removes from previous array
    }
    finalarr.push(newarr); //adds both arrays to final array
    finalarr.push(drawn);

    return finalarr;
  }

function deal(...arg){
    const cardsArray = arg[0];
    let numHands = 2;
    let cardsPerHand = 5;

    const newarr = [...cardsArray];
    const hand = [];

    //sets the values according to the arguments provided
    if (arg.length === 2){
        numHands = arg[1];
    }
    else if ( arg.length === 3){
        numHands = arg[1];
        cardsPerHand = arg[2];
    }

    for(let i = 1 ; i <= numHands ; i++){ //according to the number of hands, it iterates and add to array
        const perplayer = [];
        for(let j = 1 ; j<=cardsPerHand ; j++){ //adds cards to each array
            perplayer.push(newarr[newarr.length-1]);
            newarr.pop();
        }
        hand.push(perplayer);//adds the array to the hands array for the final answer object
    }
    const ans = { 'deck' : newarr , 'hands' : hand};

    return ans;

}

function handToString(...arg){
    const hand = arg[0];
    let sep = "  ";
    let numbers = false;
    let ans = "";

    let num = 1;

    if(arg.length === 2){
        sep = arg[1];
    }
    else if (arg.length === 3){
        sep=arg[1];
        numbers = arg[2];
    }

    if(numbers === false) { //if no numbers, then just adding the ranks and seps and suits to one string variable 
        for(let i = 0 ; i < hand.length ; i++){
            ans = ans + hand[i].rank;
            ans = ans + hand[i].suit;

            if( i !== hand.length-1){
                ans = ans + sep;
            }
            
        }
    }

    else if (numbers === true){
        for(let i = 0 ; i < hand.length ; i++){
            ans = ans + num + ": ";
            ans = ans + hand[i].rank;
            ans = ans + hand[i].suit;

            if( i !== hand.length-1){
                ans = ans + sep;
            }
            num++;
        }
    }

    return ans;



}

function matchesAnyProperty(obj , matchObj){
    let ans =false;

    if(obj.suit === matchObj.suit || obj.rank === matchObj.rank){ //compares suit and rank between two objects
        ans = true;
    }
    return ans;
}

function drawUntilPlayable(deck, matchObject){
    const deckarr = [...deck];
    const drawnarr = [];

    

    for(let i = deckarr.length-1 ; i>=0 ; i--){    //iterates over the deck of cards  
        if(deckarr[i].suit === matchObject.suit || deckarr[i].rank === matchObject.rank || deck[i].rank === '8'){ //if match found, breaks the loop
            drawnarr.push(deckarr.pop());
            break;
        }
        drawnarr.push(deckarr.pop());

    }

    return [deckarr , drawnarr];
}

export {
    range,
    generateDeck,
    shuffle,
    draw,
    deal,
    handToString,
    matchesAnyProperty,
    drawUntilPlayable
};
