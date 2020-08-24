#include <ds3231.h>


class clk_module {
  public:

byte top_leds;
byte diamond_leds;

  
struct ts t;
int dayofweek;


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


void initGame(){
      hex->showWord('p', 'i', 'n', 'g');
      delay(700);
      Wire.begin();
      DS3231_init(DS3231_CONTROL_INTCN);
    }

   void updateGame(){
      extractPressType();
      updateGameStatus();
      updateScoreboard();
    }


   void updateGameStatus(){
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
   
    }

void updateScoreboard(){
  LEDs->updateLEDs(top_leds, diamond_leds);
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
