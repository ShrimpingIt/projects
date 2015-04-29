#include <rtttl.h>

#define NUMPADS 4
int buttons[] = {2,7,10,A2};
int buttonGrounds[] = {4,5,12,A0};
int lights[] = {3,6,11,A1};

unsigned long beepLength = 200;

ProgmemPlayer tonePlayer(13);
int tones[] = {NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4};

void setup(){
  randomSeed(seedOut(32));
  initPins();
}

void loop(){
  int targetPin = rand4(); //choose a random number from 0-3
  darkenPads(); //turn off all lights
  lightPad(targetPin); //light the chosen pad
  while(getPadPressed()!=targetPin){ //wait for the chosen pad to be pushed
    delay(1);
  }
  tonePlayer.beep(tones[targetPin],beepLength); //play the beep
  while(tonePlayer.pollBeep()){ //wait for it to finish
    delay(1);
  }
}

void initPins(){
  for(int padIdx = 0; padIdx < NUMPADS; padIdx++){
    //softwire buttons
    pinMode(buttons[padIdx], INPUT); //choose one end of button as pull-up
    digitalWrite(buttons[padIdx], HIGH); //configure pull-up resistors
    pinMode(buttonGrounds[padIdx], OUTPUT); //choose the other end as pull-down
    digitalWrite(buttonGrounds[padIdx], LOW); //make sure other end acts as ground
    //softwire lights
    pinMode(lights[padIdx],OUTPUT);
  }
}

int getPadPressed(){
	for(int padIdx = 0; padIdx < NUMPADS; padIdx++){
		if(digitalRead(buttons[padIdx]) == LOW){
			return padIdx;
		}
	}
	return -1;
}

void lightPad(int padIdx){
	digitalWrite(lights[padIdx], HIGH);
}

void lightenPads(){
	for(int padIdx = 0; padIdx < NUMPADS; padIdx++){
		digitalWrite(lights[padIdx], HIGH);
	}	
}

void darkenPads(){
	for(int padIdx = 0; padIdx < NUMPADS; padIdx++){
		digitalWrite(lights[padIdx], LOW);
	}	
}

void flashSong(){
  flashSong(true);
}

void flashSong(bool cycle){
  bool wasSilent = true;
  bool isSilent = true;
  int flashPad = 0;
  while(tonePlayer.pollSong()){ //keep stepping through the song
    isSilent = tonePlayer.isSilent();
    if(isSilent != wasSilent){ //step has begun - either note or rest
      darkenPads();
      if(!isSilent){ //note is playing
        if(cycle){
          lightPad(flashPad++ % NUMPADS);
        }
        else{
          lightenPads();
        }
      }
    }
    wasSilent = isSilent;
  }
  darkenPads();
}

/** Drawing on commentary at http://citeseer.ist.psu.edu/viewdoc/download;jsessionid=4F8F207F726CB56B4630F8155F748256?doi=10.1.1.53.3686&rep=rep1&type=pdf and 
* http://stackoverflow.com/questions/8569113/why-1103515245-is-used-in-rand which mentions "The high order 16 bits are acceptable" in the basic libc C rand function
*/
int rand4(){
  return random(4);
}

/** Randomness functions from http://www.utopiamechanicus.com/article/arduino-better-random-numbers/ */

unsigned int bitOut(void)
{
  static unsigned long firstTime=1, prev=0;
  unsigned long bit1=0, bit0=0, x=0, port=4, limit=99;
  if (firstTime)
  {
    firstTime=0;
    prev=analogRead(port);
  }
  while (limit--)
  {
    x=analogRead(port);
    bit1=(prev!=x?1:0);
    prev=x;
    x=analogRead(port);
    bit0=(prev!=x?1:0);
    prev=x;
    if (bit1!=bit0)
      break;
  }
  return bit1;
}

unsigned long seedOut(unsigned int noOfBits)
{
  // return value with 'noOfBits' random bits set
  unsigned long seed=0;
  for (int i=0;i<noOfBits;++i)
    seed = (seed<<1) | bitOut();
  return seed;
}
