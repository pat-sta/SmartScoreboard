/*  data = ABCDEFGH
        MSB -> LSB
            H
           ---
        G | F | B
           ---
        E |   | C
           ---  o A
            D
*/






#include <SPI.h>
class input_SR
{
  public:
    byte shift_1;
    byte shift_2;

    int pressType;
    int buttonPressed;
    int buttonPressedTeam;
    
    int PL;

    void DataShiftIn() {
      digitalWrite(PL, LOW);
      delay(1);
      digitalWrite(PL, HIGH);
      shift_1 = SPI.transfer(0x00);
      shift_2 = SPI.transfer(0x00);
    }

    
    void updateStates() {
     
    }


    void init()
    {
      pressType=0;
      buttonPressed=0;
      buttonPressedTeam=-1;
    }
    
    
    input_SR(int _PL) : PL(_PL) {
      pinMode(PL, OUTPUT);
      SPI.setClockDivider(SPI_CLOCK_DIV128);
      SPI.setDataMode(SPI_MODE0);
      SPI.setBitOrder(MSBFIRST);
      SPI.begin();
      init();
    }
   
   int getPressType() {
      DataShiftIn();
     unsigned long time_pressed;
     unsigned long new_time_pressed;
     int tmp;
     if(shift_1 != 0b11111000) {
        tmp=1;
        bool button_release = false;
       //Serial.println(shift_1, BIN);
       time_pressed= millis();
       new_time_pressed= millis();
       analogWrite(6, 100);
       if(shift_1 <= 0b01111000) {
        while(shift_1 <= 0b01111000 || (millis() - time_pressed <400))
        { 
          if ((millis() - time_pressed) < 400){
            if (shift_1 > 0b01111000) button_release = true;
            if (button_release == true && shift_1 <= 0b01111000) {
              tmp =2;
                new_time_pressed= millis();
            }
          }
          else if ((millis() - time_pressed) > 600 && !button_release)
          {
            analogWrite(6, 100);
          }
          else if ((millis() - time_pressed) > 400 && !button_release) {
            analogWrite(6, 0);
            tmp=4;}
          
           else if ((millis() - new_time_pressed) > 600 && (button_release))
          {
            analogWrite(6, 100);
          }
           else if ((millis() - new_time_pressed) > 400 && ( button_release)) {
            analogWrite(6, 0);
            tmp=3;}
         
          DataShiftIn();}
          //Serial.println(millis() - time_pressed);
        return tmp;
       }
        
       if(shift_1 <= 0b10111000) return 2;
       if(shift_1 <= 0b11011000) return 3;
       if(shift_1 <= 0b11101000) return 4;
       if(shift_1 <= 0b11110000) return 5;
       }
       if(shift_2 != 0b11111000) {
       //Serial.println(shift_2, BIN);
       if(shift_2 <= 0b01111000) {
          ;
         while(shift_2 <= 0b01111000){DataShiftIn();} 
         return 1;
       }
       if(shift_2 <= 0b10111000) return 2;
       if(shift_2 <= 0b11011000) return 3;
       if(shift_2 <= 0b11101000) return 4;
       if(shift_2 <= 0b11110000) return 5;
       }
       return 0;
     
    }
};


class hex_display
{ public:
    int segmentLatch;
    int segmentClock;
    int segmentData;

    hex_display( int _segmentLatch, int _segmentClock, int _segmentData):
      segmentLatch(_segmentLatch), segmentClock(_segmentClock), segmentData(_segmentData)
    {
      pinMode(segmentLatch, OUTPUT);
      pinMode(segmentClock, OUTPUT);
      pinMode(segmentData, OUTPUT);
    }

