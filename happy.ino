//Import Libraries
#include "SPI.h"
#include "Adafruit_WS2801.h"

//Assign Pins
  //Ditigal
const int modeInterupt = 2; //Interupt Pin
//const int spectrumStep = 4; //Unused in this version
//const int spectrumReset = 5; //Unused in this version
const int dataPin  = 6; //Light
const int clockPin = 7;
const int psOn = 8;

const int pixelz[16][8]={ {14,  15,  16,  17,  21,  22,  23,  24},  //Square 4
                          {54,  55,  56,  57,  61,  62,  63,  64},  //Square 3
                          {94,  95,  96,  97,  101, 102, 103, 104}, //Square 2
                          {134, 135, 136, 137, 141, 142, 143, 144}, //Square 1
                          {130, 131, 132, 133, 145, 146, 147, 148}, //Square 8
                          {90,  91,  92,  93,  105, 106, 107, 108}, //Square 7
                          {50,  51,  52,  53,  65,  66,  67,  68},  //Square 6
                          {10,  11,  12,  13,  25,  26,  27,  28},  //Square 5
                          {5,   6,   7,   8,   30,  31,  32,  33},  //Square 12
                          {45,  46,  47,  48,  70,  71,  72,  73},  //Square 11
                          {85,  86,  87,  88,  110, 111, 112, 113}, //Square 10
                          {125, 126, 127, 128, 150, 151, 152, 153}, //Square 9
                          {121, 122, 123, 124, 154, 155, 156, 157}, //Square 16
                          {81,  82,  83,  84,  114, 115, 116, 117}, //Square 15
                          {41,  42,  43,  44,  74,  75,  76,  77},  //Square 14
                          {1,   2,   3,   4,   34,  35,  36,  37}}; //Square 13

boolean player1;
boolean player2;
boolean player3;
boolean player4;

int player1score = 0;
int player2score = 0;
int player3score = 0;
int player4score = 0;

boolean modeChanged = true;
int incomingByte = 0;

//Init Light Pixels
const int numPixels = 160;
Adafruit_WS2801 dayshade = Adafruit_WS2801(numPixels, dataPin, clockPin, WS2801_GRB);

//Init Global Variables
int mode = 49; //What program is running

void setup() {
  dayshade.begin(); 
  dayshade.show(); // Update LED contents, to start they are all 'off'
  
  digitalWrite(psOn, LOW);
  
  randomSeed(analogRead(5));
  
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  
  Serial.begin(9600);
}


void loop() {
  switch (mode) {
    case 31:
      win1();
      break;
    case 32:
      win2();
      break;
    case 33:
      win3();
      break;
    case 34:
      win4();
      break;
    case 48:
      blackout();
      break;
    case 49:
      game();
      break;
    case 50:
      buzzIn1();
      break;
    case 51:
      buzzIn2();
      break;
    case 52:
      buzzIn3();
      break;
    case 53:
      buzzIn4();
      break;
    case 54:
      thunder();
      break;
    case 55:
      dance();
      break;
    case 113:
      buzzOut();
      break;
    case 119:
      buzzOut1();
      break;
    case 101:
      buzzOut2();
      break;
    case 114:
      buzzOut3();
      break;
    case 116:
      buzzOut4();
      break;
  }
  dayshade.show();
  modeChanged = false;
  
  //if(digitalRead(modeInterupt)){changeMode();};
  if (Serial.available() > 0) {
    incomingByte = int(Serial.read());
    
    switch(incomingByte) {
      case 60:
        player1score = 0;
        break;
      case 61:
        player1score = 1;
        break;
      case 62:
        player1score = 2;
        break;
      case 63:
        player1score = 3;
        break;
      case 64:
        player1score = 4;
        break;
      case 70:
        player2score = 0;
        break;
      case 71:
        player2score = 1;
        break;
      case 72:
        player2score = 2;
        break;
      case 73:
        player2score = 3;
        break;
      case 74:
        player2score = 4;
        break;
      case 80:
        player3score = 0;
        break;
      case 81:
        player3score = 1;
        break;
      case 82:
        player3score = 2;
        break;
      case 83:
        player3score = 3;
        break;
      case 84:
        player3score = 4;
        break;
      case 90:
        player4score = 0;
        break;
      case 91:
        player4score = 1;
        break;
      case 92:
        player4score = 2;
        break;
      case 93:
        player4score = 3;
        break;
      case 94:
        player4score = 4;
        break;
      default:
        changeMode(incomingByte);
        break;
    }
  }
  
  buzzr();
  
  delay(5);
}

