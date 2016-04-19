/** Controls the lights with a pattern value just like before, but using a 
 *  'while loop' to visit a sequence of pins
*/

byte pattern = 0b10101010;
byte empty   = 0b00000000;

int pinNumbers[] = { 9,10,11,12,A1,A2,A3,A4 };

int bitCounter;
int bitValue;

// this sequence of steps is triggered when you reboot the microcontroller:
void setup() {

  bitCounter = 0;
  
  while(bitCounter < 8){
    pinMode(pinNumbers[bitCounter], OUTPUT); // initialize pin as output
    bitCounter = bitCounter + 1;
  }
}

// the loop routine runs over and over again forever:
void loop() {
  setLights(pattern);
  delay(1);
  setLights(empty);
  delay(2);
}

void setLights(byte pattern){
  
  bitCounter = 0;
  bitValue = 1;
  
  while(bitCounter < 8){
    digitalWrite(pinNumbers[bitCounter], (pattern & bitValue) != 0); //turn on the LED if the 'pattern' value has that bit set  
    bitCounter = bitCounter + 1;
    bitValue = bitValue * 2;
  }
}

