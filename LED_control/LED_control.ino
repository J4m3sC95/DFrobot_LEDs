/*
 * DFrobot Beetle LED control sketch
 * 
 * (based upon the iron man control sketch)
 * 
 */

uint8_t pins[5] = {
  A2, /*RED*/
  A0, /*BLUE*/
  9,  /*YELLOW*/
  11  /*GREEN*/
};

#define BUTTON_PIN  2

// effect numbers
#define EFFECT_COUNT                    7
#define FLASH                           1
#define LOADING                         2
#define ALTERNATE_FLASH                 3
#define RANDOM_FLASH_INDIVIDUAL         4
#define RANDOM_FLASH_INDIVIDUAL_INVERT  5
#define RANDOM_FLASH_PAIR               6
#define RANDOM_FLASH_PAIR_INVERT        7

int delay_array [EFFECT_COUNT + 1] = {100, 50, 10, 10, 100, 100, 100};

uint8_t count = 0;
uint8_t colour_index = 0;

boolean button_state = false;
#define BUTTON_DEBOUNCE_TIME 50
#define BUTTON_RESET_TIME 2000
#define BUTTON_PRESS_TIME 1000
uint8_t button_press_count = 0;
uint8_t previous_button_press_count = 0;
unsigned long button_timer = 0;
unsigned long button_press_timer = 0;
boolean button_timeout = false;
boolean button_press_timer_active = false;
int effect_delay = 1000;
unsigned long effect_timer = 0;

void setup() {
  //Serial.begin(115200);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  for(int n = 0; n < 4; n++){
    pinMode(pins[n], OUTPUT);
  }

  

}

void loop() {
  // wait for specified delay time whilst checking state of button
  // check if button pressed and if so take millis
  if(!digitalRead(BUTTON_PIN) && button_state == false){
    button_timer = millis();
    button_state = true;
  }
  // check for button release
  else if(digitalRead(BUTTON_PIN) && button_state == true){
    button_state = false;
    button_timer = millis() - button_timer;
    // was the button pressed for too long?
    if(button_timer > BUTTON_RESET_TIME){
      previous_button_press_count = 0;
      effect_delay = 1000;
      count = 0;
      effect_timer = 0;
      button_press_count = 0;

    }
    // if longer than debounce time find out if within button_press_time and increment count if so else set timeout bit 
    else if(button_timer > BUTTON_DEBOUNCE_TIME){
      if(button_press_count == 0){
        button_press_timer_active = true;
      }
      button_press_count++;
      button_press_timer = millis();    
    }
  }
  else if(((millis() - button_press_timer) > BUTTON_PRESS_TIME) && (button_press_timer_active == true)){
    button_press_timer_active = false;
    button_timeout = true;
  }

  // check if button_timeout is true and respond by setting new display parameters
  if(button_timeout){
    button_timeout = false;
    count = 0;
    previous_button_press_count = button_press_count;
    button_press_count = 0;
    effect_timer = 0;
    if(previous_button_press_count <= EFFECT_COUNT){
      effect_delay = delay_array[previous_button_press_count - 1];
    }
    else{
      effect_delay = 1000;
    }
    
  }

  if((millis() - effect_timer) > effect_delay){
    // update pixel ring based on the previous button press count
    switch(previous_button_press_count){
      case FLASH:
      {
        //ledsOn();
        allFlash();
      }
      break;
      case LOADING:
      {
        //
      }
      break;
      case ALTERNATE_FLASH:
      {
        //
      }
      break;
      case RANDOM_FLASH_INDIVIDUAL:
      {
        //
      }
      break;
      case RANDOM_FLASH_INDIVIDUAL_INVERT:
      {
        //
      }
      break;
      case RANDOM_FLASH_PAIR:
      {
        //
      }
      break;
      case RANDOM_FLASH_PAIR_INVERT:
      {
        //
      }
      default:
      {
        ledsOff();
      }
      break;
    }
    effect_timer = millis();
  }
}

void ledsOn(void){
  for(int n = 0; n < 4; n++){
    digitalWrite(pins[n], HIGH);
  }
}

void ledsOff(void){
  for(int n = 0; n < 4; n++){
    digitalWrite(pins[n], LOW);
  }
}

void allFlash(void){
  int flash_state;
  if(count == 0){
    flash_state = HIGH;
  }
  else if(count == 2){
    flash_state = LOW;
  }
  for(int n = 0; n < 4; n++){
    digitalWrite(pins[n], flash_state);
  }
  count++;
  if(count == 3){
    count = 0;
  }
}

/*

void allLedsOff(void){
  for(int n = 0; n<24; n++){
    strip.setPixelColor(n, off);
  }
  strip.show();
}

void allLedsOn(uint32_t colour){
    for(int n = 0; n<24; n++){
      strip.setPixelColor(n, colour);
    }
    strip.show();
}

void randomRingFlash(void){
  if(count == 0){
    ringColour = Wheel(random(255));
    allLedsOn(ringColour);
  }
  else if(count == 2){
    allLedsOff();
  }

  count++;
  if(count == 3){
    count = 0;
  }
  //delay(100);
}

void randomPixelRingFlash(void){
  if(count == 0){
    for(int n = 0; n<24; n++){
      strip.setPixelColor(n, Wheel(random(255)));
    }
    strip.show();
  }
  else if(count == 2){
    allLedsOff();
  }

  count++;
  if(count == 3){
    count = 0;
  }

  //delay(100);
}

void loading(void){
  for(int n = 0; n<24; n++){
    position_lag = n-count;
    position_lag1 = (n-24)-count;
    if(abs(position_lag1) < abs(position_lag)){
      position_lag = position_lag1;      
    }
    if((position_lag > -4) && (position_lag <= 0)){
      strip.setPixelColor(n,255/(BRIGHTNESS_FACTOR*position_lag),255/(BRIGHTNESS_FACTOR*position_lag),255/(BRIGHTNESS_FACTOR*position_lag));
    }
    else{
      strip.setPixelColor(n, 0,0,0);
    }
  }
  strip.show();
  count++;
  if(count == 24){
    count = 0;
  }
  //delay(100);
}

void rainbow_wheel(){
  for(int n=0; n<24; n++){
    colour_index = count + (n*10);
    strip.setPixelColor(n, Wheel(colour_index));
  }
  strip.show();
  count++;
  //delay(10);
}

void rainbow(){
  for(int m = 0; m< 24; m++){
    strip.setPixelColor(m, Wheel(count));
  }
  strip.show();
  count++;
  //delay(10);
}
*/
