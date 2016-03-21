#include <Wire.h>
#include "RTClib.h"
#include <rtttl.h>
#include <LowPower.h>
#include <EnableInterrupt.h>

RTC_DS1307 rtc;

#define SERIAL_RATE 9600


DateTime defaultTime = DateTime(2016, 3, 21, 02, 45, 0);

DateTime time;
DateTime prevTime;

int upButtonPin   = 7; 
int downButtonPin = 8;
long adjustmentSeconds=1;

//See more RTTTL songs at https://github.com/cefn/non-blocking-rtttl-arduino/blob/master/rtttl/examples/ProgmemSong/ProgmemSong.ino
//or look online for your favourite chimes, being careful to remove unnecessary spaces
int piezoPin = 6;
const char song_P[] PROGMEM = "Wham- Wake Me Up:d=4,o=5,b=300:f#5,2a5,2b5.,p,f#5,2a5,b5,2f#5,2d5,p,d5,e5,2f#5,2g5,f#5,e5,d5,2f#5,a5,2f#5,d5,2p";
ProgmemPlayer player(piezoPin);

int alarmHour = 8;
int alarmMinute = 41;

#define SLEEP_UNIT 50
#define IDLE_PERIOD 5000

unsigned long lastActivity;
volatile boolean sleptPeacefully;

void setup(){
  
  pinMode(piezoPin, OUTPUT);
  player.setSong(song_P);
  
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

  Serial.println("Entering low power mode");  
  do{
    sleepPeacefully(SLEEP_UNIT);

    time = rtc.now();
    if(time.hour() == alarmHour && time.minute() == alarmMinute){
      sleepDisturbed();
    }

    if(digitalRead(upButtonPin) == LOW) {
      sleepDisturbed();    
    }
    
    if(digitalRead(downButtonPin) == LOW) {
      sleepDisturbed();    
    }
    
  } while(sleptPeacefully);  
  
  lastActivity = millis();
  
  Serial.println("Exiting low power mode");  
  
  while(millis() - lastActivity < IDLE_PERIOD){

    //perform routine time-based tasks here
    
    time = rtc.now();

    if(digitalRead(upButtonPin) == LOW){
      rtc.adjust(time + TimeSpan(adjustmentSeconds));  
      adjustmentSeconds = adjustmentSeconds + 1;
      lastActivity = millis();
    }
    else if(digitalRead(downButtonPin) == LOW){
      rtc.adjust(time - TimeSpan(adjustmentSeconds));
      adjustmentSeconds = adjustmentSeconds + 1;
      lastActivity = millis();
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
    
    if(time.hour() == alarmHour && time.minute() == alarmMinute){
      Serial.println("Alarm playing!");
      player.pollSong();
      lastActivity = millis();
    }
    else{
      player.silence();
      player.initSong();
    }

  }
      
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

boolean lowPowerDue(){
  return millis() - lastActivity > IDLE_PERIOD;
}

boolean sleepPeacefully(unsigned long milliseconds){
  sleptPeacefully = true;
  sleepSerial();
  
  while (sleptPeacefully && (milliseconds >= 8000)) { LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);    milliseconds -= 8000; }
  if (sleptPeacefully && milliseconds >= 4000) {      LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);    milliseconds -= 4000; }
  if (sleptPeacefully && milliseconds >= 2000) {      LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);    milliseconds -= 2000; }  
  if (sleptPeacefully && milliseconds >= 1000) {      LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);    milliseconds -= 1000; }
  if (sleptPeacefully && milliseconds >= 500) {       LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF); milliseconds -= 500;  }
  if (sleptPeacefully && milliseconds >= 250) {       LowPower.powerDown(SLEEP_250MS, ADC_OFF, BOD_OFF); milliseconds -= 250;  }
  if (sleptPeacefully && milliseconds >= 125) {       LowPower.powerDown(SLEEP_120MS, ADC_OFF, BOD_OFF); milliseconds -= 120;  }
  if (sleptPeacefully && milliseconds >= 64) {        LowPower.powerDown(SLEEP_60MS, ADC_OFF, BOD_OFF);  milliseconds -= 60;   }
  if (sleptPeacefully && milliseconds >= 32) {        LowPower.powerDown(SLEEP_30MS, ADC_OFF, BOD_OFF);  milliseconds -= 30;   }
  if (sleptPeacefully && milliseconds >= 16) {        LowPower.powerDown(SLEEP_15Ms, ADC_OFF, BOD_OFF);  milliseconds -= 15;   }
  
  wakeSerial();
  return sleptPeacefully;
}

void sleepDisturbed(){
  sleptPeacefully = false;
}

void sleepSerial(){
  //Interrupt monitors a wire from Arduino 
  //Serial Receive pin 0 to pin 2    
  Serial.flush();
  pinMode(2, INPUT_PULLUP);
  enableInterrupt(2, &sleepDisturbed, CHANGE);
}

void wakeSerial(){
  disableInterrupt(2);
  pinMode(2,INPUT);
  Serial.begin(SERIAL_RATE);
  while(Serial.available() && Serial.peek()=='\n'){
    Serial.read(); //throw away surplus newlines on wakeup
  }
}
