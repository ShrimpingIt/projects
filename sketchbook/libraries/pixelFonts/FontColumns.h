//turn asciiColumns from relative (character width in columns) into absolute (where do the character's columns start in the columns array)

void calculateFontColumns(){

  int characterColumns;

  //calculate how many characters there are
  int numCharacters = sizeof(asciiColumns) / sizeof(int);
  
  //turn relative column count into absolute column index
  int cumulativeColumns = 0;                                                         //pixels used up so far
  for(int characterIndex = 0; characterIndex < numCharacters; characterIndex ++){    //for each character
    characterColumns = asciiColumns[characterIndex];                                 //save the number of pixels in this character?
    asciiColumns[characterIndex] = cumulativeColumns;                                //overwrite the relative column value with the cumulative column value
    cumulativeColumns = cumulativeColumns + characterColumns;
  }
  
}

int getLookupPosition(byte asciiCharacter){
  return asciiCharacter - 32;
}

int getStartColumn(byte asciiCharacter){
  return asciiColumns[getLookupPosition(asciiCharacter)];
}

int getNumColumns(byte asciiCharacter){
  return getStartColumn(asciiCharacter + 1) - getStartColumn(asciiCharacter);
}

byte getFontPattern(byte asciiCharacter, int columnIndex){
  return columns[getStartColumn(asciiCharacter) + columnIndex]; 
}
