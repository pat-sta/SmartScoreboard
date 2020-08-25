#include <ds3231.h>
#include "Baseball_animations.h"

class clk_module {
  public:

byte top_leds;
byte diamond_leds;

  
struct ts t;
int dayofweek;

baseball_animations base_animations;
int pressType;
int buttonPressed;
int buttonPressedTeam;

input_SR * buttons;
hex_display * hex;
output_SR * LEDs;

clk_module( input_SR * _buttons, hex_display * _hex, output_SR * _LEDs): buttons(_buttons), hex(_hex), LEDs(_LEDs)
    {
    }

    
void extractPressType(){
      buttons->getPressType();
      pressType = buttons->pressType;
      buttonPressed = buttons->buttonPressed;
      buttonPressedTeam = buttons-> buttonPressedTeam;
    }

int weekday(){
  int adjustment, mm, yy;
  if (t.year < 2000) t.year += 2000;
  adjustment = (14 - t.mon) / 12;
  mm = t.mon + 12 * adjustment - 2;
  yy = t.year - adjustment;
  return (t.mday + (13 * mm - 1) / 5 +
          yy + yy / 4 - yy / 100 + yy / 400) % 7;
}

void debug_animation_all(){
  byte bases [8] = {0b1000,0b1100,0b1010,0b1001,0b1110,0b1011,0b1101,0b1111};
  int hits [4] = {1,2,3,4};
  for (int i=0; i<8; i++){
    for (int j=0; j<4; j++){
      debug_animation(bases[i], hits[j],i);
    }
  }
  
  
}

void debug_animation(byte _base, int _hit, int _instance){

      
       LEDs->updateLEDs(0, _base);
       base_animations.init_animation(_base,_hit);
       hex->setNumber(_instance,_hit);
       hex->updateDisplay();
        
       delay(1000);
       
     while(1)
     {
      if (base_animations.play_frame())
      {
        LEDs->updateLEDs(0, base_animations.curr_bases);
        delay(400);
      }
      else break;
     }
  
}

void initGame(){
    
    debug_animation_all();

  
      hex->showWord(' ', ' ', ' ', ' ');
      delay(300);
      hex->showWord('c', 'l', 'c', 'k');
      delay(1400);
      hex->showWord(' ', ' ', ' ', ' ');
      delay(300);
      Wire.begin();
      DS3231_init(DS3231_CONTROL_INTCN);
    }

    bool updateGame(){
      extractPressType();
      if(!updateGameStatus()) {return false;}
      updateScoreboard();
      return true;
    }


   bool updateGameStatus(){
      DS3231_get(&t);
      t.hour = t.hour < 13 ? (t.hour) : (t.hour - 12);
      dayofweek = weekday();  
     
    if(dayofweek==3) {diamond_leds=0b0010;}
    else{diamond_leds=0b0000;}

    if     (dayofweek=0){ top_leds = 0b100000; }
    else if(dayofweek=1){ top_leds = 0b010000; }
    else if(dayofweek=2){ top_leds = 0b001000; }
    else if(dayofweek=3){ top_leds = 0b000000; }
    else if(dayofweek=4){ top_leds = 0b000100; }
    else if(dayofweek=5){ top_leds = 0b000010; }
    else if(dayofweek=6){ top_leds = 0b000001; }
    if(buttonPressed==5 && pressType==3){return false;}
      return true;
       
    }

void updateScoreboard(){
  //LEDs->updateLEDs(top_leds, diamond_leds);
  hex->showNumber(t.hour, t.min);
}



void setTime(int _hour, int _min, int _sec, int _mday, int _mon, int _year) {
  t.hour = _hour;
  t.min = _min;
  t.sec = _sec;
  t.mday = _mday;
  t.mon = _mon;
  t.year = _year;
  DS3231_set(t);
}


  
  


  
  


  


};
