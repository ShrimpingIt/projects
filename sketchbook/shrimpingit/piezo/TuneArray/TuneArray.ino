int noteLength = 200;
int pauseLength = 1;

int NUM_NOTES = 12;
int notes[] = {523,493,392,493,493,329,0,493,261,392,440,493};

void setup(){
  pinMode(6,OUTPUT);
}

void loop(){
  
  for(int idx = 0; idx < NUM_NOTES; idx++){
    tone(6, notes[idx]); 
    delay(noteLength);
    noTone(6);
    delay(pauseLength);    
  }
  
  while(millis() > 10000){ //after 10 seconds, stays in this loop, silenced
      //do nothing
  }

}