    //Given a number, or '-', shifts it out to the display
    void postNumber(byte number)
    {
      byte segments;
      switch (number)
      {
        //Numbers
        case 1: segments = 0b01100000; break;
        case 2: segments = 0b01011101; break;
        case 3: segments = 0b01110101; break;
        case 4: segments = 0b01100110; break;
        case 5: segments = 0b00110111; break;
        case 6: segments = 0b00111111; break;
        case 7: segments = 0b01100001; break;
        case 8: segments = 0b01111111; break;
        case 9: segments = 0b01110111; break;
        case 0: segments = 0b01111011; break;

        case ' ': segments = 0b00000000; break;

        case 'a': segments = 0b01101111; break;
        case 'b': segments = 0b00111110; break;
        case 'c': segments = 0b00011011; break;
        case 'd': segments = 0b01111100; break;
        case 'e': segments = 0b00011111; break;
        case 'f': segments = 0b00001111; break;
        case 'g': segments = 0b01110111; break;
        case 'h': segments = 0b00101110; break;
        case 'i': segments = 0b01100000; break;
        case 'j': segments = 0b01110000; break;
        case 'k': segments = 0b00101111; break;
        case 'l': segments = 0b00011010; break;
        case 'm': segments = 0b00101001; break;
        case 'n': segments = 0b01101011; break;
        case 'o': segments = 0b01111011; break;
        case 'p': segments = 0b01001111; break;
        case 'q': segments = 0b01100111; break;
        case 'r': segments = 0b00001011; break; // make lowercase?
        case 's': segments = 0b00110111; break;
        case 't': segments = 0b00011110; break;
        case 'u': segments = 0b01111010; break;
        case 'v': segments = 0b00111000; break;
        case 'w': segments = 0b00111001; break;
        case 'x': segments = 0b01101110; break;
        case 'y': segments = 0b01110110; break;
        case 'z': segments = 0b01011101; break;
      }

      //Clock these bits out to the drivers
      for (byte x = 0 ; x < 8 ; x++)
      {
        digitalWrite(segmentClock, LOW);
        digitalWrite(segmentData, segments & 1 << (7 - x));
        digitalWrite(segmentClock, HIGH); //Data transfers to the register on the rising edge of SRCK
      }
    }

    void postNumber(byte number, boolean decimal)
    {
      byte segments;
      switch (number)
      {
        case 1: segments = 0b01100000; break;
        case 2: segments = 0b01011101; break;
        case 3: segments = 0b01110101; break;
        case 4: segments = 0b01100110; break;
        case 5: segments = 0b00110111; break;
        case 6: segments = 0b00111111; break;
        case 7: segments = 0b01100001; break;
        case 8: segments = 0b01111111; break;
        case 9: segments = 0b01110111; break;
        case 0: segments = 0b01111011; break;

        case ' ': segments = 0b00000000; break;

        case 'a': segments = 0b01101111; break;
        case 'b': segments = 0b00111110; break;
        case 'c': segments = 0b00011011; break;
        case 'd': segments = 0b01111100; break;
        case 'e': segments = 0b00011111; break;
        case 'f': segments = 0b00001111; break;
        case 'g': segments = 0b01110111; break;
        case 'h': segments = 0b00101110; break;
        case 'i': segments = 0b01100000; break;
        case 'j': segments = 0b01110000; break;
        case 'k': segments = 0b00101111; break;
        case 'l': segments = 0b00011010; break;
        case 'm': segments = 0b00101001; break;
        case 'n': segments = 0b01101011; break;
        case 'o': segments = 0b01111011; break;
        case 'p': segments = 0b01001111; break;
        case 'q': segments = 0b01100111; break;
        case 'r': segments = 0b00001011; break; // make lowercase?
        case 's': segments = 0b00110111; break;
        case 't': segments = 0b00011110; break;
        case 'u': segments = 0b01111010; break;
        case 'v': segments = 0b00111000; break;
        case 'w': segments = 0b00111001; break;
        case 'x': segments = 0b01101110; break;
        case 'y': segments = 0b01110110; break;
        case 'z': segments = 0b01011101; break;
      }
      segments = segments + 0b10000000;
      //Clock these bits out to the drivers
      for (byte x = 0 ; x < 8 ; x++)
      {
        digitalWrite(segmentClock, LOW);
        digitalWrite(segmentData, segments & 1 << (7 - x));
        digitalWrite(segmentClock, HIGH); //Data transfers to the register on the rising edge of SRCK
      }
    }

    void showWord(byte char1, byte char2, byte char3, byte char4)
    {
      digitalWrite(segmentLatch, LOW);
      postNumber(char4);
      postNumber(char3);
      postNumber(char2);
      postNumber(char1);
      digitalWrite(segmentLatch, HIGH);
    }

    void showNumber(float value) {
      int remainder;
      int number = abs(value);
      digitalWrite(segmentLatch, LOW);
      for (byte x = 0 ; x < 4 ; x++) {
        remainder = number % 10;
        postNumber(remainder);
        number /= 10;
      }
      digitalWrite(segmentLatch, HIGH);
    }

