  #include "Baseball_animations.h"
  #include "game.h"
class Baseball: public Game {
  public:
    int outs;
    int strikes;
    byte bases;

    int team_pos;
    int t1_runs, t2_runs;

    baseball_animations base_animations;
   
    Baseball( input_SR * _buttons, hex_display * _hex, output_SR * _LEDs): Game(_buttons,_hex, _LEDs) {}


   void debug_animation_all(){
      byte bases [8] = {0b1000,0b1100,0b1010,0b1001,0b1110,0b1011,0b1101,0b1111};
      int hits [4] = {1,2,3,4};
      for (int i=0; i<8; i++){
        for (int j=0; j<4; j++){
          debug_animation(bases[i], hits[j]);
        }
  }
  
  
}
void hit_update(int _hit){
  delay(300);
  strikes=0;
  base_animations.init_animation(bases,_hit);
   while(1){
      if (base_animations.play_frame()){
        if(base_animations.add_run) add_run();
        bases = base_animations.curr_bases;
       updateScoreboard();
        delay(300);
      }
      else break;
     }
  
}


void add_run(){
  if (team_pos ==1) t1_runs++;
  else t2_runs++;
}



void debug_animation(byte _base, int _hit){
      int num_runs=0;
      hex->showWord(' ', ' ', ' ', ' ');
       delay(500);
       LEDs->updateLEDs(0, _base);
       base_animations.init_animation(_base,_hit);
       hex->setNumber(num_runs,_hit);
       hex->updateDisplay();
        
       delay(1000);
       
     while(1){
      if (base_animations.play_frame()){
        if(base_animations.add_run) num_runs++;
        LEDs->updateLEDs(0, base_animations.curr_bases);
        hex->setNumber(num_runs,_hit);
       hex->updateDisplay();
        delay(500);
      }
      else break;
     }
     delay(500);
  
}

void strike(){
  strikes ++;
  if(strikes>2) {
    updateScoreboard();
   delay(500);
    out();
  }
}


void updateTopLEDs(){
  top_leds=0;
  if (outs>2) bitSet(top_leds,0);
  if (outs>1) bitSet(top_leds,1);
  if (outs>0) bitSet(top_leds,2);
  if (strikes>2) bitSet(top_leds,3);
   if (strikes>1) bitSet(top_leds,4);
    if (strikes>0) bitSet(top_leds,5);
}

void out(){
 
  strikes =0;
  outs++;
  if (outs>2) {
    updateScoreboard();
    delay(500);
    changePosession();
  }
}

void changePosession(){
 if (team_pos ==1) team_pos =2;
 else team_pos =1; 
 clearRound();
 
}

void clearRound(){
   strikes=0;
   outs = 0;
   bases = 0b0000;
   updateScoreboard();
   delay(1000);
   bases = 0b1000;
   updateScoreboard();
}


  bool updateGameStatus() {
    if (pressType==3 && buttonPressed ==5) return false;
    if (buttonPressedTeam == team_pos){
      if(buttonPressed==1){
        if (pressType == 1) hit_update(1);
        else if (pressType == 2) hit_update(4);
      }
      else  if(buttonPressed==2){
       if (team_pos== buttonPressedTeam) hit_update(2);
      }
      else  if(buttonPressed==3){
       if (team_pos== buttonPressedTeam) hit_update(3);
      }
      else  if(buttonPressed==4){
       if (team_pos== buttonPressedTeam) strike();
      }
      else  if(buttonPressed==5){
       if (team_pos== buttonPressedTeam) out();
      }
      
    }
    return true;
}



  void updateScoreboard(){
     hex->setNumber(t1_runs, t2_runs);
    if (team_pos == 1) hex-> addDecimal(1);
    else hex-> addDecimal(3);
    hex->updateDisplay();
    updateTopLEDs();
    LEDs->updateLEDs(top_leds, bases);
}

    void initGame(){
      
      
      team_pos = 1;
      t1_runs = 0;
      t2_runs = 0;
      hex->showWord('b', 'a', 's', 'e');
      delay(700);
      hex->showWord('b', 'a', 'l', 'l');
      delay(700);
      clearRound();
      
    }

   
};
