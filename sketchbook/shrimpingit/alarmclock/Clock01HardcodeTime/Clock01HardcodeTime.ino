#include <Wire.h>
#include "RTClib.h"
#include <Narcoleptic.h>

RTC_DS1307 rtc;

void setup(){
  Serial.begin(9600);

  Wire.begin();
  rtc.begin();
  
  rtc.adjust(DateTime(2015, 4, 13, 10, 30, 0));  
  printTime();

}

void loop(){
}

void printTime(){
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