    void showNumber(float value1, float value2) {
      int remainder;
      int number = abs(value2);
      digitalWrite(segmentLatch, LOW);
      for (byte x = 0 ; x < 2 ; x++) {
        remainder = number % 10;
        postNumber(remainder);
        number /= 10;
      }
      number = abs(value1);
      for (byte x = 0 ; x < 2 ; x++) {
        remainder = number % 10;
        postNumber(remainder);
        number /= 10;
      }
      digitalWrite(segmentLatch, HIGH);
    }


};

class output_SR
{
  public:
    int latchPin;
    int clockPin;
    int dataPin;
    output_SR(int _latchPin, int _clockPin, int _dataPin):
      latchPin(_latchPin), clockPin(_clockPin), dataPin(_dataPin)
    {
      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
    }

    void shiftOut(byte data) {

      //internal function setup
      int i = 0;
      int pinState;
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);

      //clear everything out
      digitalWrite(dataPin, 0);
      digitalWrite(clockPin, 0);

      for (i = 7; i >= 0; i--)  {
        digitalWrite(clockPin, 0);
        if ( data & (1 << i) ) {
          pinState = 1;
        }
        else {
          pinState = 0;
        }

        //Sets the pin to HIGH or LOW depending on pinState
        digitalWrite(dataPin, pinState);
        //register shifts bits on upstroke of clock pin
        digitalWrite(clockPin, 1);
        //zero the data pin after shift to prevent bleed through
        digitalWrite(dataPin, 0);
      }

      //stop shifting
      digitalWrite(clockPin, 0);
    }

};

input_SR buttons(8);
hex_display hex(4, 3, 2);
output_SR LEDs(15, 16, 17);
void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  
  
  analogWrite(6, 100);

    Serial.println("Initialized");
}

int a;
void loop() {
a =buttons.getPressType();

  switch (a)
  {
    case 0: break;

    default: Serial.println(a);
//             Serial.print("Button Pressed: ");
//              Serial.println(buttons.buttonPressed);
//             Serial.print("Team Button Pressed: "); 
//              Serial.println(buttons.buttonPressedTeam);
//             Serial.print("Press Type: ");
//               Serial.println(buttons.pressType);
//             Serial.print("Press Type: ");
//               Serial.println(buttons.pressType);
//               Serial.println();
               break;
  }


  //hex.showNumber(35, 4);
  delay(100);





}



