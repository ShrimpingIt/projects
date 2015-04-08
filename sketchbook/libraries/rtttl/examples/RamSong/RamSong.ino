#include <rtttl.h>

//note this is not declared in PROGMEM
const char song[] = "AxelF:d=4,o=5,b=125:32p,8g,8p,16a#.,8p,16g,16p,16g,8c6,8g,8f,8g,8p,16d.6,8p,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g,p,SS,16f6,8d6,8c6,8a#,g,8a#.,16g,16p,16g,8c6,8g,8f,g,8d.6,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g";

unsigned long printedTime = -1;
unsigned long printedPeriod = 500;

RamPlayer player(13);

void setup(void)
{
  Serial.begin(115200);
  player.setSong(song);
}

void loop(void)
{
  
  Serial.println("First Play");

  //play the song for the first time
  player.finishSong();

  Serial.println("Song rewound automatically");  

  //play the tune again, this time blocking per note
  while(player.stepSong()){
    Serial.println("Second Play");
  }

  Serial.println("Song rewound automatically");

  //play the tune with no blocking
  while(player.pollSong()){
    tryPrint("Third Play");
  }

  Serial.println("Play has ended");    
  while(true){
    //keep the thread in this loop - circuit now silent
  }
  
}

void tryPrint(String msg){
  if(millis() - printedTime > printedPeriod){
    Serial.println(msg);
    printedTime = millis();
  }
}
