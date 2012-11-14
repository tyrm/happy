import ddf.minim.spi.*;
import ddf.minim.signals.*;
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.ugens.*;
import ddf.minim.effects.*;

import processing.serial.*; 

Minim minim;
AudioPlayer player;
AudioPlayer buzzer;
AudioPlayer thunder;

AudioPlayer kidsCheer;
AudioPlayer failTrombone;
AudioPlayer ohMy;
AudioPlayer bcMail;
AudioPlayer sexyWhistle;
AudioPlayer toilet;
AudioPlayer stupid;
AudioPlayer giggle;
AudioPlayer doh;
 
Serial serPort;
String inString;  // Input string from serial port
int lf = 10;

int player1score = 0;
int player2score = 0;
int player3score = 0;
int player4score = 0;

boolean player1buzz = false;
boolean player2buzz = false;
boolean player3buzz = false;
boolean player4buzz = false;

boolean buzzOutWin = false;

boolean player1win = false;
boolean player2win = false;
boolean player3win = false;
boolean player4win = false;

int songCounter=0;

boolean Dance = false;
boolean Lightning = false;

int buzzMode = 0;

int displayMode = 0;

boolean justClicked = true;

void setup() {
  size(displayWidth, displayHeight);
  textFont(loadFont("AgencyFB-Reg-48.vlw"));
  
  println(Serial.list()); 
  serPort = new Serial(this, Serial.list()[0], 9600); 
  serPort.bufferUntil(lf);

  minim = new Minim(this);
  
  player = minim.loadFile("ElectricShock.mp3");
  buzzer = minim.loadFile("buzzer.mp3");
  thunder = minim.loadFile("thunder.mp3");
  
  kidsCheer = minim.loadFile("kids_cheer.mp3");
  failTrombone = minim.loadFile("fail-trombone-01.mp3");
  ohMy = minim.loadFile("George-Takei-Oh-My.mp3");
  bcMail = minim.loadFile("bcmail.mp3");
  sexyWhistle = minim.loadFile("SexyWhistle.mp3");
  toilet = minim.loadFile("ToiletFlush.mp3");
  stupid = minim.loadFile("incredstupid.mp3");
  giggle = minim.loadFile("twgiggle.mp3");
  doh = minim.loadFile("doh2.mp3");
}

void draw() {
  background(0);
  
  drawMenu();
  
  buzzr();
  
  if (keyPressed) {
    if (key == ESC) {
      exit();
    }
  }
  
  if (player.isPlaying() && Dance == false){
    player.pause();
  }
}

