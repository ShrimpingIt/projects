#include "UsbKeyboard.h"

//keys next to shift on 'imaginary keyboard'
char leftKeyCode = 86;
char rightKeyCode = 53;

unsigned long leftScheduledMs =  10000;
unsigned long rightScheduledMs = 15000;

void setup(){
}
  
void loop() {
  UsbKeyboard.update();
  delayMicroseconds(20000);

  if(leftScheduledMs != 0 && millis() > leftScheduledMs){
    leftScheduledMs = 0;
    UsbKeyboard.sendKeys(leftKeyCode, 0);
    delay(100);
    UsbKeyboard.sendKeys(0, 0);    
  }

  if(rightScheduledMs != 0 && millis() > rightScheduledMs){
    rightScheduledMs = 0;
    UsbKeyboard.sendKeys(rightKeyCode, 0);
    delay(100);
    UsbKeyboard.sendKeys(0, 0);    
  }

}
