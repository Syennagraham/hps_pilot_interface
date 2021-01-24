/* 
 *  This example reads a pressure sensor out to an LCD screen using Arduino UNO
 *  
 *  Pins from pressure sensor to Arduino
 *  PS Black to GND
 *  PS Red to 5V
 *  PS Yellow to arduino A1
 *  
 */

#include <SoftwareSerial.h>
SoftwareSerial OpenLCD(6, 7); //RX (not used), TX
byte counter = 0;

void setup()
{
  
Serial.begin(9600); //Begin local communication for debug statements
OpenLCD.begin(9600); //Begin communication with OpenLCD

Serial.println("Mono/Red backlight set to 100%");
OpenLCD.write('|'); //Put LCD into setting mode
OpenLCD.write(128 + 29); //Set white/red backlight amount to 100%

}

void loop()
{

//Send the clear command to the display - this returns the cursor to the beginning of the display
OpenLCD.write('|'); //Setting character
OpenLCD.write('-'); //Clear display  

int sensorVal=analogRead(A1);
    Serial.print("Sensor Value: ");
    Serial.print(sensorVal);

float voltage = (sensorVal*5.0)/1024.0;
    Serial.print("Volts: ");
    Serial.print(voltage);
   
float pressure_pascal = (3.0*((float)voltage-0.47))*1000000.0;
  
float pressure_bar = pressure_pascal/10e5;
    Serial.print("Pressure = ");
    Serial.print(pressure_bar);
    Serial.println(" bars");
    
    OpenLCD.print("Pressure: ");
    OpenLCD.print(pressure_bar);    
    
    delay(3000);
}