void buzzr() {
  static boolean player1 = false;
  static boolean player2 = false;
  static boolean player3 = false;
  static boolean player4 = false;
  
  if(digitalRead(8)) {
    if(player1 == false) {
      Serial.println("1");
    }
    player1 = true;
  }
  else {
    player1 = false;
  };
  if(digitalRead(9)) {
    if(player2 == false) {
      Serial.println("2");
    }
    player2 = true;
  }
  else {
    player2 = false;
  };
  if(digitalRead(10)) {
    if(player3 == false) {
      Serial.println("3");
    }
    player3 = true;
  }
  else {
    player3 = false;
  };
  if(digitalRead(11)) {
    if(player4 == false) {
      Serial.println("4");
    }
    player4 = true;
  }
  else {
    player4 = false;
  };
  
}

//************************************************ Programs *************************************************//
void blackout() {
  for(int i=0; i<16; i++) {
    setSquare(i,Color(0,0,0));
  }
};

// "Normal Lighing"
void game() {
  static int counter;
  if (modeChanged == true) {
    counter = 0;
  }
  
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  
  counter++;
  
  for(int i=12; i<16; i++) {
    setSquare(i,Color(255,175,140));
  }
  if(player1score>2){setSquare(12,Color(255,0,0));};
  if(player2score>2){setSquare(13,Color(255,255,0));};
  if(player3score>2){setSquare(14,Color(0,255,0));};
  if(player4score>2){setSquare(15,Color(0,0,255));};
  
  if (counter>5) {
    for(int i=8; i<12; i++) {
      setSquare(i,Color(255,175,140));
    }
    if(player1score>1){setSquare(11,Color(255,0,0));};
    if(player2score>1){setSquare(10,Color(255,255,0));};
    if(player3score>1){setSquare(9,Color(0,255,0));};
    if(player4score>1){setSquare(8,Color(0,0,255));};
    digitalWrite(3, HIGH);
  }
  
  if (counter>10) {
    for(int i=4; i<8; i++) {
      setSquare(i,Color(255,175,140));
    }
    if(player1score>0){setSquare(4,Color(255,0,0));};
    if(player2score>0){setSquare(5,Color(255,255,0));};
    if(player3score>0){setSquare(6,Color(0,255,0));};
    if(player4score>0){setSquare(7,Color(0,0,255));};
    digitalWrite(4, HIGH);
  }
  
  if (counter>15) {
    setSquare(0, Color(0,0,255));
    setSquare(1, Color(0,255,0));
    setSquare(2, Color(255,255,0));
    setSquare(3, Color(255,0,0));
    
    digitalWrite(5, HIGH);
  }
}

void buzzIn1() {
  static int counter;
  if (modeChanged == true) {
    counter = 0;
  }
  
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  
  if (counter==0) {
    setSquare(15,Color(255,0,0));
  }
  if (counter==2) {
    setSquare(15,Color(0,0,0));
    
    setSquare(14,Color(255,0,0));
    setSquare(8,Color(255,0,0));
    
    digitalWrite(2, LOW);
  }
  if (counter==4) {
    setSquare(14,Color(0,0,0));
    setSquare(8,Color(0,0,0));
    
    setSquare(13,Color(255,0,0));
    setSquare(9,Color(255,0,0));
    setSquare(7,Color(255,0,0));
    
    digitalWrite(2, HIGH);
  }
  if (counter==6) {
    setSquare(13,Color(0,0,0));
    setSquare(9,Color(0,0,0));
    setSquare(7,Color(0,0,0));
    
    setSquare(12,Color(255,0,0));
    setSquare(10,Color(255,0,0));
    setSquare(6,Color(255,0,0));
    setSquare(0,Color(255,0,0));
    
    digitalWrite(2, LOW);
  }
  if (counter==8) {
    setSquare(12,Color(0,0,0));
    setSquare(10,Color(0,0,0));
    setSquare(6,Color(0,0,0));
    setSquare(0,Color(0,0,0));
    
    setSquare(11,Color(255,0,0));
    setSquare(5,Color(255,0,0));
    setSquare(1,Color(255,0,0));
    
    digitalWrite(2, HIGH);
  }
  if (counter==10) {;
    setSquare(11,Color(0,0,0));
    setSquare(5,Color(0,0,0));
    setSquare(1,Color(0,0,0));
    
    setSquare(4,Color(255,0,0));
    setSquare(2,Color(255,0,0));
    
    digitalWrite(2, LOW);
  }
  if (counter==12) {;
    setSquare(2,Color(0,0,0));
    setSquare(4,Color(0,0,0));
    
    setSquare(3,Color(255,0,0));
    
    digitalWrite(2, HIGH);
  }
  if (counter==14) {;
    setSquare(4,Color(255,0,0));
    
    digitalWrite(2, LOW);
  }
  if (counter==16) {;
    setSquare(11,Color(255,0,0));
    
    digitalWrite(2, HIGH);
  }
  if (counter==18) {;
    setSquare(12,Color(255,0,0));
    
    digitalWrite(2, LOW);
  }
  if (counter==20) {;
    setSquare(2,Color(255,175,140));
    setSquare(5,Color(255,175,140));
    setSquare(10,Color(255,175,140));
    setSquare(13,Color(255,175,140));
    
    digitalWrite(2, HIGH);
  }
  if (counter==22) {;
    setSquare(1,Color(255,175,140));
    setSquare(6,Color(255,175,140));
    setSquare(9,Color(255,175,140));
    setSquare(14,Color(255,175,140));
    
    digitalWrite(2, LOW);
  }
  if (counter==23) {;
    setSquare(0,Color(255,175,140));
    setSquare(7,Color(255,175,140));
    setSquare(8,Color(255,175,140));
    setSquare(15,Color(255,175,140));
    
    digitalWrite(2, HIGH);
  }
  
  counter++;
}

