//final
//MSB is

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
byte segmentLatch = 4;
byte segmentClock = 3;
byte segmentData = 2;


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//Button Value declarations



void setup()
{
  Serial.begin(9600);
  Serial.println("Large Digit Driver Example");

  pinMode(segmentClock, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(segmentLatch, OUTPUT);



  digitalWrite(segmentClock, LOW);
  digitalWrite(segmentData, LOW);
  digitalWrite(segmentLatch, LOW);

  delay(50);
  digitalWrite(segmentLatch, LOW);
  postNumber('z');
  postNumber('x');
  postNumber('w');
  postNumber('v');
  digitalWrite(segmentLatch, HIGH);






}

void loop()
{

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



void showNumber(float value) {
  int remainder;
  int number = abs(value);
  for (byte x = 0 ; x < 4 ; x++) {
    remainder = number % 10;
    postNumber(remainder);
    number /= 10;
  }
}

void showNumber(float value1, float value2) {
  int remainder;
  int number = abs(value2);
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
}


void showNumber(float value1, float value2, float value3, float value4) {
  int remainder;
  postNumber(abs(value4));
  postNumber(abs(value3));
  postNumber(abs(value2));
  postNumber(abs(value1));

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
  for (int ctr = 0; ctr < num_times; ctr++) {
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 4; j++) {
        postNumber(i, false);
      }
      LatchData(segmentLatch);
      delay(time_amt);
    }
  }
}
