
/*
  PovFixedPattern
  Flashes a set of 8 LEDs in a pattern
  LEDS are attached to Arduino Pin 9,10,11,12,A1,A2,A3,A4
  see http://start.shrimping.it/project/pov/build.html
 */
 
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

  //turn some LEDs on
  digitalWrite(9,   1);   //to turn the LED on pin 9 off,  use digitalWrite(9, 0);
  digitalWrite(10, 0);
  digitalWrite(11, 1);
  digitalWrite(12, 0);
  digitalWrite(A1, 1);
  digitalWrite(A2, 0);
  digitalWrite(A3, 1);
  digitalWrite(A4, 0);
  delay(1000);
  
  //leave all LEDs off for a period
  digitalWrite(9,   0);
  digitalWrite(10, 1);
  digitalWrite(11, 0);
  digitalWrite(12, 1);
  digitalWrite(A1, 0);
  digitalWrite(A2, 1);
  digitalWrite(A3, 0);
  digitalWrite(A4, 1);
  delay(1000);
  
}
