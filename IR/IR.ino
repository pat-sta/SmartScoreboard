#include "IRLibAll.h"
int pin =2;
//Create a receiver object to listen on pin 2
IRrecvPCI myReceiver(pin);


//Create a decoder object 
IRdecode myDecoder;   

void setup() {
  Serial.begin(9600);
  delay(2000); while (!Serial); //delay for Leonardo
  myReceiver.enableIRIn(); // Start the receiver
//  myReceiver2.enableIRIn(); // Start the receiver
  Serial.println(("Ready to receive IR signals"));
}
int continue_=0;
void loop() {
 continue_ =0;
  //Continue looping until you get a complete signal received
  if (myReceiver.getResults()) {
    Serial.println(pin);
    myDecoder.decode();           //Decode it
   Serial.println(myDecoder.value); 
   // myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver
   // Serial.println(myDecoder.value);
    switch(myDecoder.value){
      case 0:
        continue_=1;
        break;
      case 16580863:
        Serial.println("Single");
        break;
      case 16613503:
        Serial.println("Double");
        break;
       case 16597183:
        Serial.println("Triple");
        break;
      case 16589023:
        Serial.println("Homerun");
        break;
       case 16621663:
        Serial.println("Strike");
        break;     
    }}
    if(continue_){ pin = (pin==2)? 4:2;
    if (myReceiver.getResults()) {
    //Serial.println("1ST");
    myDecoder.decode();           //Decode it
   // Serial.println(myDecoder.value); 
   // myDecoder.dumpResults(true);  //Now print results. Use false for less detail
    myReceiver.enableIRIn();      //Restart receiver
   // Serial.println(myDecoder.value);
    switch(myDecoder.value){
      case 16580863:
        Serial.println("Single");
        break;
      case 16613503:
        Serial.println("Double");
        break;
       case 16597183:
        Serial.println("Triple");
        break;
      case 16589023:
        Serial.println("Homerun");
        break;
       case 16621663:
        Serial.println("Strike");
        break;     
    }}
      
    }

//  }
}

//16580863  16613503  16597183
//16589023  16621663  16605343
//16584943  16617583  16601263
//16593103  16625743  16609423
//16582903  16615543  16599223
//16591063  16623703  16607383
//16586983  16619623  16603303
