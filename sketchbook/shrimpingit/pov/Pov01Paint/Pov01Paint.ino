// Font: commodore_64_pixelised
// 528 bytes
byte fontHeight = 8;
int fontOffsets[] = {
/*EXCLAMATION*/ 16, /*"*/ 48, /*#*/ 64, /*$*/ 48, /*%*/ 48, /*&*/ 56, /*'*/ 32, /*(*/ 32, /*)*/ 32, /***/ 64, /*+*/ 48, /*,*/ 24, /*-*/ 48, /*STOP*/ 16, /*FWDSLASH*/ 56, /*0*/ 48, /*1*/ 48, /*2*/ 48, /*3*/ 48, /*4*/ 56, /*5*/ 48, /*6*/ 48, /*7*/ 48, /*8*/ 48, /*9*/ 48, /*:*/ 16, /*;*/ 24, /*<*/ 48, /*=*/ 48, /*>*/ 48, /*QUESTION*/ 48, /*@*/ 48, /*A*/ 48, /*B*/ 48, /*C*/ 48, /*D*/ 48, /*E*/ 48, /*F*/ 48, /*G*/ 48, /*H*/ 48, /*I*/ 32, /*J*/ 48, /*K*/ 48, /*L*/ 48, /*M*/ 56, /*N*/ 48, /*O*/ 48, /*P*/ 48, /*Q*/ 48, /*R*/ 48, /*S*/ 48, /*T*/ 48, /*U*/ 48, /*V*/ 48, /*W*/ 56, /*X*/ 48, /*Y*/ 48, /*Z*/ 48, /*[*/ 32, /*BACKSLASH*/ 56, /*]*/ 32, /*^*/ 48, /*_*/ 64, /*FWDAPOS*/ 32, /*a*/ 48, /*b*/ 48, /*c*/ 40, /*d*/ 48, /*e*/ 48, /*f*/ 40, /*g*/ 48, /*h*/ 48, /*i*/ 32, /*j*/ 32, /*k*/ 48, /*l*/ 32, /*m*/ 56, /*n*/ 48, /*o*/ 48, /*p*/ 48, /*q*/ 48, /*r*/ 48, /*s*/ 48, /*t*/ 48, /*u*/ 48, /*v*/ 48, /*w*/ 56, /*x*/ 48, /*y*/ 48, /*z*/ 48, /*{*/ 48, /*|*/ 16, /*}*/ 48, 0 
};

