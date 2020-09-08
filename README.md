# SmartScoreboard
Wall-mounted programmable scoreboard featuring a real-time-clock and games such as Ping-Pong, Baseball, Die Toss.
## The Team
**Patrick Stach** | stach2@illinois.edu    
Circuit design and wiring, programming scoreboard.

**Thomas Schneider** | thomass8@illinois.edu    
Scoreboard enclosure design and build, CAD design of modular housings/ enclosures.

## Portfolio
See the scoreboard in action and learn about specific parts of the build through video and pictures.  
https://illinois.digication.com/smart-scoreboard/home

[![Scoreboard in Action](https://i.gyazo.com/8c9aa34129a5f807bd8be7a402f35e7d.png)](https://illinois.digication.com/smart-scoreboard/scoreboard-in-action)

## Parts Used
| Part                            | Purpose                                                                             | Vendor Link                                                                                      |
|---------------------------------|-------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------|
| Arduino Nano Board ATmega328P   | Programmed for game logic and reading/controlling outputs/inputs                    | [Amazon](https://www.amazon.com/Arduino-A000005-ARDUINO-Nano/dp/B0097AU5OU/)                     |
| SparkFun 6.5" 7-Segment Display | Display numbers such as score, time, etc.                                           | [SparkFun](https://www.sparkfun.com/products/11441)                                              |
| SparkFun Large Digit Driver     | Controller to drive 7-Segment displays and store segment data in shift register     | [SparkFun](https://www.sparkfun.com/products/13279)                                              |
| SN74HC595 Shift Register        | Controls panel LEDs                                                                 | [SparkFun](https://www.sparkfun.com/products/13699)                                              |
| SN74HC165 Shift Register        | Used to take "snapshot" of button states                                            | [Amazon](https://www.amazon.com/SN74HC165N-74HC165-8-Bit-Parallel-Load-Registers/dp/B00UVUXIV2)  |
| 12V DC Switching Power Supply   | 120V AC                                                                             | [Amazon](https://www.amazon.com/Chanzon-Switching-Adapter-100-240V-Transformer/dp/B07HNL5D56/)   |
| LM2596 DC to DC Buck Converter  | 12V DC -> 5V DC for 5V components/logic, 12V DC -> 11V DC to dim 7-segment displays | [Amazon](https://www.amazon.com/LM2596s-Converter-Step-down-Regulator-Stabilizer/dp/B07CVBG8CT/) |
| DS3231 RTC Module               | Stores time/date information even when scoreboard is off                            | [Amazon](https://www.amazon.com/gp/product/B01IXYM3PY/)                                          |
| 12V LED Panel Lights            | Lights to indicate game data such as round, outs, bases, etc.                       | [Amazon](https://www.amazon.com/gp/product/B07DH943VR/)                                          |
| 5V Relay Board                  | Control 12V LED Panel lights from Arduino                                           | [Amazon](https://www.amazon.com/gp/product/B07QGT6RGX/)                                          |
| Arcade Push Buttons             | 5 Buttons for each team to control scoreboard                                       | [Amazon](https://www.amazon.com/gp/product/B01M0XPWGG/)                                          |


