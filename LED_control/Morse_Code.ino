/*
 * Morse code sketch taken from previous sketch
 */

// Morse Code Final Version
//   Functions:
//    - Convert text in string to morse code
//    - Supports A-Z
//    - Runs Once then powers down until reset

int characterLengths[] = {
  /*A*/ 2,  /*B*/ 4,  /*C*/ 4,  /*D*/ 3,  /*E*/ 1,  /*F*/ 4,  /*G*/ 3,  /*H*/ 4,
  /*I*/ 2,  /*J*/ 4,  /*K*/ 3,  /*L*/ 4,  /*M*/ 2,  /*N*/ 2,  /*O*/ 3,  /*P*/ 4,
  /*Q*/ 4,  /*R*/ 3,  /*S*/ 3,  /*T*/ 1,  /*U*/ 3,  /*V*/ 4,  /*W*/ 3,  /*X*/ 4,
  /*Y*/ 4,  /*Z*/ 4
};
boolean characters[] = {      // 0 = dot, 1 = dash
  /*A*/ 0, 1,
  /*B*/ 1, 0, 0, 0,
  /*C*/ 1, 0, 1, 0,
  /*D*/ 1, 0, 0,
  /*E*/ 0,
  /*F*/ 0, 0, 1, 0,
  /*G*/ 1, 1, 0,
  /*H*/ 0, 0, 0, 0,
  /*I*/ 0, 0,
  /*J*/ 0, 1, 1, 1,
  /*K*/ 1, 0, 1,
  /*L*/ 0, 1, 0, 0,
  /*M*/ 1, 1,
  /*N*/ 1, 0,
  /*O*/ 1, 1, 1,
  /*P*/ 0, 1, 1, 0,
  /*Q*/ 1, 1, 0, 1,
  /*R*/ 0, 1, 0,
  /*S*/ 0, 0, 0,
  /*T*/ 1,
  /*U*/ 0, 0, 1,
  /*V*/ 0, 0, 0, 1,
  /*W*/ 0, 1, 1,
  /*X*/ 1, 0, 0, 1,
  /*Y*/ 1, 0, 1, 1,
  /*Z*/ 1, 1, 0, 0
};

#define unit 240         // unit time (milliseconds) based on a wpm of 5
#define brightness 64   // pwm led brightness
int character;
int charPos;
uint8_t activeLed;

String message = "DAFTY";  // message to transmit

void morseTransmit(){  
  activeLed = 0;
  for(int n = 0; n <= message.length(); n++ ){    // go through all characters and comvert to character definitions as above
    character = (message.charAt(n)) - 65;        // Convert from ASCII to Character definitions above
    if(character >= 0){
      transmitCharacter(character);
      activeLed ++;
      if(activeLed == 4){
        activeLed = 0;
      }
    }
    else{
      wordspace();                               // if character value goes negative then a space is in the message
    }
  }
}

void transmitCharacter(int character){             // take character value and transmit the correct morse code combo
  charPos =  0;
  for(int n = 0; n <= character; n ++){            // find start position in characters array
    if(n == character){
    }
    else{
      charPos = charPos + characterLengths[n];
    }
  }
  for(int m = charPos; m < charPos + characterLengths[character]; m ++){      // decode data from character array and transmit relevant dot/dash
    if(characters[m] == 1){
      dash(activeLed);
    }
    else{
      dot(activeLed);
    }
  }
  delay(3*unit);      // letter space
}

void dot(uint8_t ledpin){                                      // definition for a dot followed by a part space
  digitalWrite(pins[ledpin], HIGH);
  delay(unit);
  digitalWrite(pins[ledpin], LOW);
  delay(unit);
}
void dash(uint8_t ledpin){                                      // definition for a dash followed by a part space
  digitalWrite(pins[ledpin], HIGH);
  delay(3*unit);
  digitalWrite(pins[ledpin], LOW);
  delay(unit);
}
void wordspace(){                                  // word space
  delay(7*unit);
}