void buzzIn2() {
  static int counter;
  if (modeChanged == true) {
    counter = 0;
  }
  
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  
  if (counter==0) {
    setSquare(15,Color(255,255,0));
  }
  if (counter==2) {
    setSquare(15,Color(0,0,0));
    
    setSquare(14,Color(255,255,0));
    setSquare(8,Color(255,255,0));
    setSquare(12,Color(255,255,0));
    
    digitalWrite(3, LOW);
  }
  if (counter==4) {
    setSquare(14,Color(0,0,0));
    setSquare(8,Color(0,0,0));
    setSquare(12,Color(0,0,0));
    
    setSquare(13,Color(255,255,0));
    setSquare(9,Color(255,255,0));
    setSquare(7,Color(255,255,0));
    setSquare(11,Color(255,255,0));
    
    digitalWrite(3, HIGH);
  }
  if (counter==6) {
    setSquare(13,Color(0,0,0));
    setSquare(9,Color(0,0,0));
    setSquare(7,Color(0,0,0));
    setSquare(11,Color(0,0,0));
    
    setSquare(4,Color(255,255,0));
    setSquare(10,Color(255,255,0));
    setSquare(6,Color(255,255,0));
    setSquare(0,Color(255,255,0));
    
    digitalWrite(3, LOW);
  }
  if (counter==8) {
    setSquare(4,Color(0,0,0));
    setSquare(10,Color(0,0,0));
    setSquare(6,Color(0,0,0));
    setSquare(0,Color(0,0,0));
    
    setSquare(3,Color(255,255,0));
    setSquare(5,Color(255,255,0));
    setSquare(1,Color(255,255,0));
    
    digitalWrite(3, HIGH);
  }
  if (counter==10) {;
    setSquare(3,Color(0,0,0));
    setSquare(5,Color(0,0,0));
    setSquare(1,Color(0,0,0));
    
    setSquare(2,Color(255,255,0));
    
    digitalWrite(3, LOW);
  }
  if (counter==12) {;
    setSquare(5,Color(255,255,0));
    
    digitalWrite(3, HIGH);
  }
  if (counter==14) {;
    setSquare(10,Color(255,255,0));
    
    digitalWrite(3, LOW);
  }
  if (counter==16) {;
    setSquare(13,Color(255,255,0));
    
    digitalWrite(3, HIGH);
  }
  if (counter==18) {;
    setSquare(3,Color(255,175,140));
    setSquare(4,Color(255,175,140));
    setSquare(11,Color(255,175,140));
    setSquare(12,Color(255,175,140));
    
    digitalWrite(3, LOW);
  }
  if (counter==20) {;
    setSquare(1,Color(255,175,140));
    setSquare(6,Color(255,175,140));
    setSquare(9,Color(255,175,140));
    setSquare(14,Color(255,175,140));
    
    digitalWrite(3, HIGH);
  }
  if (counter==22) {;
    setSquare(0,Color(255,175,140));
    setSquare(7,Color(255,175,140));
    setSquare(8,Color(255,175,140));
    setSquare(15,Color(255,175,140));
  }
  
  counter++;
}
void buzzIn3() {
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  
  static int counter;
  if (modeChanged == true) {
    counter = 0;
  }
  
  if (counter==0) {
    setSquare(12,Color(0,255,0));
  }
  if (counter==2) {
    setSquare(12,Color(0,0,0));
    
    setSquare(13,Color(0,255,0));
    setSquare(11,Color(0,255,0));
    setSquare(15,Color(0,255,0));
    
    digitalWrite(4,LOW);
  }
  if (counter==4) {
    setSquare(13,Color(0,0,0));
    setSquare(11,Color(0,0,0));
    setSquare(15,Color(0,0,0));
    
    setSquare(14,Color(0,255,0));
    setSquare(10,Color(0,255,0));
    setSquare(4,Color(0,255,0));
    setSquare(8,Color(0,255,0));
    
    digitalWrite(4,HIGH);
  }
  if (counter==6) {
    setSquare(14,Color(0,0,0));
    setSquare(10,Color(0,0,0));
    setSquare(4,Color(0,0,0));
    setSquare(8,Color(0,0,0));
    
    setSquare(7,Color(0,255,0));
    setSquare(9,Color(0,255,0));
    setSquare(5,Color(0,255,0));
    setSquare(3,Color(0,255,0));
    
    digitalWrite(4,LOW);
  }
  if (counter==8) {
    setSquare(7,Color(0,0,0));
    setSquare(9,Color(0,0,0));
    setSquare(5,Color(0,0,0));
    setSquare(3,Color(0,0,0));
    
    setSquare(0,Color(0,255,0));
    setSquare(6,Color(0,255,0));
    setSquare(2,Color(0,255,0));
    
    digitalWrite(4,HIGH);
  }
  if (counter==10) {;
    setSquare(0,Color(0,0,0));
    setSquare(6,Color(0,0,0));
    setSquare(2,Color(0,0,0));
    
    setSquare(1,Color(0,255,0));
    
    digitalWrite(4,LOW);
  }
  if (counter==12) {;
    setSquare(6,Color(0,255,0));
    
    digitalWrite(4,HIGH);
  }
  if (counter==14) {;
    setSquare(9,Color(0,255,0));
    
    digitalWrite(4,LOW);
  }
  if (counter==16) {;
    setSquare(14,Color(0,255,0));
    
    digitalWrite(4,HIGH);
  }
  if (counter==18) {;
    setSquare(3,Color(255,175,140));
    setSquare(4,Color(255,175,140));
    setSquare(11,Color(255,175,140));
    setSquare(12,Color(255,175,140));
    
    digitalWrite(4,LOW);
  }
  if (counter==20) {;
    setSquare(2,Color(255,175,140));
    setSquare(5,Color(255,175,140));
    setSquare(10,Color(255,175,140));
    setSquare(13,Color(255,175,140));
    
    digitalWrite(4,HIGH);
  }
  if (counter==22) {;
    setSquare(0,Color(255,175,140));
    setSquare(7,Color(255,175,140));
    setSquare(8,Color(255,175,140));
    setSquare(15,Color(255,175,140));
  }
  
  counter++;
}