void mousePressed() {
  if (inRect(20, 20, 200, 100)) { //Red Point Up
    if (player1score < 4){
      player1score++;
      updateLights(1);
    }
  }
  else if (inRect(20, 200, 200, 100)) { //Red Point Down
    if (0 < player1score) {
      player1score--;
      updateLights(1);
    }
  }
  else if (inRect(240, 20, 200, 100)) { //Yellow Point Up
    if (player2score < 4){
      player2score++;
      updateLights(2);
    }
  }
  else if (inRect(240, 200, 200, 100)) { //Yellow Point Down
    if (0 < player2score) {
      player2score--;
      updateLights(2);
    }
  }
  else if (inRect(460, 20, 200, 100)) { //Green Point Up
    if (player3score < 4){
      player3score++;
      updateLights(3);
    }
  }
  else if (inRect(460, 200, 200, 100)) { //Green Point Down
    if (0 < player3score) {
      player3score--;
      updateLights(3);
    }
  }
  else if (inRect(680, 20, 200, 100)) { //Blue Point Up
    if (player4score < 4){
      player4score++;
      updateLights(4);
    }
  }
  else if (inRect(680, 200, 200, 100)) { //Blue Point Down
    if (0 < player4score) {
      player4score--;
      updateLights(4);
    }
  }
  else if (inRect(20, 320, 200, 100)) { //Red Buzz
    buzz(1);
  }
  else if (inRect(240, 320, 200, 100)) { //Yellow Buzz
    buzz(2);
  }
  else if (inRect(460, 320, 200, 100)) { //Green Buzz
    buzz(3);
  }
  else if (inRect(680, 320, 200, 100)) { //Blue Buzz
    buzz(4);
  }
  else if (inRect(900, 20, 140, 160)) { //Buzzer Mode Off
    buzzMode = 0;
    sequence(49);
    justClicked = true;
  }
  else if (inRect(1055, 20, 140, 160)) { //Buzzer Mode In
    buzzMode = 1;
    justClicked = true;
  }
  else if (inRect(1210, 20, 140, 160)) { //Buzzer Mode Off
    buzzMode = 2;
    justClicked = true;
  }
  else if (inRect(900, 200, 450, 100)) { //Buzzer Reset
    justClicked = true;
  }
  else if (inRect(20, 320+240, 200, 190)) { // Dance
    if (Dance == false) {
      Dance = true;
      Lightning = false;
      buzzMode = 0;
      sequence(55);
      playSong();
    }
    else {
      Dance = false;
      player.pause();
      sequence(49);
    }
  }
  else if (inRect(440+20, 320+240, 200, 190)) { // Lightning
    Dance = false;
    thunder.play(0);
    buzzMode = 0;
    sequence(54);
  }
  else if (inRect(660+20, 320+240, 200, 190)) { // Lightning
    buzzMode = 0;
    
    player1score = 0;
    player2score = 0;
    player3score = 0;
    player4score = 0;
    
    updateLights(1);
    updateLights(2);
    updateLights(3);
    updateLights(4);
    
    player1win = false;
    player2win = false;
    player3win = false;
    player4win = false;
    
    if (player.isPlaying()) {
      player.pause();
    }
    
    Dance = false;
    Lightning = false;
    
    sequence(49);
  }
  else if (inRect(20, 440, 200, 100)) {
    if (player1win == false){
      if (!(player1win||player2win||player3win||player4win)) {
        player1win = true;
        sequence(31);
      }
    }
    else {
      player1win = false;
      sequence(49);
    }
  }
  else if (inRect(240, 440, 200, 100)) {
    if (player2win == false){
      if (!(player1win||player2win||player3win||player4win)) {
        player2win = true;
        sequence(32);
      }
    }
    else {
      player2win = false;
      sequence(49);
    }
  }
  else if (inRect(460, 440, 200, 100)) {
    if (player3win == false){
      if (!(player1win||player2win||player3win||player4win)) {
        player3win = true;
        sequence(33);
      }
    }
    else {
      player3win = false;
      sequence(49);
    }
  }
  else if (inRect(680, 440, 200, 100)) {
    if (player4win == false){
      if (!(player1win||player2win||player3win||player4win)) {
        player4win = true;
        sequence(34);
      }
    }
    else {
      player4win = false;
      sequence(49);
    }
  }
  else if (inRect(20, 440, 200, 100)) {
    if (player1win == false){
      player1win = true;
      sequence(31);
    }
    else {
      player1win = false;
      sequence(49);
    }
  }
  else if (inRect(900, 320, 140, 138)) {
    kidsCheer.play(0);
  }
  else if (inRect(900+155, 320, 140, 138)){
    failTrombone.play(0);
  }
  else if (inRect(900+310, 320, 140, 138)){
    ohMy.play(0);
  }
  else if (inRect(900, 320+148, 140, 138)){
    sexyWhistle.play(0);
  }
  else if (inRect(900+155, 320+148, 140, 138)){
    toilet.play(0);
  }
  else if (inRect(900+310, 320+148, 140, 138)){
    stupid.play(0);
  }
  else if (inRect(900, 320+296, 140, 138)){
    giggle.play(0);
  }
  else if (inRect(900+155, 320+296, 140, 138)){
    doh.play(0);
  }
  else if (inRect(900+310, 320+296, 140, 138)){
    bcMail.play(0);
  }
}

boolean inRect(int cx, int cy, int cw, int ch) {  
  return ((cx < mouseX) && (mouseX < cx+cw)) && ((cy < mouseY) && (mouseY < cy+ch));
}

void playSong() {
  String[] words = { "ElectricShock.mp3", "IAmtheBest.mp3", "Mach.mp3", "Oscar.mp3", "SayMyName.mp3", "ShowShowShow.mp3", "TheDJIsMine.mp3", "VolumeUp.mp3" };
  
  player = minim.loadFile(words[songCounter]);
  player.play(0);
  
  if (songCounter < 7) {
    songCounter++;
  }
  else {
    songCounter = 0;
  }
}

void serialEvent(Serial p) { 
  String theText = p.readString();
  println(int(theText));
  switch(theText.charAt(0)) {
    case '1':
      buzz(1);
      break;
    case '2':
      buzz(2);
      break;
    case '3':
      buzz(3);
      break;
    case '4':
      buzz(4);
      break;
  }
} 

