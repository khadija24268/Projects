//variable declarations
let charsize ; //defines size of player
let player; //variable for the player class object
let platformsize = 40; 
let platform = [];
let score=0;
let highscore=0;
let bonusarr = []; //array to store bonus objects
let caught = false; 
let bonuscaught = []; //
let scorebool = false;
let newchar = false; //boolean variable to help in creating new character when game starts again
let foodnum = 0; //to iterate over food array
let speedincr = 1; //for the vertical motion of platforms

let food = []; //array for food images

let gamestate = 'start'; //gamestate for changes in display
framewidth = 20; 

//variables for images
let startimg , starttext;
let instructimg;
let gameimg;
let endimg, overtext;
let platimg;
let rainbow;
let button, playbutton;
let pixelfont;
let frame;
let headingimg;
let food1, food2, food3;
let cat;

//variables for sound
let success, lose, backsound;

//preload function for all the images and sound
function preload() {
  startimg = loadImage('start.jpeg');
  instructimg = loadImage('instructions.jpeg');
  gameimg = loadImage('game.jpeg');
  endimg = loadImage('end.png');
  platimg = loadImage('platform.png');
  rainbow = loadImage('ladder.webp');
  button = loadImage('button.png');
  pixelfont = loadFont('pixelfont.ttf');
  frame = loadImage('frame.png');
  headingimg = loadImage('heading.png');
  playbutton = loadImage('playbutton.png');
  food1 = loadImage('food1.png');
  food2 = loadImage('food2.png');
  food3 = loadImage('food3.png');
  overtext = loadImage('overtext.png');
  cat = loadImage('cat1.png');
  starttext = loadImage('starttext.png');
  success = loadSound('success.mp3');
  lose = loadSound('lose.mp3');
  backsound = loadSound('sound.mp3');
}


//====================================================
//Bonus class to create the food objects
class Bonus{
  constructor(foodnum){
    this.size = 0.07*width; //maps the size according to canvas size
    this.x = random(0+framewidth, width-this.size-framewidth);
    this.y = height;
    this.num = foodnum;
    
  }
  display(platform){
    this.y = platform.y;

    image(food[this.num], this.x, platform.y-(platform.height)/2, this.size, this.size);


  }
  

}

//====================================================
//class for the player object
class Character{
  constructor(){
    this.x = width/2;
    this.y = charsize/2+framewidth;
    this.speed = 4; //speed for the movement of player horizontally
    this.rownum = 0; //to get image from spritesheet and make player move 
    this.col = 0; //to get image from spritesheet and make player move 
  }
  
  display(){
    imageMode(CENTER);
    let catimg = cat.get(this.col*88.25, this.rownum*78.75, 88.25,78.75);
    image(catimg,this.x, this.y-10, charsize, charsize ); //gets a portion of the sprite sheet for movement effect
    imageMode(CORNER);

  }
  moveleft(){ //if left key is pressed, causes player to move left
    this.x -= this.speed;
    this.rownum = 3;
    this.col = (this.col+1)%4;
    if (this.x < 0 + (charsize/2)+framewidth) {
      this.x = charsize/2+framewidth; //so player does not go beyond the canvas
    }
  }
  moveright(){ //if right key is pressed, causes player to move left
    this.x+=this.speed;
    this.rownum = 1;
    this.col = (this.col+1)%4;
    if (this.x > width-(charsize/2)-framewidth) {
      this.x = width-(charsize/2)-framewidth; //so player does not go beyond the canvas
    }
  }
  update(platform){
   
    //if the player in on the platform and not on the ladder space, then it stays on the platform
    if(this.y >= platform.y && this.y <= platform.y+platformsize && (this.x<platform.spacex || this.x > (platform.spacex+platform.spacewidth))){
      this.y = platform.y;
      
    }
    //if player on ladder space, it falls
    else if(this.x>platform.spacex && this.x < (platform.spacex+platform.spacewidth) && this.y >= platform.y && this.y <= platform.y+platformsize){
      this.rownum = 0;
      this.y+=1;
      this.col = (this.col+1)%4;
    }
    //initially it falls 
    else{
      this.y+=1;
      //this.col = (this.col+1)%4;

    }
  }
  //to check if the x and y coodinates of player and food is same to catch the food
  bonuscatch(bonus){
    if(this.x>bonus.x && this.x < bonus.x+(bonus.size) && this.y>bonus.y && this.y <bonus.y+(bonus.size)){

      caught = true;
      success.play();
    }
  }
  




}
//====================================================
//class to create platforms
class Platform{
  constructor(){
    this.x = 0;
    this.y = height;
    this.width = width;
    this.height = platformsize;
    this.speed = 1;
    
    this.spacewidth = 40; //the ladder dimensions
    this.spacex = random(0+framewidth, width-this.spacewidth-framewidth);
    

  }
  
