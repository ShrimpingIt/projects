/** This sequence should paint a minimised @ShrimpingIt Logo in the air 
* [see http://shrimping.it ]. 
* Even better with Orange LEDs
*/

byte patternSequence[] = {
  0b00100100,
  0b00111100,
  0b00011000,
  0b00111100,
  0b00011000,
  0b01111110,
  0b00011000,
  0b01111110,
  0b00011000,
  0b00011000,
  0b00100100,
  0b01000010,
  0b10000001,
  0b10000001,
  0b10000001,
};
byte allZeroes = 0x00000000;

int totalPatterns = 15;
int patternCounter;

int totalBits = 8;
int bitCounter;
int bitValue;

int pinNumbers[] = { 9,10,11,12,A1,A2,A3,A4 };

// this sequence of steps is triggered when you reboot the microcontroller:
void setup() {

  bitCounter = 0;
  
  while(bitCounter < totalBits){
    pinMode(pinNumbers[bitCounter], OUTPUT); // initialize a pin as output
    bitCounter = bitCounter + 1;
  }
}

// the loop routine runs over and over again forever:
void loop() {
  patternCounter = 0;
  
  while(patternCounter < totalPatterns){
    setLights(patternSequence[patternCounter]);
    delay(2);
    patternCounter = patternCounter + 1;
  }
  
  setLights(allZeroes);
  delay(12);
}

void setLights(byte pattern){
  
  bitCounter = 0;
  bitValue = 0b00000001;
  
  while(bitCounter < totalBits){
    digitalWrite(pinNumbers[bitCounter], (pattern & bitValue) != 0); //turn on the LED if the 'pattern' value has that bit set  
    bitCounter = bitCounter + 1;
    bitValue = bitValue * 2;
  }

}
