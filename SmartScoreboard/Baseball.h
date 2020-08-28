  #include "Baseball_animations.h"
class Baseball {
  public:
    int outs;
    int strikes;
    byte bases;

    byte top_leds;
    byte diamond_leds;

    int t1_runs, t2_runs;

    int pressType;
    int buttonPressed;
    int buttonPressedTeam;

    baseball_animations base_animations;
    
    int team_pos;

    input_SR * buttons;
    hex_display * hex;
    output_SR * LEDs;
   
    
    Baseball( input_SR * _buttons, hex_display * _hex, output_SR * _LEDs): buttons(_buttons), hex(_hex), LEDs(_LEDs)
    {
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
      int num_runs=0;
      hex->setWord(' ', ' ', ' ', ' ');
       hex->updateDisplay();
       delay(500);
       LEDs->updateLEDs(0, _base);
       base_animations.init_animation(_base,_hit);
       hex->setNumber(num_runs,_hit);
       hex->updateDisplay();
        
       delay(1000);
       
     while(1)
     {
      if (base_animations.play_frame())
      {
        if(base_animations.add_run) num_runs++;
        LEDs->updateLEDs(0, base_animations.curr_bases);
        hex->setNumber(num_runs,_hit);
       hex->updateDisplay();
        delay(300);
      }
      else break;
     }
     delay(500);
  
}



 void extractPressType(){
      buttons->getPressType();
      pressType = buttons->pressType;
      buttonPressed = buttons->buttonPressed;
      buttonPressedTeam = buttons-> buttonPressedTeam;
    }

  
bool updateGameStatus() {return true;}


    void updateScoreboard()
  {
    hex->setNumber(t1_runs, t2_runs);
    
     
  }
  
  bool updateGame(){
      extractPressType();
      if(!updateGameStatus()) {return false;}
      updateScoreboard();
      return true;
    }

    void initGame(){
      outs = 0;
      strikes = 0;
      bases = 0b1000;
      team_pos = 1;
      t1_runs = 0;
      t2_runs = 0;
      //add_runs = 0;
       debug_animation_all();
      hex->showWord('b', 'a', 's', 'e');
      delay(700);
      hex->showWord('b', 'a', 'l', 'l');
      delay(700);
    }

   
};