void buzzIn4() {
  static int counter;
  if (modeChanged == true) {
    counter = 0;
  }
  
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  
  if (counter==0) {
    setSquare(12,Color(0,0,255));
  }
  if (counter==2) {
    setSquare(12,Color(0,0,0));
    
    setSquare(13,Color(0,0,255));
    setSquare(11,Color(0,0,255));
  
    digitalWrite(5,LOW);
  }
  if (counter==4) {
    setSquare(13,Color(0,0,0));
    setSquare(11,Color(0,0,0));
    
    setSquare(14,Color(0,0,255));
    setSquare(10,Color(0,0,255));
    setSquare(4,Color(0,0,255));
  
    digitalWrite(5,LOW);
  }
  if (counter==6) {
    setSquare(14,Color(0,0,0));
    setSquare(10,Color(0,0,0));
    setSquare(4,Color(0,0,0));
    
    setSquare(15,Color(0,0,255));
    setSquare(9,Color(0,0,255));
    setSquare(5,Color(0,0,255));
    setSquare(3,Color(0,0,255));
  
    digitalWrite(5,HIGH);
  }
  if (counter==8) {
    setSquare(15,Color(0,0,0));
    setSquare(9,Color(0,0,0));
    setSquare(5,Color(0,0,0));
    setSquare(3,Color(0,0,0));
    
    setSquare(8,Color(0,0,255));
    setSquare(6,Color(0,0,255));
    setSquare(2,Color(0,0,255));
  
    digitalWrite(5,LOW);
  }
  if (counter==10) {;
    setSquare(8,Color(0,0,0));
    setSquare(6,Color(0,0,0));
    setSquare(2,Color(0,0,0));
    
    setSquare(7,Color(0,0,255));
    setSquare(1,Color(0,0,255));
  
    digitalWrite(5,HIGH);
  }
  if (counter==12) {;
    setSquare(7,Color(0,0,0));
    setSquare(1,Color(0,0,0));
    
    setSquare(0,Color(0,0,255));
  
    digitalWrite(5,LOW);
  }
  if (counter==14) {;
    setSquare(7,Color(0,0,255));
  
    digitalWrite(5,HIGH);
  }
  if (counter==16) {;
    setSquare(8,Color(0,0,255));
  
    digitalWrite(5,LOW);
  }
  if (counter==18) {;
    setSquare(15,Color(0,0,255));
  
    digitalWrite(5,HIGH);
  }
  if (counter==20) {;
    setSquare(3,Color(255,175,140));
    setSquare(4,Color(255,175,140));
    setSquare(11,Color(255,175,140));
    setSquare(12,Color(255,175,140));
  
    digitalWrite(5,LOW);
  }
  if (counter==22) {;
    setSquare(2,Color(255,175,140));
    setSquare(5,Color(255,175,140));
    setSquare(10,Color(255,175,140));
    setSquare(13,Color(255,175,140));
  
    digitalWrite(5,HIGH);
  }
  if (counter==23) {;
    setSquare(1,Color(255,175,140));
    setSquare(6,Color(255,175,140));
    setSquare(9,Color(255,175,140));
    setSquare(14,Color(255,175,140));
  }
  
  counter++;
}

