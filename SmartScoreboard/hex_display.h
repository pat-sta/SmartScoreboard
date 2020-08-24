
class hex_display
{ public:
    int segmentLatch;
    int segmentClock;
    int segmentData;
    byte postNumberData[4];


    hex_display( int _segmentLatch, int _segmentClock, int _segmentData):
      segmentLatch(_segmentLatch), segmentClock(_segmentClock), segmentData(_segmentData){
      pinMode(segmentLatch, OUTPUT);
      pinMode(segmentClock, OUTPUT);
      pinMode(segmentData, OUTPUT);
    }

    //Given a number, or '-', shifts it out to the display

    byte dataToSegments(byte number){
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
        case 'r': segments = 0b00001100; break;
        case 's': segments = 0b00110111; break;
        case 't': segments = 0b00011110; break;
        case 'u': segments = 0b01111010; break;
        case 'v': segments = 0b00111000; break;
        case 'w': segments = 0b00111001; break;
        case 'x': segments = 0b01101110; break;
        case 'y': segments = 0b01110110; break;
        case 'z': segments = 0b01011101; break;
      }
      return segments;
    }
    
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
        case 'r': segments = 0b00001100; break;
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
      //segments = segments + 0b10000000;
      //Clock these bits out to the drivers
      for (byte x = 0 ; x < 8 ; x++)
      {
        digitalWrite(segmentClock, LOW);
        digitalWrite(segmentData, segments & 1 << (7 - x));
        digitalWrite(segmentClock, HIGH); //Data transfers to the register on the rising edge of SRCK
      }
    }

  //setWord
  //setNumber(1,2)

  void setWord(byte char0, byte char1, byte char2, byte char3){
      postNumberData[0]= dataToSegments(char0);
      postNumberData[1]= dataToSegments(char1);
      postNumberData[2]= dataToSegments(char2);
      postNumberData[3]= dataToSegments(char3);
  }
//void showNumber(float value) {
//      int remainder;
//      if (value <0) {value =0;}
//      if (value >99) {value =99;}
//      int number = abs(value);
//      digitalWrite(segmentLatch, LOW);
//      for (byte x = 0 ; x < 4 ; x++) {
//        remainder = number % 10;
//        postNumber(remainder);
//        number /= 10;
//      }
//      digitalWrite(segmentLatch, HIGH);
//    }
    
  void addDecimal(int pos){
    if (!bitRead(postNumberData[pos],7)){ postNumberData[pos]+= 0b10000000;}   
  }

void updateDisplay(){
    digitalWrite(segmentLatch, LOW);
     byte segments;
     for(int i=0; i <4; i++){
      segments = postNumberData[3-i];
      Serial.println(segments);
      delay(100);
      for (byte x = 0 ; x < 8 ; x++){
        digitalWrite(segmentClock, LOW);
        digitalWrite(segmentData, segments & 1 << (7 - x));
        digitalWrite(segmentClock, HIGH); //Data transfers to the register on the rising edge of SRCK
      }
    }
    digitalWrite(segmentLatch, HIGH);
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
      if (value <0) {value =0;}
      if (value >99) {value =99;}
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
        if (x == 0)
        {
          postNumber(remainder, 1);
        }
        else postNumber(remainder);

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
