/* Click creates a sound by flexing a PiezoElectric Transducer (attached to Arduino Digital Pin 6)
 */
 
// Pin 6 (see https://www.arduino.cc/en/Hacking/PinMapping168 ) should have a piezoPin attached through a series resistor to ground in order to make this work.
// give it a name:
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