void buzzOut() {
  
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    
    player1 = true;
    player2 = true;
    player3 = true;
    player4 = true;
    
    modeChanged = false;
  }
    
    if (player1 == true){
      digitalWrite(2,HIGH);
    }
    else {
      digitalWrite(2,LOW);
    }
    if (player2 == true){
      digitalWrite(3,HIGH);
    }
    else {
      digitalWrite(3,LOW);
    }
    if (player3 == true){
      digitalWrite(4,HIGH);
    }
    else {
      digitalWrite(4,LOW);
    }
    if (player4 == true){
      digitalWrite(5,HIGH);
    }
    else {
      digitalWrite(5,LOW);
    }
  
    if (player1==true) {
      setSquare(3,Color(255,175,140));
      setSquare(4,Color(255,175,140));
      setSquare(11,Color(255,175,140));
      setSquare(12,Color(255,175,140));
      switch (counter%4) {
        case 0:
          setSquare(3,Color(255,0,0));
          break;
        case 1:
          setSquare(4,Color(255,0,0));
          break;
        case 2:
          setSquare(11,Color(255,0,0));
          break;
        case 3:
          setSquare(12,Color(255,0,0));
          break;
      }
    }
    if (player2==true) {
      setSquare(2,Color(255,175,140));
      setSquare(5,Color(255,175,140));
      setSquare(10,Color(255,175,140));
      setSquare(13,Color(255,175,140));
      switch ((counter+1)%4) {
        case 0:
          setSquare(2,Color(255,255,0));
          break;
        case 1:
          setSquare(5,Color(255,255,0));
          break;
        case 2:
          setSquare(10,Color(255,255,0));
          break;
        case 3:
          setSquare(13,Color(255,255,0));
          break;
      }
    }
    if (player3==true) {
      setSquare(1,Color(255,175,140));
      setSquare(6,Color(255,175,140));
      setSquare(9,Color(255,175,140));
      setSquare(14,Color(255,175,140));
      switch ((counter+2)%4) {
        case 0:
          setSquare(1,Color(0,255,0));
          break;
        case 1:
          setSquare(6,Color(0,255,0));
          break;
        case 2:
          setSquare(9,Color(0,255,0));
          break;
        case 3:
          setSquare(14,Color(0,255,0));
          break;
      }
    }
    if (player4==true) {
      setSquare(0,Color(255,175,140));
      setSquare(7,Color(255,175,140));
      setSquare(8,Color(255,175,140));
      setSquare(15,Color(255,175,140));
      switch ((counter+3)%4) {
        case 0:
          setSquare(0,Color(0,0,255));
          break;
        case 1:
          setSquare(7,Color(0,0,255));
          break;
        case 2:
          setSquare(8,Color(0,0,255));
          break;
        case 3:
          setSquare(15,Color(0,0,255));
          break;
      }
    }
  
  
  counter++;
  
  delay(50);
}

