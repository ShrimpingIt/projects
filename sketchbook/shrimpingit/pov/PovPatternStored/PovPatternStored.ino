
/*
  PovStoredPattern
  Uses a stored number between 0 and 255 to flash a set of 8 LEDs in a pattern
  LEDS are attached to Arduino Pin 9,10,11,12,A1,A2,A3,A4
  see http://start.shrimping.it/project/pov/build.html
 */
 
int stored = 255;
 
// the setup routine runs once when you press reset:
void setup() {                
  // initialize digital pins as outputs
  pinMode(9, OUTPUT);     
  pinMode(10, OUTPUT);     
  pinMode(11, OUTPUT);     
  pinMode(12, OUTPUT);     
  pinMode(A1, OUTPUT);     
  pinMode(A2, OUTPUT);     
  pinMode(A3, OUTPUT);     
  pinMode(A4, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {

  //show the lights for a millisecond
  
  //decide which lights are on, by finding which binary 'bits' are in the number
  
  //make a copy of the stored pattern 
  //we will throw bits of the number away but
  //we want to keep the stored pattern for the next time
  int remaining = stored; 
  
  if(remaining > 128){ //is the 128 'bit' set?
    digitalWrite(9,   1); //if it is, turn on that LED
    remaining = remaining - 128; //...throw away that 'bit' of the number
  }
  if(remaining > 64){ //look at the next 'bit' of the number to control the next LED
    digitalWrite(10,   1);
    remaining = remaining - 64; 
  }
  if(remaining > 32){ //keep going until all the LEDs are on or off according to the value of 'stored'
    digitalWrite(11,   1);
    remaining = remaining - 32; 
  }
  if(remaining > 16){
    digitalWrite(12,   1);
    remaining = remaining - 16; 
  }
  if(remaining > 8){
    digitalWrite(A1,   1);
    remaining = remaining - 8; 
  }
  if(remaining > 4){
    digitalWrite(A2,   1);
    remaining = remaining - 4; 
  }
  if(remaining > 2){
    digitalWrite(A3,   1);
    remaining = remaining - 2; 
  }
  if(remaining > 1){
    digitalWrite(10,   1);
    remaining = remaining - 1; 
  }  
  delay(1);
  
  //then turn the LEDs off for a millisecond to let them cool
  digitalWrite(9,   0);
  digitalWrite(10, 0);
  digitalWrite(11, 0);
  digitalWrite(12, 0);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  digitalWrite(A3, 0);
  digitalWrite(A4, 0);
  delay(1);
  
}
