/** Accesses the 8 bits of a byte to see which of the 8 lights it should turn on.
* Try changing the 8 bits of the byte (named 'pattern') 
* and hit upload to see what happens.
*/

byte pattern = 0b10101010;

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

  //inspect the bits in the byte 'pattern' to  
  //turn on selected LEDs
  digitalWrite(9,    (pattern & 0b00000001) != 0);
  digitalWrite(10,   (pattern & 0b00000010) != 0); 
  digitalWrite(11,   (pattern & 0b00000100) != 0); 
  digitalWrite(12,   (pattern & 0b00001000) != 0); 
  digitalWrite(A1,   (pattern & 0b00010000) != 0); 
  digitalWrite(A2,   (pattern & 0b00100000) != 0); 
  digitalWrite(A3,   (pattern & 0b01000000) != 0); 
  digitalWrite(A4,   (pattern & 0b10000000) != 0); 
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