void updateLights(int playr) {
  switch(playr) {
    case 1:
      sequence(60+player1score);
      break;
    case 2:
      sequence(70+player2score);
      break;
    case 3:
      sequence(80+player3score);
      break;
    case 4:
      sequence(90+player4score);
      break;
  }
}

void sequence(int theSeq) {
  serPort.write(theSeq);
}

void buzzr() {
  if (buzzMode == 1) {
    if (justClicked) {
      sequence(49);
      
      player1buzz = false;
      player2buzz = false;
      player3buzz = false;
      player4buzz = false;
      
      justClicked = false;
    };
  }
  else if (buzzMode == 2) {
    if (justClicked) {
      sequence (113);
      
      buzzOutWin = false;
      player1buzz = false;
      player2buzz = false;
      player3buzz = false;
      player4buzz = false;
      
      justClicked = false;
    }
  }
}
void buzz(int player){
  int buzzOutCount = 0;
  
  if (buzzMode == 1 && !(player1buzz||player2buzz||player3buzz||player4buzz)) {
    buzzer.play(0);
    switch (player) {
      case(1):
        player1buzz=true;
        sequence(50);
        break;
      case(2):
        player2buzz=true;
        sequence(51);
        break;
      case(3):
        player3buzz=true;
        sequence(52);
        break;
      case(4):
        player4buzz=true;
        sequence(53);
        break;
    }
  }
  else if (buzzMode == 2 && buzzOutWin == false) {
    buzzer.play(0);
    switch (player) {
      case(1):
        player1buzz=true;
        sequence(119);
        break;
      case(2):
        player2buzz=true;
        sequence(101);
        break;
      case(3):
        player3buzz=true;
        sequence(114);
        break;
      case(4):
        player4buzz=true;
        sequence(116);
        break;
    }
    
    if (player1buzz == false){buzzOutCount++;}
    if (player2buzz == false){buzzOutCount++;}
    if (player3buzz == false){buzzOutCount++;}
    if (player4buzz == false){buzzOutCount++;}
    
    if (buzzOutCount == 1) {
      buzzOutWin = true;
      
      if (player1buzz == false){sequence(50);}
      else if (player2buzz == false){sequence(51);}
      else if (player3buzz == false){sequence(52);}
      else if (player4buzz == false){sequence(53);}
    }
  }
}

void drawMenu(){
  stroke(255);
  noFill();
  rect(20, 20, 200, 100); //Red Point Up
  rect(20, 200, 200, 100); //Red Point Down
  
  rect(240, 20, 200, 100); //Yellow Point Up
  rect(240, 200, 200, 100); //Yellow Point Down
  
  rect(460, 20, 200, 100); //Green Point Up
  rect(460, 200, 200, 100); //Green Point Down
  
  rect(680, 20, 200, 100); //Blue Point Up
  rect(680, 200, 200, 100); //Blue Point Down
  
  rect(20, 320, 200, 100); //Red Buzz
  rect(240, 320, 200, 100); //Yellow Buzz
  rect(460, 320, 200, 100); //Green Buzz
  rect(680, 320, 200, 100); //Blue Buzz
  
  rect(900, 20, 140, 160); //Buzzer Mode Off
  rect(1055, 20, 140, 160); //Buzzer Mode In
  rect(1210, 20, 140, 160); //Buzzer Mode Off
  
  rect(900, 200, 450, 100); //Buzzer Reset
  
  rect(20, 320+240, 200, 190); // Dance
  rect(440+20, 320+240, 200, 190); // Lightning
  rect(660+20, 320+240, 200, 190); // Lightning
  
  rect(20, 440, 200, 100); //Red Winner
  rect(240, 440, 200, 100); //Green Winner
  rect(460, 440, 200, 100); //Yellow Winner
  rect(680, 440, 200, 100); //Blue Winner
  
  //Soundboard
  rect(900, 320, 140, 137); 
  rect(900+155, 320, 140, 137);
  rect(900+310, 320, 140, 137);
  
  rect(900, 320+148-1, 140, 137);
  rect(900+155, 320+148-1, 140, 137);
  rect(900+310, 320+148-1, 140, 137);
  
  rect(900, 320+296-2, 140, 136);
  rect(900+155, 320+296-2, 140, 136);
  rect(900+310, 320+296-2, 140, 136);
}

boolean sketchFullScreen() {
  return true;
}

void stop()
{
// the AudioPlayer you got from Minim.loadFile()
player.close();
minim.stop();

// this calls the stop method that
// you are overriding by defining your own
// it must be called so that your application
// can do all the cleanup it would normally do
super.stop();
}
