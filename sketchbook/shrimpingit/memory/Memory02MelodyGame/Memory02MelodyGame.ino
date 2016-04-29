//#include <Tone.h> //to reinclude, need to fix initSong to only initialise tonePin once
#include <rtttl.h>

/** 
This is a clone of the logic of MB Games' Simon memory game 

It is intended to drive an example circuit developed for the @ShrimpingIt
project, which documents how to make extremely low cost and simple
Arduino-compatible circuits. See http://start.shrimping.it/project/memory/

A cheaper soldered version can use tactile switches on the back, and LEDs on the 
front directly as illuminated buttons, massively reducing the cost of parts.
*/

//the pins used to provide the 
//backlit pads for the Simon Game
#define NUMPADS 4
int buttons[] = {2,7,10,A2};
int buttonGrounds[] = {4,5,12,A0};
int lights[] = {3,6,11,A1};

//the storage used for the pad 
//sequence you have to follow 
#define MAXSEQUENCE 128
int sequence[MAXSEQUENCE];
int sequencePos = 0;
int sequenceLength = 1;

//These should in the end use RTTTL to define any tune
const char greetSong[] PROGMEM = "PacMan:b=160:32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32c6,32p,32c7,32p,32g6,32p,32e6,32p,32c7,32g6,16p,16e6,16p,32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32d#6,32e6,32f6,32p,32f6,32f#6,32g6,32p,32g6,32g#6,32a6,32p,32b.6";
const char levelSong[] PROGMEM = "DonkeyKong:d=4,o=5,b=300:c6,32p,8d6,8p,f6,8p,8d6,16p,8c6,16p,8d6,16p,a#";
const char failSong[] PROGMEM = "Fail:b=80:16d,8p,16c#,8p,16c,8p,4b4";

#define SHOW 1
#define HEAR 2
int gameMode = SHOW;

ProgmemPlayer tonePlayer(13);
int tones[] = {NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4};

unsigned long lastTriggered = 0;
int lastPadPressed = -1;

long toneLength = 400;
long restLength = 100;

unsigned long noteStarted = -1;
int noteDuration = -1;

void setup(){
  Serial.begin(9600);
  randomSeed(seedOut(31));
  initPins();
  tonePlayer.setSong(greetSong);

  //play greeting song
  tonePlayer.setSong(greetSong);
  flashSong();
  
  delay(toneLength * 2);

  resetGame();
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

void loop(){
	//decide if anything needs doing, based on current mode
	if(gameMode == SHOW){
		//simon is playing a sequence to memorise
		showSequence();
	}
	else if(gameMode==HEAR){
		//not teaching but waiting for presses
		hearSequence();
	}
}

void randomiseSequence(){
	for(int sequenceIdx = 0; sequenceIdx < MAXSEQUENCE; sequenceIdx++){
		//sequence[sequenceIdx] = random(NUMPADS);
	        sequence[sequenceIdx] = rand4();
	}
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

int getPadPressed(){
	for(int padIdx = 0; padIdx < NUMPADS; padIdx++){
		if(digitalRead(buttons[padIdx]) == LOW){
			return padIdx;
		}
	}
	return -1;
}

void setMode(int mode){
  if(mode == SHOW){
    delay(toneLength);    
  }
  tonePlayer.silence();
  darkenPads();
  gameMode = mode;
  sequencePos = 0;
}

void resetGame(){
        tonePlayer.setSong(levelSong);
        flashSong();
        delay(toneLength);

        sequenceLength = 1;
	randomiseSequence();
        setMode(SHOW);
}

void showSequence(){
	//get a timestamp for this iteration
	long now = millis();

	//consider progressing the tune and lights
	if(tonePlayer.isSilent()){
                Serial.println("No sound");
		//test if a beep should begin
		if(now - lastTriggered > (toneLength + restLength) || lastTriggered == 0){
                        Serial.println("Last note finished");
			//progress sequence, play note and illuminate light
			if(sequencePos < sequenceLength){
                              Serial.print("Playing new note: ");
                              Serial.println(sequence[sequencePos]);
				//still more of target melody to play
				tonePlayer.beep(tones[sequence[sequencePos]], toneLength);
				digitalWrite(lights[sequence[sequencePos]], HIGH);
				lastTriggered = now;
				sequencePos += 1;
			}
			else{
                              Serial.println("Played all the notes in this round");
				//target melody is complete
				//now check the player can copy it
                                setMode(HEAR);
			}				
		}
	}
	else{
          Serial.println("Speaker playing");
		//sound is playing, check if it should stop
		if(!tonePlayer.pollBeep()){
                        Serial.println("Stopping note");
			//stop sound and extinguish lights
                        tonePlayer.silence();
			darkenPads();
		}
	}
}

void hearSequence(){

	int padPressed = getPadPressed(); 
        Serial.print("Pad pressed");
        Serial.println(padPressed);
	
	if(padPressed != lastPadPressed){
		//pad state has changed
		if(lastPadPressed == -1){
			//a pad was pressed, so light that pad
			lightPad(padPressed);
			if(padPressed == sequence[sequencePos]){
                                Serial.println("Note is correct, incrementing sequence");
				//if correct target play successful tone
				tonePlayer.beep(tones[padPressed], toneLength);
				//extend the melody and teach again
				sequencePos += 1;
                                if(sequencePos == sequenceLength){
                                  //completed this round
                                  sequenceLength += 1;
  				  if(sequenceLength != MAXSEQUENCE){
                                    //not completed game, so re-run
                                    Serial.println("Demonstrating longer sequence");
                                    setMode(SHOW);
  				  }
                                  else{
                                    Serial.println("Game is complete");
                                    //completed game!
                                    //TODO some kind of fanfare
                                    resetGame();
                                  }
                                }
			}
			else{
                                Serial.println("Note is wrong, resetting game");
  				//play failure tone
                                tonePlayer.setSong(failSong);
                                flashSong(false);
                                delay(toneLength * 4);
				//start teaching a new random sequence
				resetGame();
			}
			lastTriggered = millis();
		}
		else{
			//a pad was released
			//turn off lights and silence
			tonePlayer.silence();
			darkenPads();
		}
		lastPadPressed = padPressed;
	}
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