  displayplatform(){
    rectMode(CORNER);
    noStroke();
     image(platimg, this.x-50, this.y , this.width+100, this.height);
  }
  displayspace(){
    rectMode(CORNER);
    noStroke();

    image(rainbow, this.spacex, this.y, this.spacewidth, this.height+90);
    
  }

  //causes platform to move upwards
  update(){
    this.y -= this.speed;

  }
  
  
}


function setup() {
  
  createCanvas(500, 500);
  charsize = 0.15*width;
  background(220);
  player = new Character();

  bonusarr.push(new Bonus(foodnum));
  bonuscaught.push(0);

  food = [food1, food2, food3];



}

function draw() {

    if(frameCount == 1){ //makes the song play only once 
   backsound.play();
  }
  
  //goes over the gamestates to set the display accordingy 
  
  if(gamestate == 'start'){ //if game is at start page then display homepage
  image(startimg, 0, 0, width, height, 0, 0, startimg.width, startimg.height, COVER);
    
    rectMode(CENTER);
    noStroke();
    fill(236,212,114, 120);
    rect(width/2, (height/2)- (height/4) , width/1.5, (height/5));
    rectMode(CORNER);

      imageMode(CENTER);
  image(starttext,width/2, (height/2)- (height/4) , width/1.5, (height/5));

    
      image(button, width/2, height/2, map(button.width, 0, button.width, 0, width/4), map(button.height, 0, button.height, 0, height/4));
    startpage();
    imageMode(CORNER);
    drawframe();
 
    
  }
  //if gamestate is of 'game' then plays the game through thegame() function
  else if(gamestate == 'game'){

    image(gameimg, 0, 0, width, height, 0, 0, gameimg.width, gameimg.height, COVER); //homepage image displayed
  thegame(); //plays game through this function
drawframe(); 

  }
  
  else if(gamestate == 'over'){ //if gamestate is over then end page displayed 
    image(endimg, 0, 0, width, height, 0, 0, endimg.width, endimg.height, COVER);

  endpage();
    drawframe();
    
  }
  else if(gamestate == 'instructions'){ //displays instructions 
    instructionspage();

  }
}
//========================
function thegame(){ 

 
   //checks if game is started again and creates a new player to play the game again
    if(newchar == true){
     player = new Character();
    newchar = false;
  }
  
  
  
  //checks if player has gone above or below the canvas dimensions and calls the end page 
  if(player.y<0+framewidth || player.y > height-framewidth){
    gamestate = 'over';
      lose.play();
  }

  //for keys to move the player
  if(keyIsDown(LEFT_ARROW)){
    player.moveleft();
  }
  else if (keyIsDown(RIGHT_ARROW)){
    player.moveright();
  }
  


  
  //for new platform and elements to be created and added to their arrays
  if(frameCount%60 == 0){
      foodnum++;
  if (foodnum>food.length-1){
    foodnum = 0;
  }
    platform.push(new Platform());
    bonusarr.push(new Bonus(foodnum));
    bonuscaught.push(0);
 
  }


  
  //FOR LOOP
  for(let i = 0 ; i<platform.length ; i++){
    //shows platforms and updates their positions by decreasing y coordinated to move them up
    platform[i].displayplatform();
    platform[i].displayspace();
    platform[i].update();
     
    
    //checks if player has caught the food
    player.bonuscatch(bonusarr[i]);
    
    //if it is caught, the array to store element boolean representation is updated
    if(caught==true){
      bonuscaught[i] = 1;

    }
    
    //elements are only displayed if their respective values in bonuscaught is 0 so that when the player catches a food, it gets 1 value and disappears 
    if (bonuscaught[i] ==0){
      bonusarr[i].display(platform[i]);
    }
    
    //increases the score when caught
    if(caught == true){
      caught = false;
      scorebool = true;
    }
 
    //when platform and food goes beyond the roof, they are removed from their arrays 
    if (platform[i].y < 0-(platformsize+200) || bonusarr[i].y < 0-(platformsize+200)){
      platform.splice(i, 1);
      bonusarr.splice(i, 1);
      bonuscaught.splice(i,1);
 

    }
    
    //Player's position checked against platform and ladder's position
    player.update(platform[i]);

    platform[i].update();//moves it up
    
  }
  
  player.display(); 
  
  //END of FOR
  
  
  
  //Score increment
  if(scorebool == true){
    
    score++;
    scorebool = false;
  }

  //Text display
  textAlign(LEFT);
  fill('#5D3314');
  textSize(30);
  text('Score: '+ score, 35,50);
  
}

