#include <Wire.h>
#include "RTClib.h"
#include <LowPower.h>
#include <EnableInterrupt.h>

RTC_DS1307 rtc;

#define SERIAL_RATE 9600

#define SERIAL_RECEIVE_PIN 0
#define SERIAL_IDLE_PERIOD 30000
#define SLEEP_UNIT 10000

#define COMMANDMAX 19

String command = "";
String field = "";
int fieldStart = 0;

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

unsigned long lastSerialActivity;
volatile boolean sleptPeacefully;

void setup(){
  Serial.begin(SERIAL_RATE);
  Wire.begin();
  rtc.begin();
  
  lastSerialActivity = millis();
  
  //reserve enough string memory for ISO8601 date string like 2015-06-01T12:00:00
  command.reserve(COMMANDMAX + 1); 
  field.reserve(COMMANDMAX + 1);
  
  printDateTimeVerbose();
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
      lastSerialActivity = millis(); //record receiving the command
    }
  }
  
  if(lowPowerDue()){
    Serial.print("\nNo commands since ");
    Serial.print(SERIAL_IDLE_PERIOD);
    Serial.println(" ms");
    Serial.println("Hit 'Enter' to wake\n(send a Newline character)");    

    while(true){
      if(sleepPeacefully(SLEEP_UNIT)){
        //perform routine time-based tasks here
      }
      else{
        Serial.println("Awakened: awaiting commands");
        lastSerialActivity = millis(); //record being woken up
        break; //start processing commands again
      }
    }
  }

}

boolean lowPowerDue(){
  return millis() - lastSerialActivity > SERIAL_IDLE_PERIOD;
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
