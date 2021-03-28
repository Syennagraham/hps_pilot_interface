/* 
 *  This example reads a pressure sensor out to a terminal and an LCD screen (if desired) using Arduino Uno
 *  
 *  Pins from pressure sensor to Arduino
 *  PS Black to Arduino GND
 *  PS Red to Arduino 5V
 *  PS Yellow to Arduino A1
 *  
 */

#include <Wire.h>

#define DISPLAY_ADDRESS1 0x72 //This is the default address of the OpenLCD

int pressure; 

void setup() {
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

void loop() {
  whiteON();

  float dep = depth();
  
  float top = 0.75;
  float bottom = 0.40;

  if( bottom < dep > top ) 
  {
    greenON();
  }
  else
  {
    redON();
  }
}


int depth()  // Get the pressure from the pressure sensor
{
  //Send the clear command to the display - this returns the cursor to the beginning of the display
    Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
    Wire.write('|'); //Setting character
    Wire.write('-'); //Clear display  
  
  int sensorVal=analogRead(A1);
      Serial.print("Sensor Value: ");
      Serial.println(sensorVal);
  
  float voltage = (sensorVal*5.0)/1024.0;
      Serial.print("Volts: ");
      Serial.println(voltage);
     
  float pressure_pascal = (3.0*((float)voltage-0.47))*1000000.0;
    
  float pressure_bar = pressure_pascal/10e5;
      Serial.print("Pressure = ");
      Serial.print(pressure_bar);
      Serial.println(" bars");
      
      Wire.print("Pressure: ");
      Wire.println(pressure_bar);    
      
      delay(3000);
      //return pressure_bar;
  
  float gravity = 9.8;
  float density = 997;    
  
  float depth_meters = pressure_bar/( gravity * density);
      Serial.print("Depth = ");
      Serial.print(depth_meters, 6);
      Serial.println(" meters");
      
      Wire.print("Depth: ");
      Wire.println(depth_meters, 6);    
      
      delay(3000);
      return depth_meters;
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
