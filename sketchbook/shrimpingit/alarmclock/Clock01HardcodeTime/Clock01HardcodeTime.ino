#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

#define SERIAL_RATE 9600

void setup(){
  Serial.begin(SERIAL_RATE);
  Wire.begin();
  rtc.begin();
  
  DateTime now = rtc.now();
  if(!rtc.isrunning() || now.year() == 2099){ 
    //time never set since powering RTC chip
    //set it to a hard-coded time
    rtc.adjust(DateTime(2016, 3, 21, 01, 24, 0));  
  }
  
}

void loop(){
  delay(1000);
  printIsoDateTime();
}

/** Prints a dateTime conforming to ISO8601. */ 
void printIsoDateTime(){
    DateTime now = rtc.now();    
    Serial.print(now.year(), DEC);
    Serial.print('-');
    Serial.print(now.month(), DEC);
    Serial.print('-');
    Serial.print(now.day(), DEC);
    Serial.print('T');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}