void buzzOut1() {
  player1 = false;
  
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0||counter==6) {
    setSquare(3,Color(0,0,0));
    setSquare(4,Color(0,0,0));
    setSquare(11,Color(0,0,0));
    setSquare(12,Color(0,0,0));
  }
  
  if (counter==3) {
    setSquare(3,Color(255,0,0));
    setSquare(4,Color(255,0,0));
    setSquare(11,Color(255,0,0));
    setSquare(12,Color(255,0,0));
  }
  
  if (counter==9) {
    mode = 113;
  }
  
  counter++;
}
void buzzOut2() {
  player2 = false;
  
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0||counter==6) {
    setSquare(2,Color(0,0,0));
    setSquare(5,Color(0,0,0));
    setSquare(10,Color(0,0,0));
    setSquare(13,Color(0,0,0));
  }
  
  if (counter==3) {
    setSquare(2,Color(255,255,0));
    setSquare(5,Color(255,255,0));
    setSquare(10,Color(255,255,0));
    setSquare(13,Color(255,255,0));
  }
  
  if (counter==9) {
    mode = 113;
  }
  
  counter++;
}
void buzzOut3() {
  player3 = false;
  
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0||counter==6) {
    setSquare(1,Color(0,0,0));
    setSquare(6,Color(0,0,0));
    setSquare(9,Color(0,0,0));
    setSquare(14,Color(0,0,0));
  }
  
  if (counter==3) {
    setSquare(1,Color(0,255,0));
    setSquare(6,Color(0,255,0));
    setSquare(9,Color(0,255,0));
    setSquare(14,Color(0,255,0));
  }
  
  if (counter==9) {
    mode = 113;
  }
  
  counter++;
}
void buzzOut4() {
  player4 = false;
  
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0||counter==6) {
    setSquare(0,Color(0,0,0));
    setSquare(7,Color(0,0,0));
    setSquare(8,Color(0,0,0));
    setSquare(15,Color(0,0,0));
  }
  
  if (counter==3) {
    setSquare(0,Color(0,0,255));
    setSquare(7,Color(0,0,255));
    setSquare(8,Color(0,0,255));
    setSquare(15,Color(0,0,255));
  }
  
  if (counter==9) {
    mode = 113;
  }
  
  counter++;
}

void win1() {
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(255,0,0));
    }
  }
  else if (counter==3) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,0,0));
    }
  }
  counter++;
  if (counter > 6) {
    counter = 0;
  }
}
void win2() {
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(255,255,0));
    }
  }
  else if (counter==3) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,0,0));
    }
  }
  counter++;
  if (counter > 6) {
    counter = 0;
  }
}void win3() {
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,255,0));
    }
  }
  else if (counter==3) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,0,0));
    }
  }
  counter++;
  if (counter > 6) {
    counter = 0;
  }
}void win4() {
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,0,255));
    }
  }
  else if (counter==3) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,0,0));
    }
  }
  counter++;
  if (counter > 6) {
    counter = 0;
  }
}


void thunder() {
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0||counter==4||counter==8|counter==12||counter==16||counter==20||counter==24||counter==28) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(255,175,140));
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    }
  }
  else if (counter==2||counter==6||counter==10||counter==14||counter==18||counter==22||counter==26||counter==30) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,0,0));
    
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    }
  }
  
  counter++;
  
  if (counter > 45) {
    changeMode(49);
    game();
  }
}