byte fontBytes[] = {
/*EXCLAMATION*/ 95, 95, 
/*"*/ 3, 3, 0, 0, 3, 3, 
/*#*/ 20, 127, 127, 20, 20, 127, 127, 20, 
///*$*/ 36, 46, 107, 107, 58, 18, 
/*$ [smilie] */ 16,34,40,104,42,16,
///*$ [heart] */ 144, 87, 61, 61, 87, 144,
///*$ [snail] */ 128,128,192,252,254,195,219,227,223,195,254,252,192,255,124,15,
///*$ [butterfly] */ 148,206,111,127,62,28,25,254,254,25,28,62,127,111,206,148,
/*%*/ 99, 51, 24, 12, 102, 99, 
/*&*/ 50, 127, 77, 77, 119, 114, 80, 
/*'*/ 4, 6, 3, 1, 
/*(*/ 28, 62, 99, 65, 
/*)*/ 65, 99, 62, 28, 
/***/ 8, 42, 62, 28, 28, 62, 42, 8, 
/*+*/ 8, 8, 62, 62, 8, 8, 
/*,*/ 128, 224, 96, 
/*-*/ 8, 8, 8, 8, 8, 8, 
/*STOP*/ 96, 96, 
/*FWDSLASH*/ 64, 96, 48, 24, 12, 6, 2, 
/*0*/ 62, 127, 73, 69, 127, 62, 
/*1*/ 64, 68, 127, 127, 64, 64, 
/*2*/ 98, 115, 81, 73, 79, 70, 
/*3*/ 34, 99, 73, 73, 127, 54, 
/*4*/ 24, 24, 20, 22, 127, 127, 16, 
/*5*/ 39, 103, 69, 69, 125, 57, 
/*6*/ 62, 127, 73, 73, 123, 50, 
/*7*/ 3, 3, 121, 125, 7, 3, 
/*8*/ 54, 127, 73, 73, 127, 54, 
/*9*/ 38, 111, 73, 73, 127, 62, 
/*:*/ 99, 99, 
/*;*/ 128, 227, 99, 
/*<*/ 8, 28, 54, 99, 65, 65, 
/*=*/ 20, 20, 20, 20, 20, 20, 
/*>*/ 65, 65, 99, 54, 28, 8, 
/*QUESTION*/ 2, 3, 81, 89, 15, 6, 
/*@*/ 62, 127, 65, 77, 79, 46, 
/*A*/ 124, 126, 11, 11, 126, 124, 
/*B*/ 127, 127, 73, 73, 127, 54, 
/*C*/ 62, 127, 65, 65, 99, 34, 
/*D*/ 127, 127, 65, 99, 62, 28, 
/*E*/ 127, 127, 73, 73, 65, 65, 
/*F*/ 127, 127, 9, 9, 1, 1, 
/*G*/ 62, 127, 65, 73, 123, 58, 
/*H*/ 127, 127, 8, 8, 127, 127, 
/*I*/ 65, 127, 127, 65, 
/*J*/ 32, 96, 65, 127, 63, 1, 
/*K*/ 127, 127, 28, 54, 99, 65, 
/*L*/ 127, 127, 64, 64, 64, 64, 
/*M*/ 127, 127, 6, 12, 6, 127, 127, 
/*N*/ 127, 127, 14, 28, 127, 127, 
/*O*/ 62, 127, 65, 65, 127, 62, 
/*P*/ 127, 127, 9, 9, 15, 6, 
/*Q*/ 30, 63, 33, 97, 127, 94, 
/*R*/ 127, 127, 25, 57, 111, 70, 
/*S*/ 38, 111, 73, 73, 123, 50, 
/*T*/ 1, 1, 127, 127, 1, 1, 
/*U*/ 63, 127, 64, 64, 127, 63, 
/*V*/ 31, 63, 96, 96, 63, 31, 
/*W*/ 127, 127, 48, 24, 48, 127, 127, 
/*X*/ 99, 119, 28, 28, 119, 99, 
/*Y*/ 7, 15, 120, 120, 15, 7, 
/*Z*/ 97, 113, 89, 77, 71, 67, 
/*[*/ 127, 127, 65, 65, 
/*BACKSLASH*/ 2, 6, 12, 24, 48, 96, 64, 
/*]*/ 65, 65, 127, 127, 
/*^*/ 4, 6, 127, 127, 6, 4, 
/*_*/ 64, 64, 64, 64, 64, 64, 64, 64, 
/*FWDAPOS*/ 1, 3, 6, 4, 
/*a*/ 32, 116, 84, 84, 124, 120, 
/*b*/ 126, 126, 72, 72, 120, 48, 
/*c*/ 56, 124, 68, 68, 68, 
/*d*/ 48, 120, 72, 72, 126, 126, 
/*e*/ 56, 124, 84, 84, 92, 24, 
/*f*/ 8, 124, 126, 10, 10, 
/*g*/ 152, 188, 164, 164, 252, 124, 
/*h*/ 127, 127, 4, 4, 124, 120, 
/*i*/ 68, 125, 125, 64, 
/*j*/ 128, 128, 250, 122, 
/*k*/ 127, 127, 16, 56, 104, 64, 
/*l*/ 65, 127, 127, 64, 
/*m*/ 124, 124, 24, 56, 28, 124, 120, 
/*n*/ 124, 124, 4, 4, 124, 120, 
/*o*/ 56, 124, 68, 68, 124, 56, 
/*p*/ 252, 252, 36, 36, 60, 24, 
/*q*/ 24, 60, 36, 36, 252, 252, 
/*r*/ 124, 124, 4, 4, 12, 8, 
/*s*/ 72, 92, 84, 84, 116, 36, 
/*t*/ 4, 4, 62, 126, 68, 68, 
/*u*/ 60, 124, 64, 64, 124, 124, 
/*v*/ 28, 60, 96, 96, 60, 28, 
/*w*/ 28, 124, 112, 56, 112, 124, 28, 
/*x*/ 68, 108, 56, 56, 108, 68, 
/*y*/ 156, 188, 160, 224, 124, 60, 
/*z*/ 68, 100, 116, 92, 76, 68, 
/*{*/ 8, 8, 62, 119, 65, 65, 
/*|*/ 127, 127, 
/*}*/ 65, 65, 119, 62, 8, 8,  0 
};

