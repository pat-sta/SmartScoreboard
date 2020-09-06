#ifndef OUTPUT_SR_H
#define OUTPUT_SR_H

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
    //data1 = TOP
    //data2 = BASES
    void updateLEDs(byte data1, byte data2)
    {
      digitalWrite(latchPin, 0);
      shiftOut(data1);
      shiftOut(data2);
      digitalWrite(latchPin, 1);

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

#endif