void dance() {
  static int counter;
  
  if (modeChanged==true) {
    counter = 0;
    modeChanged = false;
  }
  
  if (counter==0) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(255,0,0));
    }
    
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }
  else if (counter==20) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(255,255,0));
    }
    
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
  }
  else if (counter==40) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,255,0));
    }
    
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  else if (counter==60) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,0,255));
    }
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
  }
  else if (counter==80) {
    for(int i=0; i<16; i++) {
      setSquare(i,Color(0,0,0));
    }
    setSquare(0,Color(255,0,0));
    setSquare(4,Color(255,0,0));
    setSquare(8,Color(255,0,0));
    setSquare(12,Color(255,0,0));
    
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  else if (counter==100) {
    setSquare(1,Color(255,255,0));
    setSquare(5,Color(255,255,0));
    setSquare(9,Color(255,255,0));
    setSquare(13,Color(255,255,0));
    
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  else if (counter==120) {
    setSquare(2,Color(0,255,0));
    setSquare(6,Color(0,255,0));
    setSquare(10,Color(0,255,0));
    setSquare(14,Color(0,255,0));
    
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }
  else if (counter==140) {
    setSquare(3,Color(0,0,255));
    setSquare(7,Color(0,0,255));
    setSquare(11,Color(0,0,255));
    setSquare(15,Color(0,0,255));
    
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
  }
  else if (counter==160) {
    setSquare(0,Color(0,0,0));
    setSquare(4,Color(0,0,0));
    setSquare(8,Color(0,0,0));
    setSquare(12,Color(0,0,0));
    
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
  }
  else if (counter==180) {
    setSquare(1,Color(0,0,0));
    setSquare(5,Color(0,0,0));
    setSquare(9,Color(0,0,0));
    setSquare(13,Color(0,0,0));
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
  }
  else if (counter==200) {
    setSquare(2,Color(0,0,0));
    setSquare(6,Color(0,0,0));
    setSquare(10,Color(0,0,0));
    setSquare(14,Color(0,0,0));
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
  }
  else if (counter==220) {
    setSquare(3,Color(0,0,0));
    setSquare(7,Color(0,0,0));
    setSquare(11,Color(0,0,0));
    setSquare(15,Color(0,0,0));
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  else if (counter==240) {
    setSquare(0,Color(255,0,0));
    setSquare(7,Color(255,0,0));
    setSquare(8,Color(255,0,0));
    setSquare(15,Color(255,0,0));
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
  }
  else if (counter==260) {
    setSquare(0,Color(0,0,0));
    setSquare(7,Color(0,0,0));
    setSquare(8,Color(0,0,0));
    setSquare(15,Color(0,0,0));
    setSquare(1,Color(255,255,0));
    setSquare(6,Color(255,255,0));
    setSquare(9,Color(255,255,0));
    setSquare(14,Color(255,255,0));
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }
  else if (counter==280) {
    setSquare(1,Color(0,0,0));
    setSquare(6,Color(0,0,0));
    setSquare(9,Color(0,0,0));
    setSquare(14,Color(0,0,0));
    setSquare(2,Color(0,255,0));
    setSquare(5,Color(0,255,0));
    setSquare(10,Color(0,255,0));
    setSquare(13,Color(0,255,0));
    
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  else if (counter==300) {
    setSquare(2,Color(0,0,0));
    setSquare(5,Color(0,0,0));
    setSquare(10,Color(0,0,0));
    setSquare(13,Color(0,0,0));
    setSquare(3,Color(0,0,255));
    setSquare(4,Color(0,0,255));
    setSquare(11,Color(0,0,255));
    setSquare(12,Color(0,0,255));
    
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
  }
  
  counter++;
  
  if (counter > 320) {
    counter = 0;
  }
  
}

//************************************************ Util Functions ************************************************//
/***************** changeMode *****************\
| This funation changes the mode of the lighs. |
\**********************************************/
void changeMode(int newMode) {
  mode = newMode;
  modeChanged = true;
}

/*void setSquare(byte square, uint32_t colorz) {
  dayshade.setPixelColor(square,colorz);
}*/

void setSquare(byte square, uint32_t colorz) {
  for(int i = 0; i < 8; i++) {
    dayshade.setPixelColor(pixelz[square][i],colorz);
  }
}
  
/***************** Color *****************\
| Create a 24 bit color value from R,G,B. |
\*****************************************/
uint32_t Color(byte r, byte g, byte b)
{
  uint32_t c;
  c = r;
  c <<= 8;
  c |= g;
  c <<= 8;
  c |= b;
  return c;
}
/********************** Wheel **********************\
| Input a value 0 to 255 to get a color value.      |
| The colours are a transition r - g -b - back to r |
\***************************************************/
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
   WheelPos -= 85;
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170; 
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
