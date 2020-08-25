class ping_pong {
  public:
    
    int t1_score, t2_score;
    int t1_round, t2_round;
    int team_pos;

    int pressType;
    int buttonPressed;
    int buttonPressedTeam;

    input_SR * buttons;
    hex_display * hex;
    output_SR * LEDs;

    ping_pong( input_SR * _buttons, hex_display * _hex, output_SR * _LEDs): buttons(_buttons), hex(_hex), LEDs(_LEDs)
    {
    }
    

    void extractPressType()
    {
      buttons->getPressType();
      pressType = buttons->pressType;
      buttonPressed = buttons->buttonPressed;
      buttonPressedTeam = buttons-> buttonPressedTeam;
    }

    void initGame()
    {
      t1_score=0;
      t2_score=0;
      t1_round=0;
      t2_round=0;
      team_pos=0;
      
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

    

    
    bool updateGame(){
      extractPressType();
      if(!updateGameStatus()) {return false;}
      updateScoreboard();
      return true;
    }

    bool updateGameStatus()
    {
      if(buttonPressed==1){
        if(pressType==1){
          if(buttonPressedTeam==1){
            team_pos=1;
            if(t1_score <100) {t1_score++;}
          }
          else if(buttonPressedTeam==2){
            team_pos=2;
            if(t2_score <100) {t2_score++;}
          }
        }
        
      }
      else if(buttonPressed==2){
        if(pressType==1){
          if(buttonPressedTeam==1){
            if(t1_score >0) {t1_score--;};
          }
          else if(buttonPressedTeam==2){
             if(t2_score >0) {t2_score--;}
          }
        }
        
      }
      else if(buttonPressed==3){
        t1_score =0;
        t2_score =0;
        team_pos=0;
      }
       else if(buttonPressed==4){
   
      }
      else if(buttonPressed==5){
        if(pressType==3){
          return false;
         }
      }
        hex->setNumber(t1_score,t2_score);
        if(team_pos==1) {hex->addDecimal(1);}
        else if(team_pos==2) {hex->addDecimal(3);}
      
      return true;
      }

     void updateScoreboard()
    {

      LEDs->updateLEDs(0, 0);
       hex->updateDisplay();
      //delay(1000);
//       hex->setWord(0,3,0,4);
//       hex->addDecimal(3);
//       hex->updateDisplay();
//       delay(1000);
    
    }


    
};