int numSides = 4; //the number of sides in the tilt switch
int tiltPins[] = {8,7,5,6}; //listed in clockwise direction
int numLights = 8;
int povPins[] = {9,10,11,12,A1,A2,A3,A4};

int columnDelay = 2;
int spaceCols = 4;

String message ="HACK $";

void drawMessage(){
  
  for(int letterPos = 0; letterPos < message.length(); letterPos++){

    //use ascii charcode to index font information starting with 33 = first printable char
    int fontPos = int(message.charAt(letterPos)) - 33;
    
    //draw space or letter
    if(fontPos == -1){
      //it's a space
      drawSpace();
    }
    else{
      //it's a printable character. draw it
      drawCharacter(fontPos);
    }
    
    //draw a single pixel space between each character of message
    drawBlankCol();
  }  
}

void drawBlankCol(){
    for(int row = 0; row < fontHeight; row++){
      digitalWrite(povPins[row],LOW);
    }
    delay(columnDelay);
}

void drawSpace(){
  for(int col = 0; col < spaceCols; col++){
    drawBlankCol();
  }
}

void drawCharacter(int fontPos){
  int startBit = fontOffsets[fontPos]; //first bit of character
  int endBit = fontOffsets[fontPos + 1]; //start of next char (or dummy char at end)
  
  for(int colStart = startBit; colStart < endBit; colStart += fontHeight){
    for(int row = 0; row < fontHeight; row++){
      //calculate the bit position
      int bitPos = colStart + row;
      int byteOffset = bitPos / 8;
      int bitOffset = bitPos % 8;
      //read the individual bit
      if(((fontBytes[byteOffset]) & (1 << bitOffset)) == 0){ 
        digitalWrite(povPins[row], LOW);
      }
      else{
        digitalWrite(povPins[row], HIGH);
      }
    }
    delay(columnDelay); //wait between columns
  }
}


/** Configure input and output pins corresponding with each tilt direction to begin. */
void setup(){
  
  Serial.begin(9600);
  Serial.println(message);
  
  for(int side = 0; side < numSides; side++){    
    //configure tilt pins as input and set high resistance
    pinMode(tiltPins[side],INPUT);
    digitalWrite(tiltPins[side],LOW);
  }
  
  for(int light = 0; light < numLights; light++){
    //configure lights as output and turn off
    pinMode(povPins[light], OUTPUT);
    digitalWrite(povPins[light],LOW);
  }
  
  //translate offsets from relative (character width) into absolute (cumulative width so far)
  int numOffsets = sizeof(fontOffsets) / sizeof(int);
  int bitCount = 0;
  for(int offsetIdx = 0; offsetIdx < numOffsets; offsetIdx++){
    int charWidth = fontOffsets[offsetIdx]; 
    fontOffsets[offsetIdx] = bitCount;
    bitCount += charWidth;
  }
  
}

/** visit each side in turn to check if it's connected
* and display each direction using different LEDs
*/
void loop(){
  //int tilt = getTilt();
  drawMessage();
}

int getTilt(){
 for(int side = 0; side < numSides; side++){
   if(checkTilted(side)){
     return side;
   }
 } 
 return -1;
}

/** Configures each pin in turn as a button (with pull-up resistor) and a neighbour as ground.
* Then checks to see if the 'button' is closed (e.g. the coin is connecting the pins).
*/
boolean checkTilted(int focusPos){
  
  int focusPin = tiltPins[focusPos];
  
  //configure lower neighbour as high resistance (Z)
  int lowerPin = tiltPins[wrap(focusPos-1,numSides)]; //the previous pin (neighbour in anti-clockwise direction) 
  pinMode(lowerPin,INPUT);
  digitalWrite(lowerPin,LOW);

  //configure upper neighbour as output to ground (sink)
  int upperPin = tiltPins[wrap(focusPos+1,numSides)]; //the next pin (neighbour in clockwise direction)
  pinMode(upperPin, OUTPUT);
  digitalWrite(upperPin,LOW);

  //configure focus pin as input with pull-up resistor
  pinMode(focusPin, INPUT);
  digitalWrite(focusPin, HIGH);
  
  return digitalRead(focusPin) == LOW;
  
}

/** Keeps a value within bounds when overflowing or underflowing, 
* so that incrementing or decrementing a number stays in bounds. 
* (workaround for the fact that % in C isn't a mathematical modulus and behaves weird with negative numbers) */
int wrap(int value, int upperBound){
  return value < 0 ? ((value % upperBound) + upperBound) % upperBound : value % upperBound;
}
