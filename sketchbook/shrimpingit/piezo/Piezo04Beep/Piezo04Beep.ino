/* Beep uses a library function called tone() instead of explicitly clicking the Piezo,
* like the previous sketches in the series. The tone() function is told the frequency to
* generate, and then employs the 'timer interrupt' capability of the ATMEGA328, to look
* after the clicking behaviour 'in parallel', while your sketch carries out other operations.
* See https://github.com/ShrimpingIt/projects/tree/master/sketchbook/shrimpingit/piezo for the other examples in this series
*/

// Pin 6 (see https://www.arduino.cc/en/Hacking/PinMapping168 ) should have a piezoPin
// attached through a series resistor to ground in order to make this work.
// store the number 6 with the name piezoPin
void setup(){
  pinMode(6,OUTPUT);
}

void loop(){
  tone(6, 4000);
  delay(1000);
  noTone(6);
  delay(1000);

  while(millis() > 10000){ //after 10 seconds, stays in this loop, silenced
      //do nothing
  }

}
