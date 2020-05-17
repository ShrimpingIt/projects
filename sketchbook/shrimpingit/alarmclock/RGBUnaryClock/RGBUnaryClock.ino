#include <Wire.h>
#include "RTClib.h"
#include <rtttl.h>

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            5

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      24

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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

//Each of these binary sequences should have 
//an easily distinguishable number of LED lights
int distinctNumbers[] = {
  0b000000000000, //0
  0b000000000001, //1
  0b100000000001, //2
  0b000100010001, //3
  0b001001001001, //4
  0b011000100011, //5
  0b000000111111, //6
  0b111111000001, //7
  0b011011011011, //8
  0b011101110111, //9
  0b101111111101, //10
  0b111110111111, //11
  0b111111111111  //12
};

int minBright = 5;
int maxBright = 50;
int brightnesses[] = {
  minBright, minBright, minBright, minBright,
  minBright, minBright, minBright, minBright,
  minBright, minBright, minBright, minBright,
  minBright, minBright, minBright, minBright,
  minBright, minBright, minBright, minBright,
  minBright, minBright, minBright, minBright,
};

int alarmHour = 9;
int alarmMinute = 35;

void setup(){
  Serial.begin(SERIAL_RATE);
  Wire.begin();
  rtc.begin();

  //reserve enough string memory for ISO8601 date string like 2015-06-01T12:00:00
  command.reserve(COMMANDMAX + 1); 
  field.reserve(COMMANDMAX + 1);

  pinMode(PIN, OUTPUT);
 
  player.setSong(song_P);
  
  if (rtc.isrunning()) {
    printDateTimeVerbose();
  }
  else{
    Serial.println("Realtime Clock has not yet been set!");
  }  

    // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.

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

void randomWalkBrightness(int lightPos){
  if(random(0,2) == 0){
    if(brightnesses[lightPos] < maxBright){
      brightnesses[lightPos] += 1;
    }
  }
  else{
    if(brightnesses[lightPos] > minBright){
      brightnesses[lightPos] -= 1;
    }    
  }
}

void shiftLights(int showHours, int showMinutes){

  DateTime now = rtc.now();    

  boolean nightMode = false; //now.hour() >= 19 || now.hour() < 7;

  int brightness = nightMode ? 2 : 256;

  int minuteWheelPos  = nightMode? 48: (millis() / 200) % 256;
  int hourWheelPos = nightMode? 0: (minuteWheelPos + 128) % 256;

  int lightPos;

  for(int minutePos = 0; minutePos < 12; minutePos++ ){
    lightPos = minutePos;
    if(leftUnaryIsLit(showMinutes, minutePos)){
      pixels.setPixelColor(lightPos, scale(Wheel(minuteWheelPos), brightness)); //GRB
    }
    else{
      pixels.setPixelColor(lightPos, pixels.Color(0,0,0)); //GRB      
    }
    randomWalkBrightness(lightPos);
  }

  for(int hourPos = 0; hourPos < 12; hourPos++){
    lightPos = hourPos + 12;
    if(distinctNumberIsLit(showHours, hourPos)){      
      pixels.setPixelColor(lightPos, scale(Wheel(hourWheelPos), brightness)); //GRB
    }
    else{
      pixels.setPixelColor(lightPos, pixels.Color(0,0,0)); //GRB      
    }
    randomWalkBrightness(hourPos);
  }

  pixels.show(); // This sends the updated pixel color to the hardware.

}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 8);
}
uint8_t green(uint32_t c) {
  return (c >> 16);
}
uint8_t blue(uint32_t c) {
  return (c);
}

uint32_t scale(uint32_t color, int brightness) {
  return pixels.Color(
    (brightness * red(color)) / 256,
    (brightness * green(color)) / 256,
    (brightness * blue(color)) / 256
  );
}
