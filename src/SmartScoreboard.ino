
#include "hex_display.h"
#include "input_SR.h"
#include "output_SR.h"
#include "Baseball.h"
#include "ping_pong.h"
#include "clock_module.h"
#include "game.h"



//buzzer buzzer_inst(9);

input_SR buttons_inst(8, 6, 5);
hex_display hex_inst(4, 3, 2);
output_SR LEDs_inst(15, 16, 17);

Baseball baseball_inst(&buttons_inst, &hex_inst, &LEDs_inst);
ping_pong pingpong_inst(&buttons_inst, &hex_inst, &LEDs_inst);
clk_module clk_module_inst(&buttons_inst, &hex_inst, &LEDs_inst);

void setup() {
  //Start Serial for debuging purposes
  Serial.begin(9600);

 
 //pingpong_inst.initGame();
 //clk_module_inst.initGame();
 
}



void loop() {
  baseball_inst.initGame();
 while (baseball_inst.updateGame());
 pingpong_inst.initGame();
 while(pingpong_inst.updateGame());
 
 //analogWrite(6, 255);
//analogWrite(5, 255);

 //pingpong_inst.initGame();
//while(pingpong_inst.updateGame()){}
 //clk_module_inst.initGame();
//while(clk_module_inst.updateGame()){}



//clk_module_inst.updateGame();

  delay(50);

}
