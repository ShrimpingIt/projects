#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

#define SERIAL_RATE 9600

DateTime defaultTime = DateTime(2016, 3, 21, 02, 45, 0);
DateTime time;
DateTime prevTime;

int upButtonPin   = 7; 
int downButtonPin = 8;
long adjustmentSeconds;

void setup(){
  
  pinMode(upButtonPin,   INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);
  
  Serial.begin(SERIAL_RATE);
  Wire.begin();
  rtc.begin();
  
  if(!setClock()){
    Serial.println("Clock has been set");    
  }
  
  time = rtc.now();
  Serial.print("Date: ");
  Serial.print(time.year(), DEC);
  Serial.print('-');
  Serial.print(time.month(), DEC);
  Serial.print('-');
  Serial.print(time.day(), DEC);
  Serial.println();
  prevTime = time;
}

void loop(){
  
  time = rtc.now();
  
  if(digitalRead(upButtonPin) == LOW){
    rtc.adjust(time + TimeSpan(adjustmentSeconds));  
    adjustmentSeconds = adjustmentSeconds + 1;
  }
  else if(digitalRead(downButtonPin) == LOW){
    rtc.adjust(time - TimeSpan(adjustmentSeconds));
    adjustmentSeconds = adjustmentSeconds + 1;
  }
  else{
      adjustmentSeconds = 1;
  }
  
  if(time.unixtime() != prevTime.unixtime()){
    
    Serial.print("Time: ");
    Serial.print(time.hour(), DEC);
    Serial.print(':');
    Serial.print(time.minute(), DEC);
    Serial.print(':');
    Serial.print(time.second(), DEC);
    Serial.println();
  
    prevTime=time;
    
  }
  
  delay(50);
  
}

/** Check the Clock chip's memory to check it was previously set to the desired time. 
* If the clock hadn't been set,  then set it. 
* return true if the clock needed setting, otherwise return false. */
boolean setClock(){
  long timeSet;
  byte memoryLocation = 0;
  rtc.readnvram((byte*)&timeSet, sizeof(long), memoryLocation);
  if(timeSet != defaultTime.unixtime()){
    timeSet = defaultTime.unixtime();
    rtc.writenvram(memoryLocation, (byte*)&timeSet, sizeof(long));
    rtc.adjust(defaultTime);
    return true;
  }
  else{
    return false;
  }
}
