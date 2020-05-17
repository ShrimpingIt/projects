#include <Wire.h>
#include "RTClib.h"
#include <rtttl.h>

RTC_DS1307 rtc;

#define SERIAL_RATE 9600

#define NUM_REGISTER_BYTES 4

#define COMMANDMAX 19

String command = "";
String field = "";
int fieldStart = 0;

//See more RTTTL songs at https://github.com/cefn/non-blocking-rtttl-arduino/blob/master/rtttl/examples/ProgmemSong/ProgmemSong.ino
//or look online for your favourite chimes, being careful to remove unnecessary spaces
const char song_P[] PROGMEM = "Wham- Wake Me Up:d=4,o=5,b=300:f#5,2a5,2b5.,p,f#5,2a5,b5,2f#5,2d5,p,d5,e5,2f#5,2g5,f#5,e5,d5,2f#5,a5,2f#5,d5,2p";

ProgmemPlayer player(6);

char* dayName[]={
  "Sunday",  
  "Monday",  
  "Tuesday",  
  "Wednesday",  
  "Thursday",  
  "Friday",  
  "Saturday",  
  "Sunday",  
};

char* monthName[]={
  "",  
  "January",  
  "February",  
  "March",  
  "April",  
  "May",  
  "June",  
  "July",  
  "August",  
  "September",
  "October",  
  "November",  
  "December",
};


byte registerBytes[NUM_REGISTER_BYTES];
const int latchPin = A1;
const int clockPin = A2;
const int dataPin = A3;

//Each of these binary sequences should have 
//an easily distinguishable number of LED lights
int distinctNumbers[] = {
  0b000000000000, //0
  0b100000000000, //1
  0b100000100000, //2
  0b100010001000, //3
  0b100100100100, //4
  0b110001000110, //5
  0b111111000000, //6
  0b111001001110, //7
  0b110110110110, //8
  0b111011101110, //9
  0b101111111101, //10
  0b111111111101, //11
  0b111111111111  //12
};

//these are the assignments of each LED driver
//pin to an hour or minute light
//positive number from 1 to 12 is an hour indicator light
//negative number from -1 to -12 is a minutes indicator light
//zero means do not use
int assignments[] ={
   7,  8, 0,  9, 10, 0, 11, 12,
   -1, -2, 0, -3, -4, 0, -5, -6,
    1,  2, 0,  3,  4, 0,  5,  6,
   -7, -8, 0, -9,-10, 0,-11,-12
};

int brightness = 255;

int alarmHour = 9;
int alarmMinute = 00;

void setup(){
  Serial.begin(SERIAL_RATE);
  Wire.begin();
  rtc.begin();

  //reserve enough string memory for ISO8601 date string like 2015-06-01T12:00:00
  command.reserve(COMMANDMAX + 1); 
  field.reserve(COMMANDMAX + 1);

  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
 
  player.setSong(song_P);
  
  if (rtc.isrunning()) {
    printDateTimeVerbose();
  }
  else{
    Serial.println("Realtime Clock has not yet been set!");
  }  
  
}

