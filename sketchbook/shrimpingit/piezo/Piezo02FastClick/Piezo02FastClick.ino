/* FastClick uses Microsecond timing so that it can produce
* tones with a higher frequency than Click, which is limited to 500Hz
* See https://github.com/ShrimpingIt/projects/tree/master/sketchbook/shrimpingit/piezo for the other examples in this series
*/

// Pin 6 (see https://www.arduino.cc/en/Hacking/PinMapping168 ) should have a piezoPin
// attached through a series resistor to ground in order to make this work.
// store the number 6 with the name piezoPin
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
