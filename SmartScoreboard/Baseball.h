class Baseball {
  public:
    int outs;
    int strikes;
    byte bases;

    int StrikeOut_SO;

    int add_runs;
    int t1_runs, t2_runs;

    int pressType;
    int buttonPressed;
    int buttonPressedTeam;
    
    int curr_team;

    input_SR * buttons;
    hex_display * hex;
    output_SR * LEDs;

    Baseball( input_SR * _buttons, hex_display * _hex, output_SR * _LEDs): buttons(_buttons), hex(_hex), LEDs(_LEDs)
    {
    }
    int enable_home(int en) {
    return 8 * en;
  }


 void extractPressType(){
      buttons->getPressType();
      pressType = buttons->pressType;
      buttonPressed = buttons->buttonPressed;
      buttonPressedTeam = buttons-> buttonPressedTeam;
    }

    void foul(){
      
    }
     void strike(){
      
    }

    void singleHit(){
      
    }

    void doubleHit(){
      
    }

    void tripleHit(){
      
    }

    void homerunHit(){
      
    }
void updateGameStatus() {
//      if (pressID == 5){
//        strikes ++;
//        Serial.println(strikes);
//      }
//      if (pressID == 6){
//        strikes = 0;
//        outs ++;
//      }
//      if (strikes == 3) {
//        strikes = 0;
//        outs ++;
//      }
//      if (outs == 3) {
//        strikes = 0;
//        outs = 0;
//        changePosession();
//      }
    }

      void updateScoreboard()
    {
       //hex->showNumber(t1_score,t2_score);
    
    }
    
 void updateGame(){
      extractPressType();
      updateGameStatus();
      updateScoreboard();
    }

    void initGame(){
      outs = 0;
      strikes = 0;
      bases = 0b0000;
      curr_team = 1;
      t1_runs = 0;
      t2_runs = 0;
      add_runs = 0;

      hex->showWord('b', 'a', 's', 'e');
      delay(700);
      hex->showWord('b', 'a', 'l', 'l');
      delay(700);
    }

    void changePosession() {
      Serial.println("Changed Posession");
      outs = 0;
      strikes = 0;
      bases = 0b0000;
      curr_team = (curr_team == 1 ) ? 2 : 1;
      Serial.print("Batting: Team ");
      Serial.println(curr_team);
    }

    
    void updateButtonLights() {
      switch (curr_team)
      {
        case 0:
          //buttons->set_LED_brightness(0,0);
          break;
        case 1:
          //buttons->set_LED_brightness(150,30);
          break;
        case 2:
          // buttons->set_LED_brightness(150,30);
          //buttons->set_LED_brightness(30,150);
          break;
        default: break;
      }
    }
  

    int CountRunners(byte bases) {
      return (bases == 0) ? 0 : (bases & 1) + CountRunners(bases >> 1);
    }

    void updateBases() {
      byte new_bases = bases;
      add_runs = 0;

    
//      switch (pressID) {
//        case 1: // Single
//          Serial.println("Here");
//          switch (bases) {
//            case 0b000:
//              new_bases = 0b100;
//              break;
//            case 0b001:
//              new_bases = 0b101;
//              break;
//            case 0b100: case 0b010:
//              new_bases = 0b110;
//              break;
//            default:
//              new_bases = 0b111;
//              break;
//          }
//          break;
//
//        case 2: // Double
//          //Serial.println("Here");
//          switch (bases) {
//            case 0b000:
//              new_bases = 0b010;
//              break;
//            default:
//              new_bases = 0b011;
//              break;
//          }
//          break;
//
//        case 3: // Triple
//          //Serial.println("Here");
//          new_bases = 0b001;
//          break;
//
//        case 4: // HomeRun
//          //Serial.println("Here");
//          new_bases = 0b000;
//          break;
//      }
//      if (buttons->buttonPressed != 0 && buttons->buttonPressed != 5)
//        add_runs = CountRunners(bases) + 1 - CountRunners(new_bases);
//      bases = new_bases;
    }
};