//==============================

function startpage(){ //function to display the images of starting page


    //checks if mouse pressed on the button and directs to instructions
    if(mouseX < width/2 + (width/(width/100)/2) && mouseX > width/2 - (width/(width/100)/2) && mouseY > height/2 - (height/(height/100)/2) && mouseY < height/2 + (height/(height/100)/2) && mouseIsPressed){
      gamestate = 'instructions';
      success.play();
    }
  
}



function endpage(){ //function to display score and highscore and 'game over' page

    imageMode(CENTER);
  image(overtext,width/2, height/2,  width-framewidth, height-framewidth);
  imageMode(CORNER);
  for(let i = 0 ; i<platform.length ; i++){
      platform.pop();
      bonusarr.pop();
      bonuscaught.pop();
  }
  newchar = true;
  
  if(score>highscore){ //updates the highscore with each previous score 
    highscore = score;
  }

  textAlign(CENTER);
  fill(255);
  textSize(0.075*width);
  text('Score: '+score , width/2, (height/2)-30);
  text('High Score: '+highscore , width/2, ((height/2)+30)-20);

  
  if(keyIsDown(ENTER)){ //when ENTER is pressed, gamestate changed so that game starts again
    gamestate = 'game';
    score= 0 ;
  }

}

function instructionspage(){ //displays instruction images 
  image(instructimg, 0, 0, width, height, 0, 0, instructimg.width, instructimg.height, COVER);
  textFont(pixelfont);
  
  image(headingimg, 0, 0, width, height/1.5);

  image(playbutton, (3*width)/4, (3*height)/4, map(button.width, 0, button.width, 0, width-(3*width)/4), map(button.height, 0, button.height, 0, height-(3*height)/4));
  
  //checks if mouse clicked on the button and continues to game state of playing the game
  if(mouseX>(3*width)/4 && mouseX < width && mouseY > (3*height)/4 && mouseY < height && mouseIsPressed){
    gamestate = 'game';
    success.play();
  }

  

}

function drawframe(){ //draws the frame around the canvas 
  noStroke();
  fill('#ECD472');
  rect(0,0,framewidth,height);
  rect(width-framewidth, 0, framewidth, height);
  rect(0,0,width,framewidth);
  rect(0,height-framewidth, width,framewidth);
}