//
//
//
//class Scoreboard
//{
//    hex_display * hex_display;
//
//
//  public:
//
//
//    void updateLEDs(byte top, byte diamond) {
//      hex_display->shiftOut(top);
//      hex_display->shiftOut(diamond);
//    }
//
//    byte topLEDSaccum_SO(int first, int second)
//    {
//      if (first == 0 && second == 0) return 0b000000;
//      else if (first == 0 && second == 1) return 0b000001;
//      else if (first == 0 && second == 2) return 0b000011;
//      else if (first == 0 && second == 3) return 0b000111;
//
//      else if (first == 1 && second == 0) return 0b100000;
//      else if (first == 1 && second == 1) return 0b100100;
//      else if (first == 1 && second == 2) return 0b100110;
//      else if (first == 1 && second == 3) return 0b100111;
//
//
//      else if (first == 2 && second == 0) return 0b110000;
//      else if (first == 2 && second == 1) return 0b110100;
//      else if (first == 2 && second == 2) return 0b110110;
//      else if (first == 2 && second == 3) return 0b110111;
//
//      else if (first == 3 && second == 0) return 0b111000;
//      else if (first == 3 && second == 1) return 0b111100;
//      else if (first == 3 && second == 2) return 0b111110;
//      else return 0b111111;
//    }
//
//
//
//};
//
//int white = 8; // strike
//int yellow = 9; // hr
//int blue = 10; //triple
//int red = 11; //double
//int green = 12; //single
//
//int num_runs = 0;
//int add_runs = 0;
//int press_type = 0;
//
//Scoreboard myScoreboard(14, 15, 16);
//
//void setup() {
//  //Start Serial for debuging purposes
//  Serial.begin(9600);
//  //set pins to output because they are addressed in the main loop
//
//  pinMode(green, INPUT);
//  pinMode(red, INPUT);
//  pinMode(blue, INPUT);
//  pinMode(yellow, INPUT);
//  pinMode(white, INPUT);
//  Serial.println("Initializing");
//  {
//    Serial.println((String)"Number of Runs: " + num_runs);
//  }
//
//
//}
//
//// random flip
//
//
//byte round_SR;
//byte base_SR;
//int strikes = 0;
//int outs = 0;
//
//int button_curr [5] = {0, 0, 0, 0, 0};
//int button_prev [5] = {0, 0, 0, 0, 0};
//
//byte bases = 0b000;
//
//int press_code( int button_curr[5], int button_prev[5])
//{
//  int code = 0;
//  for (int i = 0; i < 5; i++) {
//    if (!button_prev[i] && button_curr[i])
//      code = i + 1;
//  }
//  return code;
//}
//
//void print_action(int press_type) {
//  switch (press_type) {
//    case 1: Serial.println("---\nSingle");
//
//      break;
//    case 2: Serial.println("---\nDouble");
//      break;
//    case 3: Serial.println("---\nTriple");
//      break;
//    case 4: Serial.println("---\nHome Run");
//      break;
//    case 5: Serial.println("---\nStrike");
//      break;
//    default:
//      break;
//  }
//}
//
//int enable_home(int en) {
//  return 8 * en;
//}
//
//
//int CountRunners(byte bases)
//{
//  return (bases == 0) ? 0 : (bases & 1) + CountRunners(bases >> 1);
//}
//
//void update_bases(byte& bases, int press_type, int& add_runs) {
//  byte new_bases = bases;
//  add_runs = 0;
//  switch (press_type) {
//    case 1: // Single
//      switch (bases) {
//        case 0b000:
//          new_bases = 0b100;
//          break;
//        case 0b001:
//          new_bases = 0b101;
//          break;
//        case 0b100: case 0b010:
//          new_bases = 0b110;
//          break;
//        default:
//          new_bases = 0b111;
//          break;
//      }
//      break;
//
//    case 2: // Double
//      switch (bases) {
//        case 0b000:
//          new_bases = 0b010;
//          break;
//        default:
//          new_bases = 0b011;
//          break;
//      }
//      break;
//
//    case 3: // Triple
//      new_bases = 0b001;
//      break;
//
//    case 4: // HomeRun
//      new_bases = 0b000;
//      break;
//  }
//  if (press_type != 0 && press_type != 5)
//    add_runs = CountRunners(bases) + 1 - CountRunners(new_bases);
//  bases = new_bases;
//}
//
//
//
//
//void loop() {
//
//
//
//  // Data gathering
//
//
//  button_curr[0] = !digitalRead(green);
//  button_curr[1] = !digitalRead(red);
//  button_curr[2] = !digitalRead(blue);
//  button_curr[3] = !digitalRead(yellow);
//  button_curr[4] = !digitalRead(white);
//
//  press_type = press_code(button_curr, button_prev);
//
//  print_action(press_type);
//
//  update_bases(bases, press_type, add_runs);
//  num_runs += add_runs;
//  if (add_runs != 0)
//  {
//    Serial.println((String)"Number of Runs: " + num_runs);
//  }
//
//
//  if (press_type != 0 && press_type != 5) {
//    myScoreboard.updateLEDs(myScoreboard.topLEDSaccum_SO(strikes, outs), bases + enable_home(0));
//    delay(750);
//  }
//
//  myScoreboard.updateLEDs(myScoreboard.topLEDSaccum_SO(strikes, outs), bases + enable_home(1));
//
//
//  for (int i = 0; i < 5; i++) {
//    button_prev[i] = button_curr[i];
//  }
//
//
//
//  delay(50);
//
//}
//
//
//
//
//
//
//
//
//void shiftOut(byte myDataOut) {
//  //internal function setup
//  int i = 0;
//  int pinState;
//
//  //clear everything out just in case to
//  //prepare shift register for bit shifting
//  digitalWrite(dataPin, 0);
//  digitalWrite(clockPin, 0);
//
//  for (i = 7; i >= 0; i--)  {
//    digitalWrite(clockPin, 0);
//    if ( myDataOut & (1 << i) ) {
//      pinState = 1;
//    }
//    else {
//      pinState = 0;
//    }
//
//    //Sets the pin to HIGH or LOW depending on pinState
//    digitalWrite(dataPin, pinState);
//    //register shifts bits on upstroke of clock pin
//    digitalWrite(clockPin, 1);
//    //zero the data pin after shift to prevent bleed through
//    digitalWrite(dataPin, 0);
//  }
//  //stop shifting
//  digitalWrite(clockPin, 0);
//}
