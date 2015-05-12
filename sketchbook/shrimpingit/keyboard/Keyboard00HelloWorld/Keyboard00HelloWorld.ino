#include "UsbKeyboard.h"

void setup(){
}
  
void loop() {
  for(int i = 0; i < 500; i++){
    UsbKeyboard.update();
    delayMicroseconds(20000);
  }
    
  UsbKeyboard.sendKeys(KEY_H,0);
  UsbKeyboard.sendKeys(KEY_E,0);
  UsbKeyboard.sendKeys(KEY_L,0);
  UsbKeyboard.sendKeys(KEY_L,0);
  UsbKeyboard.sendKeys(KEY_O,0);

  UsbKeyboard.sendKeys(KEY_SPACE,0);

  UsbKeyboard.sendKeys(KEY_W,0);
  UsbKeyboard.sendKeys(KEY_O,0);
  UsbKeyboard.sendKeys(KEY_R,0);
  UsbKeyboard.sendKeys(KEY_L,0);
  UsbKeyboard.sendKeys(KEY_D,0);

  UsbKeyboard.sendKeys(KEY_ENTER,0);
    
}
