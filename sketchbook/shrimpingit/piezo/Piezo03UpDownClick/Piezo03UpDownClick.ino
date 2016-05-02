/* UpDownClick adds two buttons as inputs, to complement the Piezo output.
* It includes logic to change the pitch of the tone by using the buttons as
* Up and Down controls.
* See https://github.com/ShrimpingIt/projects/tree/master/sketchbook/shrimpingit/piezo for the other examples in this series
*/

// Pin 6 (see https://www.arduino.cc/en/Hacking/PinMapping168 ) should have a piezoPin
// attached through a series resistor to ground in order to make this work.
// store the number 6 with the name piezoPin
int piezoPin = 6;
int upPin = 7;
int downPin = 8;

int clickDelay = 10000;
int delayStep = 48;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(piezoPin, OUTPUT);
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(piezoPin, HIGH);   // turn the piezoPin on (HIGH is the voltage level)
  delayMicroseconds(clickDelay);               // wait for a second
  digitalWrite(piezoPin, LOW);   // turn the piezoPin on (HIGH is the voltage level)
  delayMicroseconds(clickDelay);               // wait for a second

  if(digitalRead(upPin)==LOW){
    if(clickDelay < 16383 - delayStep){
      clickDelay = clickDelay + delayStep;
    }
  }

  if(digitalRead(downPin)==LOW){
    if(clickDelay > 0 + delayStep){
      clickDelay = clickDelay - delayStep;
    }
  }

}
