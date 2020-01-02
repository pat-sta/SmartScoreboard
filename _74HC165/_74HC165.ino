
#include <SPI.h>
 //MOSI: pin 11 don't use for anything
 //MISO: pin 12 to Q7 of last register
 //SCK:  pin 13 to CP
 // PL:  pin 8
 byte shift_1, shift_2;
 int team1_buttons[5];
 int PL = 8;

 
void setup(){
  Serial.begin(9600);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.begin();
 
  pinMode(PL, OUTPUT);
  digitalWrite(PL, HIGH);
}


void loop(){
  digitalWrite(PL, LOW);
  delay(1);
  digitalWrite(PL,HIGH);
  shift_2 = SPI.transfer(0x00);
  shift_1 = SPI.transfer(0x00);

  for (int i = 0; i <5 ; i++){
  team1_buttons[i] = !bitRead(shift_1,7-i);
  }
  
 for(int i = 0; i < 5; i++)
{
  Serial.print(team1_buttons[i]);
}
Serial.println();
  
//  Serial.print("Register 1 = ");
//  Serial.println(shift_1,BIN);
//  Serial.print("Register 2 = ");
//  Serial.println(shift_2,BIN);  
  delay(10);
}
