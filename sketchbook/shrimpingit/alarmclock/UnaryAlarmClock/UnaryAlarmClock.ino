#include <Wire.h>
#include "RTClib.h"
#include <rtttl.h>
#include <Narcoleptic.h>

RTC_DS1307 rtc;

//See more RTTTL songs at https://github.com/cefn/non-blocking-rtttl-arduino/blob/master/rtttl/examples/ProgmemSong/ProgmemSong.ino
//or look online for your favourite chimes, being careful to remove unnecessary spaces
const char song_P[] PROGMEM = "Wham- Wake Me Up:d=4,o=5,b=300:f#5,2a5,2b5.,p,f#5,2a5,b5,2f#5,2d5,p,d5,e5,2f#5,2g5,f#5,e5,d5,2f#5,a5,2f#5,d5,2p";

ProgmemPlayer player(9);

boolean lit[36];
const int clockPin = A3;
const int dataPin = A2;

//Each of these binary sequences should have 
//an easily distinguishable number of LED lights
int distinctNumbers[] = {
  0b000000000000, //0
  0b000000100000, //1
  0b100000000001, //2
  0b100010001000, //3
  0b001001001001, //4
  0b011000100011, //5
  0b101010101010, //6
  0b100000111111, //7
  0b011011011011, //8
  0b011101110111, //9
  0b101111111101, //10
  0b111111011111, //11
  0b111111111111  //12
};

//these are the assignments of each LED driver
//pin to an hour or minute light
//positive number from 1 to 12 is an hour indicator light
//negative number from -1 to -12 is a minutes indicator light
//zero means do not use
int assignments[] ={
    1,  2, 0,  3, 0,  4, 0,  5,  6,
   -6, -5, 0, -4, 0, -3, 0, -2, -1,
  -12,-11, 0,-10, 0, -9, 0, -8, -7,
    7,  8, 0,  9, 0, 10, 0, 11, 12
};

int brightness = 255;

int alarmHour = 7;
int alarmMinute = 00;

boolean report = true;

void setup(void)
{
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(57600);
  Wire.begin();
  rtc.begin();
 
  player.setSong(song_P);
  
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2015,2, 23, 1, 0, 0));
  }
  
  DateTime now = rtc.now();
  
  //for testing
  //alarmHour = now.hour();
  //alarmMinute = now.minute() + 2;
}

void loop(void)
{
    
  DateTime now;

  now = rtc.now();
  
  setTime(now.hour(), now.minute());
  
  while(now.hour() == alarmHour && now.minute() == alarmMinute){
    player.finishSong();
    now = rtc.now();
  }

  Narcoleptic.delay(10000);
  
  if(report){
    Serial.print(now.hour());
    Serial.print(":");
    Serial.print(now.minute());
    Serial.print(":");
    Serial.print(now.second());
    Serial.println();
    Serial.flush();
  }
  
}

void setTime(int newHours, int newMins){ 
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
  return (distinctNumbers[numLights] & (1 << pos)) != 0;  
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
    
  int showLights; //count of lights illuminated in the current bank
  int shiftPos; //the current pin which is being written to
  
  //go through all the pins of both shift registers
  for(shiftPos = 0; shiftPos < 36; shiftPos++){
    
    //figure out the assigned role of this pin 
    //value between 1 and 12 (magnitude), and if it's an hour or minute (sign)
    int assignment = assignments[shiftPos];

    if(assignment == 0){ //it's not meant to be active (has no LED in this pin)
      lit[shiftPos] = false; //leave it off
    }
    else {
      if(assignment >= 0){ //positive number indicates an hour light
        assignment = assignment - 1;  //shift to index LEDs from 0 to 11, not 1 to 12
        lit[shiftPos] = distinctNumberIsLit(showHours, assignment); 
      }
      else { //negative number indicates a minute light
        assignment = abs(assignment) - 1; //change sign and shift to index LEDs from 0 to 11 not 1 to 12
        lit[shiftPos] = leftUnaryIsLit(showMinutes, assignment); 
      }
    }    
        
    shiftOut(dataPin, clockPin, MSBFIRST, lit[shiftPos] ? brightness : 0); //set current light
        
  } 

  digitalWrite(clockPin, LOW);
  delay(1);
 
  if(report){
    Serial.print("arr:");
    for(shiftPos = 0; shiftPos < 36; shiftPos++){
      Serial.print(lit[shiftPos]?"1":"0");
    }
    Serial.println();
    Serial.flush();
  }


}
 
