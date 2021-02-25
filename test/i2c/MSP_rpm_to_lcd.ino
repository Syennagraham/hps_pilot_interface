/*
 * This code displays RPM data to the LCD using I2C
 *  * Proximity sensor A 
 *    Blue  - GND
 *    Black - P2.6
 *    Brown - 5V
 * Proximity sensor B
 *    Blue  - GND
 *    Black - P2.4
 *    Brown - 5V  
 * LCD
 *    RAW - 3.3V
 *    GND - GND
 *    SDA - P6.4
 *    SCL - P6.5
 *    
 * By: Syenna Graham   
 */

#include <Wire.h>

#define DISPLAY_ADDRESS1 0x72 //This is the default address of the OpenLCD

// Constants for the RPM sensors
const int dataINA = 39; //Proximity sensor input A (PSA)
const int dataINB = 38; //Proximity sensor input B (PSB) 

unsigned long prevmillis; // To store time
unsigned long duration; // To store time difference
unsigned long refresh; // To store time for refresh of reading

int rpmA; // RPM from sensor A value
int rpmB; // RPM from sensor B value
int avg_rpm; // (RPMA-RPMB)/ 2

boolean currentstateA; // Current state of PSA input scan
boolean prevstateA; // State of PSA sensor in previous scan

boolean currentstateB; // Current state of PSB input scan
boolean prevstateB; // State of PSB sensor in previous scan

void setup(){

    // Start communication with the LCD
    Wire.begin();
    //Wire.setClock(400000); //Optional - set I2C SCL to High Speed Mode of 400kHz

    // Set up for the debugging serial monitor
    Serial.begin(9600); //Start serial communication at 9600 for debug statements
    Serial.println("RPM DATA TO LCD CODE");

    // Set up for the LCD readings
    //Send the reset command to the display - this forces the cursor to return to the beginning of the display
    Wire.beginTransmission(DISPLAY_ADDRESS1);
    Wire.write('|'); //Put LCD into setting mode
    Wire.write('-'); //Send clear display command
    Wire.endTransmission();

    // Set up for the RPM sensor readings
    pinMode(dataINA,INPUT);
    pinMode(dataINB,INPUT);        
    prevmillis = 0;
    prevstateA = LOW;  
    prevstateB = LOW;  
}

void loop()
{
    rpm_value();
    delay(50); //The maximum update rate of OpenLCD is about 100Hz (10ms). A smaller delay will cause flicker
}

void rpm_value()
{  
   // Start talking to the LCD via I2C
   Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device #1
   Wire.write('|'); //Put LCD into setting mode
   Wire.write('-'); //Send clear display command
   
   // RPMA Measurement
   currentstateA = digitalRead(dataINA); // Read PSA sensor state
   if( prevstateA != currentstateA) // If there is change in input
     {
       if( currentstateA == HIGH ) // If input only changes from LOW to HIGH
         {
           duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
           rpmA = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
           prevmillis = micros(); // store time for nect revolution calculation
         }
     }
    prevstateA = currentstateA; // store this scan (prev scan) data for next scan
    Serial.println("RPM A .. ");
    Serial.println(rpmA);
  
  
   // RPMB Measurement
   currentstateB = digitalRead(dataINB); // Read PSB sensor state
   if( prevstateB != currentstateB) // If there is change in input
     {
       if( currentstateB == HIGH ) // If input only changes from LOW to HIGH
         {
           duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
           rpmB = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
           prevmillis = micros(); // store time for next revolution calculation
         }
     }
    prevstateB = currentstateB; // store this scan (prev scan) data for next scan
    Serial.println("RPM B .. ");
    Serial.println(rpmB);
  
    // Calculating average rpm 
    avg_rpm = (rpmA + rpmB) / 2;
    Serial.println("AVERAGE RPM .. ");
    Serial.println(avg_rpm);

    // Send RPM data to the LCD screen 
    Wire.print("RPM: ");
    Wire.print(avg_rpm);
    Wire.endTransmission(); //Stop I2C transmission
}
