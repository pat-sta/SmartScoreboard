#ifndef PING_PONG_H
#define PING_PONG_H



#include "game.h"

class ping_pong :public Game {
  public:
    
    int t1_score, t2_score;
    int t1_round, t2_round;
    int team_pos;

ping_pong( input_SR * _buttons, hex_display * _hex, output_SR * _LEDs): Game(_buttons,_hex, _LEDs) {}

    void initGame(){
      t1_score=0;
      t2_score=0;
      t1_round=0;
      t2_round=0;
      team_pos=1;
      
      hex->showWord(' ', ' ', ' ', ' ');
      delay(300);
      hex->showWord('p', 'i', 'n', 'g');
      delay(700);
       hex->showWord(' ', ' ', ' ', ' ');
      delay(200);
      hex->showWord('p', 'o', 'n', 'g');
      delay(700);
      hex->showWord(' ', ' ', ' ', ' ');
      delay(200);
      
    }

     bool updateGameStatus()
    {
      if(buttonPressed==1){
       if (t1_score <99) t1_score++;
      }
      else if (buttonPressed==2){
        if (t1_score >0) t1_score--;
      }
      else if (buttonPressed==3){
        if (t1_score <99) t2_score++;
      }
      else if (buttonPressed==4){
        if (t2_score >0) t2_score--;
      }
      else if (buttonPressed==5){
        t1_score =0;
        t2_score =0;
        
        
      }
      if (pressType==3 && buttonPressed ==5) return false;
      return true;
    }
    
     void updateScoreboard()
    {
       LEDs->updateLEDs(0, 0);
       hex->setNumber(t1_score, t2_score);
       hex->updateDisplay();    
    }


    
};

#endif // PING_PONG_H
