
//**************************************************************//
//  Name    : shiftOutCode, Dual Binary Counters                 //
//  Author  : Carlyn Maw, Tom Igoe                               //
//  Date    : 25 Oct, 2006                                       //
//  Version : 1.0                                                //
//  Notes   : Code for using a 74HC595 Shift Register            //
//          : to count from 0 to 255                             //
//**************************************************************//

//Pin connected to ST_CP of 74HC595
int latchPin = 14; //yellow
//Pin connected to SH_CP of 74HC595
int clockPin = 15; //green
////Pin connected to DS of 74HC595
int dataPin = 16; //blue

int white = 8; // strike
int yellow = 9; // hr
int blue = 10; //triple
int red = 11; //double
int green = 12; //single

int num_runs=0;
int add_runs =0;
int press_type=0;

void setup() {
  //Start Serial for debuging purposes  
  Serial.begin(9600);
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
   pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(green, INPUT);
  pinMode(red, INPUT);
  pinMode(blue, INPUT);
  pinMode(yellow, INPUT);
   pinMode(white, INPUT);
   Serial.println("Initializing");
  {  Serial.println((String)"Number of Runs: " + num_runs);}
  

}

// random flip


byte strike_out_shift_out( int strikes, int outs)
{
        if (strikes ==0 && outs ==0) return 0b000000;
   else if (strikes ==0 && outs ==1) return 0b000001;
   else if (strikes ==0 && outs ==2) return 0b000011;
   else if (strikes ==0 && outs ==3) return 0b000111;
  
  else if (strikes ==1 && outs ==0) return 0b100000;
  else if (strikes ==1 && outs ==1) return 0b100100;
  else if (strikes ==1 && outs ==2) return 0b100110;
  else if (strikes ==1 && outs ==3) return 0b100111;
  

  else if (strikes ==2 && outs ==0) return 0b110000;
  else if (strikes ==2 && outs ==1) return 0b110100;
  else if (strikes ==2 && outs ==2) return 0b110110;
  else if (strikes ==2 && outs ==3) return 0b110111;

   else if (strikes ==3 && outs ==0) return 0b111000;
  else if (strikes ==3 && outs ==1) return 0b111100;
  else if (strikes ==3 && outs ==2) return 0b111110;
  else return 0b111111;
}

byte round_SR;
byte base_SR;
int strikes = 0;
int outs = 0;

int button_curr [5]= {0,0,0,0,0};
int button_prev [5] = {0,0,0,0,0};

byte bases = 0b000;

int press_code( int button_curr[5], int button_prev[5])
{
  int code=0;
  for (int i =0; i <5; i++){
    if (!button_prev[i] && button_curr[i])
      code= i+1;
     }
   return code;
}

void print_action(int press_type) {
switch (press_type){
      case 1: Serial.println("---\nSingle");
          
        break;
      case 2: Serial.println("---\nDouble");
        break;
      case 3: Serial.println("---\nTriple");
        break;
      case 4: Serial.println("---\nHome Run");
        break;
      case 5: Serial.println("---\nStrike");
        break;
      default:
        break;
    }
}

int enable_home(int en) {return 8*en;}


int CountRunners(byte bases)
{
    return (bases==0)? 0: (bases & 1) + CountRunners(bases >> 1);
}

void update_bases(byte& bases, int press_type, int& add_runs){
 byte new_bases = bases;
 add_runs =0;
 switch (press_type) {
    case 1: // Single
      switch(bases) {
        case 0b000:
          new_bases = 0b100;
          break;
         case 0b001:
           new_bases = 0b101;
           break;
        case 0b100: case 0b010:
          new_bases = 0b110;
          break;
         default:
           new_bases = 0b111;
           break;
      }
      break;
      
    case 2: // Double
      switch(bases) {
        case 0b000:
          new_bases = 0b010;
          break;
        default:
          new_bases = 0b011;
          break;
      }
      break;
      
    case 3: // Triple
      new_bases = 0b001;
      break;
    
    case 4: // HomeRun
      new_bases= 0b000;
      break;
 }
 if (press_type != 0 && press_type != 5)
  add_runs = CountRunners(bases)+1 - CountRunners(new_bases);
  bases = new_bases;
}




void loop() {



  // Data gathering
   

   button_curr[0] = !digitalRead(green);
   button_curr[1] = !digitalRead(red);
   button_curr[2] = !digitalRead(blue);
   button_curr[3] = !digitalRead(yellow);
   button_curr[4] = !digitalRead(white);

   press_type = press_code(button_curr, button_prev);
  
   print_action(press_type);

   update_bases(bases,press_type,add_runs);
   num_runs+=add_runs;
   if (add_runs != 0) 
   {  Serial.println((String)"Number of Runs: " + num_runs);}
     
    //ground latchPin and hold low for as long as you are transmitting
    if (press_type !=0 && press_type !=5) {
       digitalWrite(latchPin, 0);
        shiftOut(dataPin, clockPin,   strike_out_shift_out(strikes,outs)); 
        shiftOut(dataPin, clockPin, bases + enable_home(0));
        digitalWrite(latchPin, 1);
        delay (1000);
    }
   
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin,   strike_out_shift_out(strikes,outs)); 
    shiftOut(dataPin, clockPin, bases + enable_home(1));
    digitalWrite(latchPin, 1);

    
    for (int i=0; i <5; i++) {button_prev[i]=button_curr[i];}
    

    
    delay(50);
 
}










void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

//internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

 //clear everything out just in case to
 //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}
