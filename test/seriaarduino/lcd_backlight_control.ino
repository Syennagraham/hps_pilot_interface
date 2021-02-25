/*
This example shows how to change the backlight brightness and colors of
LCD screen attached to an arduino UNO with serial communication. 

Default: 9600bps.

To get this code to work, attach an OpenLCD to an Arduino Uno using the following pins:
RX (OpenLCD) to Pin 7 (Arduino)
VIN to 5V
GND to GND

If using a logic converter:
Arduino pin 7 to LC (logic converter) HV1
Arduino pin 3.3V to LC LV
Arduino pin 5V to LC HV
Arduino pin GND to breadboard GND
Arduino pin VIN to LCD RAW
Breadboard GND to LCD GND
Breadboard GND to LC GND
LC LV1 to LCD RX
For picture:  https://cdn.sparkfun.com/assets/learn_tutorials/7/8/9/LCD_Serial_basic_bb.png 

Command cheat sheet:
ASCII / DEC / HEX
'|' / 124 / 0x7C - Put into setting mode

/ 128-157 / 0x80-0x9D - Set the primary backlight brightness. 128 = Off, 157 = 100%.
/ 158-187 / 0x9E-0xBB - Set the green backlight brightness. 158 = Off, 187 = 100%.
/ 188-217 / 0xBC-0xD9 - Set the blue backlight brightness. 188 = Off, 217 = 100%.
For example, to change the baud rate to 115200 send 124 followed by 18.
*/

#include <SoftwareSerial.h>
SoftwareSerial OpenLCD(6, 7); //RX (not used), TX
byte counter = 0;

void setup()
{
  
Serial.begin(9600); //Begin local communication for debug statements
OpenLCD.begin(9600); //Begin communication with OpenLCD
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(158 + 0); //Set green backlight amount to 0%
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(188 + 0); //Set blue backlight amount to 0%

}

void loop()
{
  
//Control red backlight 
Serial.println("Mono/Red backlight set to 0%");
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(128); //Set white/red backlight amount to 0%
delay(3000);
//Control red backlight
Serial.println("Mono/Red backlight set to 51%");
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(128 + 15); //Set white/red backlight amount to 51%
delay(3000);
//Control red backlight
Serial.println("Mono/Red backlight set to 100%");
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(128 + 29); //Set white/red backlight amount to 100%
delay(3000);
all_off(); // turn off all backlights - see function below



//Control green backlight to 51%
Serial.println("Green backlight set to 51%");
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(158 + 15); //Set green backlight amount to 51%
delay(3000);
//Control green backlight to 100%
Serial.println("Green backlight set to 100%");
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(158 + 29); //Set green backlight amount to 100%
delay(3000);
all_off(); // turn off all backlights - see function below



//Control blue backlight to 51%
Serial.println("Blue backlight set to 51%");
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(188 + 15); //Set blue backlight amount to 51%
delay(3000);
//Control blue backlight to 100%
Serial.println("Blue backlight set to 100%");
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(188 + 29); //Set blue backlight amount to 100%
delay(3000);
all_off(); // turn off all backlights - see function below
}



void all_off(void)
{
  
// Set all colors to 0
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(128); //Set white/red backlight amount to 0%
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(158 + 0); //Set green backlight amount to 0%

OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(188 + 0); //Set blue backlight amount to 0%
delay(3000);

}
