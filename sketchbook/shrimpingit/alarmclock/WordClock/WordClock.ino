#include "RTClib.h"
#include "Adafruit_NeoPixel.h"
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

DateTime defaultTime = DateTime(2016, 6, 8, 01, 06, 30);

int upButtonPin   = 7;
int downButtonPin = 8;
long adjustmentSeconds;

int totalLeds = 50;

//record the positions of different lights

int itsWord[] = {0,1};

int halfMins[] =    { 2, 3};
int quarterMins[] = { 4, 6};
int twentyMins[] =  { 7, 9};
int tenMins[] =     {10,10};
int fiveMins[] =    {11,12};

int minutesWord[] = {23,21};
int toWord[] =      {20,20};
int pastWord[] =    {19,18};

int oneOclock[] =   {17,17};
int twoOclock[] =   {16,15};
int threeOclock[] = {14,13};
int fourOclock[] =  {24,25};
int fiveOclock[] =  {26,27};
int sixOclock[] =   {28,28};
int sevenOclock[] = {29,31};
int eightOclock[] = {32,33};
int nineOclock[] =  {34,35};
int tenOclock[] =   {36,36};
int elevenOclock[]= {49,47};
int twelveOclock[]= {46,44};

int finalWord[] =   {43,37};

int* allHours[12] = {
  oneOclock, twoOclock, threeOclock, /* rock */ 
  fourOclock, fiveOclock, sixOclock, /* rock */
  sevenOclock, eightOclock, nineOclock, /* rock */ /* we're gonna rock around the clock tonight  */
  tenOclock, elevenOclock, twelveOclock, 
};


int* allWords[]={
  itsWord,halfMins,quarterMins,twentyMins,tenMins,fiveMins,
  minutesWord,toWord,pastWord,oneOclock,twoOclock,threeOclock,
  fourOclock, fiveOclock, sixOclock, sevenOclock, eightOclock, nineOclock, tenOclock,
  elevenOclock,twelveOclock,finalWord,
};
int numWords = sizeof(allWords) / sizeof(int**);

#define PIXELPIN 6

#define NUMPIXELS      50

int morecambeSeconds = 2;

boolean useRainbow = true;
int wheelPeriod = 5013;
byte wheelOffset = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIXELPIN, NEO_RGB + NEO_KHZ400);

  //calculate the low-contrast and high-contrast colors to use
uint32_t visible = strip.Color(255,255,255);
uint32_t invisible = strip.Color(0,0,0);

DateTime time;
int hour, minute, second;

void setup() {
  Wire.begin();
  rtc.begin();
  strip.begin();
  Serial.begin(9600);

  pinMode(upButtonPin,   INPUT_PULLUP);
  pinMode(downButtonPin, INPUT_PULLUP);

  setClock();

  time = rtc.now();
  Serial.print("Date: ");
  Serial.print(time.year(), DEC);
  Serial.print('-');
  Serial.print(time.month(), DEC);
  Serial.print('-');
  Serial.print(time.day(), DEC);
  Serial.println();

}

void loop() {
  time = getTime();
  hour =    time.hour();
  minute =  time.minute();
  second =  time.second();

  if(((minute % 15) == 0) && second < 10){
    showDemo();
  }
  else{
    if(second > 60 - morecambeSeconds){
      showMorecambe();
    }
    else{
      showTime();
    }
  }

  wheelOffset = (((millis() % wheelPeriod) * 255) / wheelPeriod);
  
  delay(50);
}

DateTime getTime(){
  return rtc.now();
}

void showDemo(){  
  colorWipe(strip.Color(255, 0, 0), 20); // Red
  colorWipe(strip.Color(0, 255, 0), 20); // Green
  colorWipe(strip.Color(0, 0, 255), 20); // Blue
  theaterChase(strip.Color(255, 0, 0), 10); // Red
  theaterChase(strip.Color(0, 255, 0), 10); // Green
  theaterChase(strip.Color(0, 0, 255), 10); // Blue
  rainbowCycle(2);
}

void showMorecambe(){
  unsigned long start, moment;
  start = millis();
  do{
    moment = millis();

    hideAll();
    
    if(((moment-start) % 500) < 250){
      setWordVisible(itsWord);
      setWordVisible(finalWord);
    }
    else{
      hideWord(itsWord);
      hideWord(finalWord);
    }

    strip.show();

  }
  while(((moment - start) / 1000) < morecambeSeconds);
}

