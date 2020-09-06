#ifndef GAME_H
#define GAME_H


#include "hex_display.h"
#include "input_SR.h"
#include "output_SR.h"

class Game{
public:
	  input_SR * buttons;
    hex_display * hex;
    output_SR * LEDs;
    
    byte top_leds;
    byte diamond_leds;

    int pressType;
    int buttonPressed;
    int buttonPressedTeam;

virtual bool updateGameStatus(){}
virtual void updateScoreboard(){}
virtual void initGame(){}

Game( input_SR * _buttons, hex_display * _hex, output_SR * _LEDs): buttons(_buttons), hex(_hex), LEDs(_LEDs) {}
void extractPressType(){
      buttons->getPressType();
      pressType = buttons->pressType;
      buttonPressed = buttons->buttonPressed;
      buttonPressedTeam = buttons-> buttonPressedTeam;
    }

   bool updateGame(){
    extractPressType();
    if(!updateGameStatus()) {return false;}
    updateScoreboard();
    return true;
  }

};
#endif // GAME_H
