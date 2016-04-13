/** Configures 8 LEDs as outputs, then flashes them so fast you can't see them turn off.
* 
* digitalWrite(9, true)  instructs Arduino Pin 9 to turn on.
* digitalWrite(9, false) instructs Arduino Pin 9 to turn off.
* 
* Try changing the true and false values in the loop() routine 
* and hit upload to see what happens.
*/

// this sequence of steps is triggered when you reboot the microcontroller:
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

// this sequence of steps is triggered over and over again forever:
void loop() {

  //turn on selected LEDs
  digitalWrite(9,  true );
  digitalWrite(10, false); 
  digitalWrite(11, true ); 
  digitalWrite(12, false); 
  digitalWrite(A1, true ); 
  digitalWrite(A2, false); 
  digitalWrite(A3, true ); 
  digitalWrite(A4, false); 
  delay(1);
  
  //turn all the LEDs off for a bit to let them cool down
  digitalWrite(9,  false);
  digitalWrite(10, false);
  digitalWrite(11, false);
  digitalWrite(12, false);
  digitalWrite(A1, false);
  digitalWrite(A2, false);
  digitalWrite(A3, false);
  digitalWrite(A4, false);
  delay(2);
  
}
