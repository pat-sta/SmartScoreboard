   //final
    
    /*
 Controlling large 7-segment displays
 By: Nathan Seidle
 SparkFun Electronics
 Date: February 25th, 2015
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 This code demonstrates how to post two numbers to a 2-digit display usings two large digit driver boards.

 Here's how to hook up the Arduino pins to the Large Digit Driver IN

 Arduino pin 6 -> CLK (Green on the 6-pin cable)
 5 -> LAT (Blue)
 7 -> SER on the IN side (Yellow)
 5V -> 5V (Orange)
 Power Arduino with 12V and connect to Vin -> 12V (Red)
 GND -> GND (Black)

 There are two connectors on the Large Digit Driver. 'IN' is the input side that should be connected to
 your microcontroller (the Arduino). 'OUT' is the output side that should be connected to the 'IN' of addtional
 digits.

 Each display will use about 150mA with all segments and decimal point on.

*/
void postNumber(byte number, boolean decimal);
void LatchData(byte segmentLatch);
void showBlank(int time_amt);
void loopNumpers(int time_amt, int num_times);

//GPIO declarations
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
byte segmentClock = 3;
byte segmentLatch = 4;
byte segmentData = 2;

//byte white_button= 2;
//byte blue_button= 3;
//byte red_button= 4;
//byte yellow_button= 5;
//byte green_button= 6;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Button Value declarations
int last_green_state = 1;
int last_red_state = 1;
int last_yellow_state = 1;
int last_blue_state = 1;
int last_white_state = 1;

int PWM_hex =3;
 

void setup()
{
  Serial.begin(9600);
  Serial.println("Large Digit Driver Example");

  pinMode(segmentClock, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(segmentLatch, OUTPUT);
  pinMode(PWM_hex, OUTPUT);

//  pinMode(green_button, INPUT_PULLUP);
//  pinMode(red_button, INPUT_PULLUP);
//  pinMode(yellow_button, INPUT_PULLUP);
//   pinMode(blue_button, INPUT_PULLUP);
//  pinMode(white_button, INPUT_PULLUP);
// 
 
  digitalWrite(segmentClock, LOW);
  digitalWrite(segmentData, LOW);
  digitalWrite(segmentLatch, LOW);

   delay(50);
   showBlank(400);

    loopNumpers(300, 1);
    
  for (int i=0; i<3; i++)
  {
    // SAY PING
    postNumber('g', false);
    postNumber('n', false);
    
     postNumber('I', false);
    postNumber('P', false);
   
    
  
   LatchData(segmentLatch);
    
    
    delay(1000);
    
    // SAY PONG
     postNumber('g', false);
     postNumber('n', false);
   
     postNumber('O', false);
    postNumber('P', false);
   
   
  
    LatchData(segmentLatch);
  
    delay(1000);
    
}
 
  
  

}
//Buttons are active low

//digitalRead() = 1 => switch not pressed
//digitalRead() = 0 => switch pressed

int number_A = 0;
int number_B = 0;

void loop()
{
  digitalWrite(PWM_hex,255);
//
//  showNumber(number_A); 
//  showNumber(number_B); 
//   //Latch the current segment data
//  digitalWrite(segmentLatch, LOW);
//  digitalWrite(segmentLatch, HIGH); //Register moves storage register on the rising edge of RCK
//  
//  if(new_press(&last_green_state, green_button))
//  {
//    if (number_A <99) {number_A ++;}
//  }
//  if(new_press(&last_red_state, red_button))
//  {
//    if (number_A>-9) {number_A --;}
//  }
//   if(new_press(&last_blue_state, blue_button))
//  {
//    number_A = 0;
//    number_B = 0;
//  }
//
//   if(new_press(&last_white_state, white_button))
//  {
//    if (number_B <99) {number_B ++;}
//  }
//  if(new_press(&last_yellow_state, yellow_button))
//  {
//    if (number_B>-9) {number_B --;}
//  }
//  delay(50);
//}
//
//int new_press(int * last_pressed, int pin)
//{
//  // pressed = 0 => switch was not pressed
//  int pressed = !(digitalRead(pin));
//  if (pressed)
//  {
//    if(*last_pressed)
//    {
//      return 0;
//    }
//    else
//    {
//      *last_pressed = 1;
//      return 1;
//    }
//  }
//  else
//  {
//    *last_pressed = 0;
//    return 0;
//  }
}


//Given a number, or '-', shifts it out to the display
void postNumber(byte number, boolean decimal)
{
  //    -  A
  //   / / F/B
  //    -  G
  //   / / E/C
  //    -. D/DP

#define a  1<<0
#define b  1<<6
#define c  1<<5
#define d  1<<4
#define e  1<<3
#define f  1<<1
#define g  1<<2
#define dp 1<<7

  byte segments;

  switch (number)
  {
    case 1: segments = b | c; break;
    case 2: segments = a | b | d | e | g; break;
    case 3: segments = a | b | c | d | g; break;
    case 4: segments = f | g | b | c; break;
    case 5: segments = a | f | g | c | d; break;
    case 6: segments = a | f | g | e | c | d; break;
    case 7: segments = a | b | c; break;
    case 8: segments = a | b | c | d | e | f | g; break;
    case 9: segments = a | b | c | d | f | g; break;
    case 0: segments = a | b | c | d | e | f; break;
    case ' ': segments = 0; break;
    case 'c': segments = g | e | d; break;
    case '-': segments = g; break;
    case 'P': segments = e | f | a | b | g; break;
    case 'I': segments = b | c; break;
    case 'n': segments = e | a | c | f | b; break;
    case 'g': segments = a | f | g | b | c | d; break;
    case 'O': segments = a | b | c | d | e | f; break;
  }

  if (decimal) segments |= dp;

  //Clock these bits out to the drivers
  for (byte x = 0 ; x < 8 ; x++)
  {
    digitalWrite(segmentClock, LOW);
    digitalWrite(segmentData, segments & 1 << (7 - x));
    digitalWrite(segmentClock, HIGH); //Data transfers to the register on the rising edge of SRCK
    
  }
}
//Takes a number (-9,99) and displays on two 7-Segment Displays. Has boundary bhecks
void showNumber(float value)
{
  int negative = (value <0)? 1: 0;
  int number = abs(value); //Remove negative signs and any decimals

  //Serial.print("number: ");
  //Serial.println(number);
  if (negative) {
     if (number > 9) {number = 9;}
     postNumber(number, false);
     postNumber('-', false);
  }
  else {
     for (byte x = 0 ; x < 2 ; x++)
    {
      int remainder = number % 10;
      postNumber(remainder, false);
      number /= 10;
    }
  }
}

void LatchData(byte segmentLatch)
{
  digitalWrite(segmentLatch, LOW);
  digitalWrite(segmentLatch, HIGH);
}


void showBlank(int time_amt)
{
   postNumber(' ', false);
   postNumber(' ', false);
   postNumber(' ', false);
   postNumber(' ', false);
   LatchData(segmentLatch);
   delay(time_amt);
}


void loopNumpers(int time_amt, int num_times)
{
  for (int ctr =0; ctr < num_times; ctr++){
    for (int i=0; i< 10; i++){
      for(int j=0; j <4; j++){
        postNumber(i, false);
      }
      LatchData(segmentLatch);
      delay(time_amt);
     }
  }
}
