
//**************************************************************//
//  Name    : shiftOutCode, Dual Binary Counters                 //
//  Author  : Carlyn Maw, Tom Igoe                               //
//  Date    : 25 Oct, 2006                                       //
//  Version : 1.0                                                //
//  Notes   : Code for using a 74HC595 Shift Register            //
//          : to count from 0 to 255                             //
//**************************************************************//

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;



void setup() {
  //Start Serial for debuging purposes  
  Serial.begin(9600);
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);

}
int round_arr [6] = {1,0,1,1,0,1};
//

int base_arr [4] = {0,0,0,1};


byte round_arr_to_SR(int round_arr [6]) {
  byte temp =0;
  for (int i = 1; i<7; i++){ 
    if (round_arr[i-1] ==1) {
     temp = (temp + pow(2,i))+1;
      Serial.print(i);
      Serial.print(" ");
      Serial.print(pow(2,i));
      Serial.print(" ");
      Serial.println(temp);
    }
   }
  return temp;
}

byte base_arr_to_SR(int base_arr [4]) {
 byte temp =0;
  for (int i = 1; i<5; i++){ 
  if (base_arr[i-1] ==1){
      temp = (temp + pow(2,i))+1;
      Serial.print(i);
      Serial.print(" ");
      Serial.print(pow(2,i));
      Serial.print(" ");
      Serial.println(temp);
  }
   }
   
  return temp;
}


byte round_SR;
byte base_SR;
void loop() {
  //count up routine
    round_SR= round_arr_to_SR(round_arr);
    base_SR= base_arr_to_SR(base_arr);
  
    Serial.println("-");
    //ground latchPin and hold low for as long as you are transmitting
    digitalWrite(latchPin, 0);
    //count up on GREEN/ ORANGE LEDs
    shiftOut(dataPin, clockPin,  round_SR); 
    //count down on BLUE LEDs
    shiftOut(dataPin, clockPin, base_SR);
    //return the latch pin high to signal chip that it 
    //no longer needs to listen for information
    digitalWrite(latchPin, 1);
//    Serial.println(round_SR);
//    Serial.println(round_SR,BIN);
     //Serial.println(base_SR);
    //Serial.println(base_SR,BIN);
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
