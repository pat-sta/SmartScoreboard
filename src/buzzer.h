
class buzzer{ 

  bool active = false;
	

public:
	int outPin;



	 buzzer( int _outPin): outPin(_outPin)
    {
    	pinMode(outPin, OUTPUT);
      noTone(outPin);
    }

  toneOn()
  {
    
  
     digitalWrite(outPin, HIGH);
    delay(2);
     digitalWrite(outPin, LOW);
     active = true;
     
  }
   toneOff()
  {
   
      digitalWrite(outPin, LOW);
   
  }
  


};
