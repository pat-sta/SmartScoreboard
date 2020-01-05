
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
  

}



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
int strikes = 1;
int outs = 0;

int green_curr=0;
int red_curr=0;
int blue_curr=0;
int yellow_curr=0;
int white_curr=0;

int green_prev=0;
int red_prev=0;
int blue_prev=0;
int yellow_prev=0;
int white_prev=0;

byte bases = 0b1000;

void loop() {



  // Data gathering
   

   green_curr = digitalRead(green);
   red_curr = digitalRead(red);
   blue_curr = digitalRead(blue);
   yellow_curr = digitalRead(yellow);
   white_curr = digitalRead(white);

   
  
    Serial.println("-");
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    
    //Strikes/ Outs LEDs
    shiftOut(dataPin, clockPin,   strike_out_shift_out(strikes,outs)); 
    //base LEDs
    shiftOut(dataPin, clockPin, bases);
    
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 2);
//    Serial.println(round_SR);
//    Serial.println(round_SR,BIN);
     //Serial.println(base_SR);
    //Serial.println(base_SR,BIN);
    Serial.println();
    
    green_prev= green_curr;
    red_prev= red_curr;
    blue_prev= blue_curr;
    yellow_prev= yellow_curr;
    white_prev= white_curr;
    

    
    delay(2000);
 
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
