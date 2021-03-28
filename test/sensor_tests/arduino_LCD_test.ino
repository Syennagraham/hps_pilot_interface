/*
This example shows how to change the backlight brightness and colors of
LCD screen attached to an arduino UNO with I2C communication. 

This example also displays cycle count to check communication. 

Default: 9600bps.

To get this code to work, attach an LCD to an Arduino Uno using the following pins:
arduino(3.3V) - LCD(RAW)
arduino(GND)  - LCD(GND)
arduino(SDA)  - LCD(SDA)
arduino(SCL)  - LCD(SCL)

Command cheat sheet:
ASCII / DEC / HEX
'|' / 124 / 0x7C - Put into setting mode
/ 128-157 / 0x80-0x9D - Set the primary backlight brightness. 128 = Off, 157 = 100%.
/ 158-187 / 0x9E-0xBB - Set the green backlight brightness. 158 = Off, 187 = 100%.
/ 188-217 / 0xBC-0xD9 - Set the blue backlight brightness. 188 = Off, 217 = 100%.
For example, to change the baud rate to 115200 send 124 followed by 18.

Reference:
https://media.digikey.com/pdf/Data%20Sheets/Sparkfun%20PDFs/AVR_Based_Serial_Enabled_LCDs_HookupGuide_Web.pdf

*/

#include <Wire.h>
#define DISPLAY_ADDRESS1 0x72 //This is the default address of the OpenLCD
int cycles = 0;

byte counter = 0;

void setup()
{
    // Start communication with the LCD
    Wire.begin();
    //Wire.setClock(400000); //Optional - set I2C SCL to High Speed Mode of 400kHz

    // Set up for the debugging serial monitor
    Serial.begin(9600); //Start serial communication at 9600 for debug statements
    Serial.println("RPM DATA TO LCD CODE");

    // Set up for the LCD readings
    //Send the reset command to the display - this forces the cursor to return to the beginning of the display
    Wire.beginTransmission(DISPLAY_ADDRESS1);
    Wire.write('|');  //Put LCD into setting mode
    Wire.write('-');  //Send clear display command
    Wire.write(9);    // Enable/disable splash screen
    Wire.write('|');  //Put LCD into setting mode 
    allOFF();         // Turn all backlight colors off
    whiteON();        // Turn backlight to white
    Wire.endTransmission();
}

void loop()
{
   cycles++; //Counting cycles! Yay!
 // Serial.print("Cycle: "); //These serial.print statements take multiple miliseconds
 // Serial.println(cycles);
 i2cSendValue(cycles); //Send the four characters to the display
 delay(50); 
}

//Given a number, i2cSendValue chops up an integer into four values and sends them out over I2C
void i2cSendValue(int value)
{
 Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
 Wire.write('|'); //Put LCD into setting mode
 Wire.write('-'); //Send clear display command
 Wire.print("Cycles: ");
 Wire.print(value);
 Wire.endTransmission(); //Stop I2C transmission
}
  
void whiteON()   // Turn the backlight color to white
{
  Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
  Wire.write('|'); //Put LCD into setting mode
  //Wire.write('/');  // Disable system messages 
  Wire.write(187); //Set green backlight amount to 0% 
  Wire.write('|'); //Put LCD into setting mode 
  Wire.write(217); //Set blue backlight amount to 0% 
  Wire.write('|'); //Put LCD into setting mode 
  Wire.write(157); //Set white/red backlight amount to 100% 
  delay(3000);
  Wire.endTransmission(); //Stop I2C transmission
}

void redON()  // Turn the backlight color to red
{
  Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
  Wire.write('|'); //Put LCD into setting mode  
  Wire.write(158); //Set green backlight amount to 0% 
  Wire.write('|'); //Put LCD into setting mode 
  Wire.write(188); //Set blue backlight amount to 0% 
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(157); //Set white/red backlight amount to 100% 
  delay(3000);
  Wire.endTransmission(); //Stop I2C transmission
}

void blueON()  // Turn the backlight color to blue
{
  Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(158); //Set green backlight amount to 0% 
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(128); //Set red backlight amount to 0%  
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(217); //Set blue backlight amount to 100%
  delay(3000);
  Wire.endTransmission(); //Stop I2C transmission
}

void greenON()  // Turn the backlight color to green
{
  Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(188); //Set blue backlight amount to 0% 
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(128); //Set red backlight amount to 0%  
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(187); //Set green backlight amount to 100%
  delay(3000);
  Wire.endTransmission(); //Stop I2C transmission
}

void allOFF(void) //  Turn all backlight colors off
{
  Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
  // Set all colors to 0
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(128); //Set white/red backlight amount to 0%
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(158 + 0); //Set green backlight amount to 0% 
  Wire.write('|'); //Put LCD into setting mode
  Wire.write(188 + 0); //Set blue backlight amount to 0%
  Wire.write('|'); //Put LCD into setting mode
  Wire.write('-'); 
  delay(500);
  Wire.endTransmission(); //Stop I2C transmission
}
