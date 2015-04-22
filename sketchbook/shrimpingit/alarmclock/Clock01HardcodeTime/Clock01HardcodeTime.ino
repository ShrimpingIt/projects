#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

#define SERIAL_RATE 9600

void setup(){
  Serial.begin(SERIAL_RATE);
  Wire.begin();
  rtc.begin();
  
  if(!rtc.isrunning()){ 
    //if time never set since powering RTC chip
    //then set it to a hard-coded time
    rtc.adjust(DateTime(2015, 4, 13, 10, 30, 0));  
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
