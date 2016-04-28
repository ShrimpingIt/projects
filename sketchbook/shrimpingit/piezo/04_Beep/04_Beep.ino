void setup(){
  pinMode(6,OUTPUT);
}

void loop(){
  tone(6, 4000);
  delay(1000);
  noTone(6);
  delay(1000);

  while(millis() > 10000){ //after 10 seconds, stays in this loop, silenced
      //do nothing
  }
  
}
