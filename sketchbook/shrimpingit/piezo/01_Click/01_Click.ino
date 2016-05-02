/* Click creates a sound by flexing a PiezoElectric Transducer (attached to Arduino Digital Pin 6)
* It will be very quiet, but if you put your ear near the circuit, you will hear a click as the
* voltage changes once a second. Adjust the delays to hear the difference. Because the delays
* are in milliseconds, the fastest you can click is 1000 times a second, equivalent to a 500Hz tone
* See https://github.com/ShrimpingIt/projects/tree/master/sketchbook/shrimpingit/piezo for the other examples in this series
*/

// Pin 6 (see https://www.arduino.cc/en/Hacking/PinMapping168 ) should have a piezoPin
// attached through a series resistor to ground in order to make this work.
// store the number 6 with the name piezoPin
int piezoPin = 6;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(piezoPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(piezoPin, HIGH);   // turn the piezoPin on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(piezoPin, LOW);   // turn the piezoPin on (HIGH is the voltage level)
  delay(1000);               // wait for a second
}
