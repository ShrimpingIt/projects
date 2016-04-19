//defines a list of the columns making up the font, and a lookup table giving the width in columns of each ASCII character

#include "Commodore64.h"
//#include "SG05.h"

//adds up the widths of characters, and saves the absolute positions of the first column of that character
#include "FontColumns.h"

String message = "$ HACK";

byte allZeroes = 0x00000000;

int bitCounter;
int bitValue;

int pinNumbers[] = { 9, 10, 11, 12, A1, A2, A3, A4 };

int columnDuration = 2;

// this sequence of steps is triggered when you reboot the microcontroller:
void setup() {

  calculateFontColumns();

  bitCounter = 0;

  while (bitCounter < 8) {
    pinMode(pinNumbers[bitCounter], OUTPUT); // initialize a pin as output
    bitCounter = bitCounter + 1;
  }

}

// the loop routine runs over and over again forever:
void loop() {

  int messagePosition = 0;

  while (messagePosition < message.length()) {

    byte asciiCharacter = message.charAt(messagePosition);
    int width = getNumColumns(asciiCharacter);

    int columnIndex = 0;
    while (columnIndex < width) {
      byte pattern = getFontPattern(asciiCharacter, columnIndex);
      setLights(pattern);
      delay(columnDuration);
      columnIndex = columnIndex + 1;
    }
      
    //create a gap between each character in the message
    setLights(allZeroes);
    delay(columnDuration);

    messagePosition = messagePosition + 1;

  }

}

void setLights(byte pattern) {

  bitCounter = 0;
  bitValue = 0b00000001;

  while (bitCounter < 8) {
    digitalWrite(pinNumbers[bitCounter], (pattern & bitValue) != 0); //turn on the LED if the 'pattern' value has that bit set
    bitCounter = bitCounter + 1;
    bitValue = bitValue * 2;
  }

}
