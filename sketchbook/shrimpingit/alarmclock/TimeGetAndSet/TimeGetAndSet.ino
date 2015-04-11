#include <Wire.h>
#include "RTClib.h"
#include <Narcoleptic.h>

RTC_DS1307 rtc;

/*
char dayNames[][]={
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

char monthNames[][]={
    "January",
    "February",
    "March",
    "April",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};
*/

#define COMMANDMAX 19

String command = "";
String field = "";

int fieldStart = 0;

void setup(){
  Serial.begin(57600);
  Wire.begin();
  rtc.begin();
  command.reserve(COMMANDMAX + 1); 
  field.reserve(COMMANDMAX + 1);
}

void loop(){
  if(Serial.available()){
    char nextChar = Serial.read();
    if(nextChar != '\n'){
      command += nextChar;
    }
    else{
      processCommand();
    }
  }
}

void processCommand(){
  
  int year,month,day,hour,minute,second;
     
  fieldStart = 0;
  
  //try to parse an ISO 8601 date fragment
   
  year = nextIntField('-');
  if(year != -1){
    month = nextIntField('-');
    day = nextIntField('T');
    if(day == -1){
      day = remainingIntField();
    }      
    setDate(year, month, day);
  }

  //try to parse an ISO 8601 time fragment

  hour = nextIntField(':');
  if(hour != -1){
    minute = nextIntField(':');
    if(minute == -1){
      minute = remainingIntField();
      second = 0;
    }
    else{
      second = remainingIntField();      
    }
    setTime(hour, minute, second);
  }
  
  //always print out the date and time (sending just newline reports time)
  printTime();

  command = "";

}

int nextIntField(char terminator){
  int fieldEnd = command.indexOf(terminator, fieldStart);
  if(fieldEnd != -1){
    field = command.substring(fieldStart,fieldEnd);
    fieldStart = fieldEnd + 1;
    int value = field.toInt();
    return value;
  }
  else{
    return -1;
  }
}

int remainingIntField(){
  field = command.substring(fieldStart);
  int value = field.toInt();
  return value;
}


/** Sets both the date and the time */
void setDateTime(  uint16_t year, uint8_t  month, uint8_t  day, uint8_t  hour, uint8_t  minute, uint8_t  second){
  rtc.adjust(DateTime(year, month, day, hour, minute, second));
}

/** Sets only the date */
void setDate(  uint16_t year, uint8_t  month, uint8_t  day){ //changes only the date
  DateTime now = rtc.now();
  setDateTime(year, month, day, now.hour(), now.minute(), now.second());
}

/** Sets only the time */
void setTime(uint8_t  hour, uint8_t  minute, uint8_t  second){ //changes only the time
  DateTime now = rtc.now();
  setDateTime(now.year(), now.month(), now.day(), hour, minute, second);
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