void showTime(){

  //turn off all the lights to begin
  hideAll();

  //light up the generic labels
  setWordVisible(itsWord);

  //store the hour for (optional) offsetting
  int showHour = hour;

  if(minute < 5){
    //show no minutes
  }
  else if(minute < 35){

    //light up the relevant minutes
    if(minute < 10){
      setWordVisible(fiveMins);
      setWordVisible(minutesWord);
    }
    else if(minute < 15){
      setWordVisible(tenMins);
      setWordVisible(minutesWord);
    }
    else if(minute < 20){
      setWordVisible(quarterMins);
    }
    else if(minute < 25){
      setWordVisible(twentyMins);
      setWordVisible(fiveMins);
      setWordVisible(minutesWord);
    }
    else{
      setWordVisible(halfMins);
    }

    //light up the 'past' label
    setWordVisible(pastWord);

  }
  else { //the minute is 35 or higher
    //change hour to compensate for 'to/past logic'
    showHour = showHour + 1;
    
    //light up the relevant minutes
    if(minute < 40){
      setWordVisible(twentyMins);
      setWordVisible(fiveMins);
      setWordVisible(minutesWord);
    } 
    else if(minute < 45){
      setWordVisible(twentyMins);
      setWordVisible(minutesWord);
    }
    else if(minute < 50){
      setWordVisible(quarterMins);
    }
    else if(minute < 55){
      setWordVisible(tenMins);
      setWordVisible(minutesWord);
    }
    else{
      setWordVisible(fiveMins);
      setWordVisible(minutesWord);
    }

    //light up the 'to' label
    setWordVisible(toWord);  

  }

  //compensate for 24 hour clock, and 0 is 12;
  showHour = ((showHour - 1) % 12) + 1;

  //finally set the hour
  setWordVisible(allHours[showHour - 1]);

  setWordVisible(finalWord);

  strip.show(); // This sends the updated pixel color to the hardware.

}

void hideAll(){
  //turn off all the lights
  for(int wordCount = 0; wordCount < numWords; wordCount++){
    hideWord(allWords[wordCount]);
  }
}

void hideWord(int wordRange[]){
  setWordColor(wordRange, invisible);
}

void setWordVisible(int wordRange[]){
  //handle forward and reverse-sequenced lights
  int beginLight, endLight;
  if(wordRange[0]<=wordRange[1]){
    beginLight = wordRange[0];
    endLight =   wordRange[1];
  }
  else{
    beginLight = wordRange[1];
    endLight =   wordRange[0];    
  }
  
  for(int lightPos = beginLight; lightPos <= endLight; lightPos++){
    uint32_t color = useRainbow ? Wheel( (byte) ((((255 * lightPos) / NUMPIXELS) + wheelOffset) % 255)) : visible;
    strip.setPixelColor(lightPos, color); 
  }
}

void setWordColor(int wordRange[], uint32_t color){
  //handle forward and reverse-sequenced lights
  int beginLight, endLight;
  if(wordRange[0]<=wordRange[1]){
    beginLight = wordRange[0];
    endLight =   wordRange[1];
  }
  else{
    beginLight = wordRange[1];
    endLight =   wordRange[0];    
  }
  
  for(int lightPos = beginLight; lightPos <= endLight; lightPos++){
    strip.setPixelColor(lightPos, color); 
  }

/*
  if(color == visible){
    if(wordRange == itsWord){
      Serial.print("It's ");
    }
  
    if(wordRange == halfMins){
      Serial.print("half ");
    }
    if(wordRange == quarterMins){
      Serial.print("quarter ");
    }
    if(wordRange == twentyMins){
      Serial.print("twenty ");
    }
    if(wordRange == tenMins){
      Serial.print("ten ");
    }
    if(wordRange == fiveMins){
      Serial.print("five ");
    }
  
    if(wordRange == minutesWord){
      Serial.print("minutes ");
    }
    if(wordRange == toWord){
      Serial.print("to ");
    }
    if(wordRange == pastWord){
      Serial.print("past ");
    }
  
    if(wordRange == oneOclock){
      Serial.print("one ");
    }
    if(wordRange == twoOclock){
      Serial.print("two ");
    }
    if(wordRange == threeOclock){
      Serial.print("three ");
    }
    if(wordRange == fourOclock){
      Serial.print("four ");
    }
    if(wordRange == fiveOclock){
      Serial.print("five ");
    }
    if(wordRange == sixOclock){
      Serial.print("six ");
    }
    if(wordRange == sevenOclock){
      Serial.print("seven ");
    }
    if(wordRange == eightOclock){
      Serial.print("eight ");
    }
    if(wordRange == nineOclock){
      Serial.print("nine ");
    }
    if(wordRange == tenOclock){
      Serial.print("ten ");
    }
    if(wordRange == elevenOclock){
      Serial.print("eleven ");
    }
    if(wordRange == twelveOclock){
      Serial.print("twelve ");
    }

    if(wordRange == finalWord){
      Serial.println("#MorecambeTime ");
    }

  }
*/

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
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

