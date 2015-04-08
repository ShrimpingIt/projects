#include <rtttl.h>

//const char song_P[] PROGMEM = "Ghostbusters:d=4,o=5,b=180:4c5,4c5,8e5,8f5,8g5,8p, 4a#5,4a#5,4f5,4f5,4c5,4c5,8e5,8f5,8g5,8p,4a#5,4a#5,4f5";
//const char song_P[] PROGMEM = "dkong_level:d=4,o=5,b=200:c6,32p,8d6,8p,f6,8p,8d6,16p,8c6,16p,8d6,16p,a#";
//const char song_P[] PROGMEM = "PacMan:b=160:32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32c6,32p,32c7,32p,32g6,32p,32e6,32p,32c7,32g6,16p,16e6,16p,32b,32p,32b6,32p,32f#6,32p,32d#6,32p,32b6,32f#6,16p,16d#6,16p,32d#6,32e6,32f6,32p,32f6,32f#6,32g6,32p,32g6,32g#6,32a6,32p,32b.6";
//const char song_P[] PROGMEM = "DonkeyKong:d=4,o=5,b=200:8a#,8p,8d6,16p,16f.6,16g.6,16f.6,8a#,8p,8d6,16p,16f.6,16g.6,16f.6,8a#,8p,8d6,16p,16f.6,16g.6,16f.6,8a#,8p,8d6,16p,16f.6,16g.6,16f.6";
//const char song_P[] PROGMEM = "Dambuste:d=4,o=5,b=63:4f6,8a#6,8f6,8f6,16d#6,16d6,8d#6,8f6,4d6,8f6,8d6,8d6,16c6,16a#,8a,8c6,8a#.,16c6,8d6,8g6,8f.6,16d6,4f6,8c6,8f6,16g6,16a6,8a#6,4a6,4p";
//const char song[] = "AxelF:d=4,o=5,b=125:32p,8g,8p,16a#.,8p,16g,16p,16g,8c6, 8g,8f,8g,8p,16d.6,8p,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6, 16g,16f,16p,16f,8d,8a#,2g,p,SS,16f6,8d6,8c6,8a#,g,8a#.,16g, 16p,16g,8c6,8g,8f,g,8d.6,16g,16p,16g,8d#6,8d6,8a#,8g,8d6, 8g6,16g,16f,16p,16f,8d,8a#,2g";
const char song_P[] PROGMEM = "Tetris:d=4,o=5,b=200:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a";

unsigned long printedTime = -1;
unsigned long printedPeriod = 500;

ProgmemPlayer player(13);

void setup(void)
{
  Serial.begin(115200);
  player.setSong(song_P);
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
