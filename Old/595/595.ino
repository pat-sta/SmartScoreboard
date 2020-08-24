//final
//**************************************************************//
//  Name    : shiftOutCode, Dual Binary Counters                 //
//  Author  : Carlyn Maw, Tom Igoe                               //
//  Date    : 25 Oct, 2006                                       //
//  Version : 1.0                                                //
//  Notes   : Code for using a 74HC595 Shift Register            //
//          : to count from 0 to 255                             //
//**************************************************************//

//Pin connected to ST_CP of 74HC595
int latchPin = 15; //yellow
//Pin connected to SH_CP of 74HC595
int clockPin = 16; //green
////Pin connected to DS of 74HC595
int dataPin = 17; //blue


void setup() {
  //Start Serial for debuging purposes  
  Serial.begin(9600);
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);

}



byte round_shift_out( int t1_round, int t2_round)
{
        if (t1_round ==0 && t2_round ==0) return 0b000000;
   else if (t1_round ==0 && t2_round ==1) return 0b000001;
   else if (t1_round ==0 && t2_round ==2) return 0b000011;
   else if (t1_round ==0 && t2_round ==3) return 0b000111;
  
  else if (t1_round ==1 && t2_round ==0) return 0b100000;
  else if (t1_round ==1 && t2_round ==1) return 0b100100;
  else if (t1_round ==1 && t2_round ==2) return 0b100110;
  else if (t1_round ==1 && t2_round ==3) return 0b100111;
  

  else if (t1_round ==2 && t2_round ==0) return 0b110000;
  else if (t1_round ==2 && t2_round ==1) return 0b110100;
  else if (t1_round ==2 && t2_round ==2) return 0b110110;
  else if (t1_round ==2 && t2_round ==3) return 0b110111;

   else if (t1_round ==3 && t2_round ==0) return 0b111000;
  else if (t1_round ==3 && t2_round ==1) return 0b111100;
  else if (t1_round ==3 && t2_round ==2) return 0b111110;
  else return 0b111111;
}



byte round_SR;
byte base_SR;
void loop() {
  //count up routine
   
  
    Serial.println("-");
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    
    //round LEDs
    shiftOut(dataPin, clockPin,  0b111000); 
    //base LEDs
    shiftOut(dataPin, clockPin, 0b0100);
    digitalWrite(latchPin, 1);

    Serial.println();
    delay(1000);
     digitalWrite(latchPin, 0);
    //round LEDs
    shiftOut(dataPin, clockPin,  0b010101); 
    //base LEDs
    shiftOut(dataPin, clockPin, 0b1010);
    
    
    digitalWrite(latchPin, 1);

    Serial.println();
    delay(1000);

    
 
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