void loop(){

  while(Serial.available()){
    char nextChar = Serial.read();
    if(nextChar != '\n'){
      command += nextChar;
    }
    else{
      processCommand();
      command.remove(0);
    }
  }
    
  DateTime now = rtc.now();
  
  showTime(now.hour(), now.minute());
  
  //tune is re-triggered throughout the alarm minute
  while(now.hour() == alarmHour && now.minute() == alarmMinute){
    Serial.print("Playing Alarm Melody at ");
    printDateTimeVerbose();
    player.finishSong();
    now = rtc.now();
  }
    
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


void printDateTimeIso(){
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

void printDateTimeVerbose(){
    DateTime now = rtc.now();

    Serial.print("It's ");
    
    Serial.print(now.hour() % 12 == 0 ? 12 : now.hour() % 12, DEC);
    Serial.print(" ");
    Serial.print(now.minute(), DEC);
    Serial.print(" ");
    Serial.print(now.second(), DEC);
    Serial.print(now.hour() != (now.hour() % 12) ? " pm ": " am ");
    
    Serial.print(" on ");
    
    Serial.print(dayName[now.dayOfWeek()]);
    Serial.print(" the ");
    Serial.print(now.day(), DEC);
    Serial.print(ordinalSuffix(now.day()));
    Serial.print(" of ");
    Serial.print(monthName[now.month()]);
    Serial.print(", ");
    Serial.print(now.year(), DEC);

    Serial.println();
}

char* ordinalSuffix(int number){
  if(number < 4 || number > 20){
    switch(number%10){
      case 1: return "st";
      case 2: return "nd";
      case 3: return "rd";
    }
  }
  return "th";
}

void processCommand(){
  
  int year,month,day,hour,minute,second;
  boolean newDateTime = false;
     
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
    newDateTime = true;
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
    newDateTime = true;
  }
  
  if(newDateTime){
    printDateTimeVerbose();
  }
  else if(command.length() > 0){
    Serial.print("Could not understand: ");
    Serial.println(command);
  }
  
  command.remove(0);
  
}

int nextIntField(char terminator){
  int fieldEnd = command.indexOf(terminator, fieldStart);
  if(fieldEnd != -1){
    field += command.substring(fieldStart,fieldEnd);
    fieldStart = fieldEnd + 1;
    int value = field.toInt();
    field.remove(0);
    return value;
  }
  else{
    return -1;
  }
}

int remainingIntField(){
  field += command.substring(fieldStart);
  int value = field.toInt();
  field.remove(0);
  return value;
}



void showTime(int newHours, int newMins){ 
  //calculate for display
  newHours = newHours % 12; //bounds checking
  newHours = newHours == 0? 12: newHours; //make 0 to be 12
  newMins %= 60; //bounds checking
  newMins /= 5; //12 segments of 5 minuts each
  //send calculated values
  shiftLights(newHours, newMins);
}

/** Given a number to display
* should the LED at a given position be lit? 
* Uses a special distinctNumbers matrix to decide
* (making numbers easier to distinguish visually)
*/
boolean distinctNumberIsLit(int numLights, int pos){
  //inspects an individual bit to se if this hour LED should be lit
  return (distinctNumbers[numLights] & (1 << (11 - pos))) != 0;  
}

boolean rightUnaryIsLit(int numLights, int pos){
  return numLights > pos;
}

boolean leftUnaryIsLit(int numLights, int pos){
  return numLights > (11 - pos);
}

boolean centerUnaryIsLit(int numLights, int pos){
  return abs(pos - 6) <= (numLights / 2);
}

void shiftLights(int showHours, int showMinutes){

  digitalWrite(latchPin,LOW);
    
  int showLights; //count of lights illuminated in the current bank
  int shiftPos; //the current pin which is being written to
  int bytePos; //the current byte being written to
  int bitPos; //the current bit in the current byte being written to
    
  //go through all the pins of both DM134 chips setting high bits to light lights
  for(shiftPos = 0; shiftPos < NUM_REGISTER_BYTES * 8; shiftPos++){
    
    int bytePos = shiftPos / 8;
    int bitPos = shiftPos % 8;
    
    //figure out the assigned role of this pin 
    //value between 1 and 12 (magnitude), and if it's an hour or minute (sign)
    int assignment = assignments[shiftPos];

    byte setBit = 1 << bitPos;
    if(assignment == 0){ //it's not meant to be active (has no LED in this pin)
      //do nothing - bit is already zero
    }
    else {
      if(assignment >= 0){ //positive number indicates an hour light
        assignment = assignment - 1;  //shift to index LEDs from 0 to 11, not 1 to 12
        if(distinctNumberIsLit(showHours, assignment)){
          registerBytes[bytePos] |= setBit;
        }
      }
      else { //negative number indicates a minute light
        assignment = abs(assignment) - 1; //change sign and shift to index LEDs from 0 to 11 not 1 to 12
        if(leftUnaryIsLit(showMinutes, assignment)){
          registerBytes[bytePos] |= setBit;
        }
      }
    }    
        
        
  } 
  
  for(bytePos = 0; bytePos < NUM_REGISTER_BYTES; bytePos++){
    shiftOut(dataPin, clockPin, LSBFIRST, registerBytes[bytePos]);
    registerBytes[bytePos] = 0; //reset to blank for next time round
  }

  digitalWrite(latchPin,HIGH);
  delay(1);
  digitalWrite(latchPin, LOW);

}
 
