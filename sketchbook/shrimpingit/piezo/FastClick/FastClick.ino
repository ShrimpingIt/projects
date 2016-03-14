/* Click creates a sound by flexing a PiezoElectric Transducer (attached to Arduino Digital Pin 6)
 */
 
// Pin 6 (see https://www.arduino.cc/en/Hacking/PinMapping168 ) should have a piezoPin attached through a series resistor to ground in order to make this work.
// give it a name:
int piezoPin = 6;
int clickDelay = 10000;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(piezoPin, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(piezoPin, HIGH);   // turn the piezoPin on (HIGH is the voltage level)
  delayMicroseconds(clickDelay);               // wait for a second
  digitalWrite(piezoPin, LOW);   // turn the piezoPin on (HIGH is the voltage level)
  delayMicroseconds(clickDelay);               // wait for a second
}
