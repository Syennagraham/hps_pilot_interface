/*
 * This code displays RPM data to the terminal and LCD (if desired) using I2C
 * Proximity sensor A 
 *    Blue  - GND
 *    Black - 3
 *    Brown - 5V
 * Proximity sensor B
 *    Blue  - GND
 *    Black - 4
 *    Brown - 5V  
 * LCD
 *    RAW - 3.3V
 *    GND - GND
 *    SDA - Arduino SDA
 *    SCL - Arduino SCL
 *    
 * By: Syenna Graham - syennagraham@vt.edu
 */

#include <Wire.h>

#define DISPLAY_ADDRESS1 0x72 //This is the default address of the OpenLCD

const int dataINA = 3; //Proximity sensor input A (PSA)
const int dataINB = 4; //Proximity sensor input B (PSB) 

unsigned long prevmillis; // To store time
unsigned long duration; // To store time difference
unsigned long refresh; // To store time for refresh of reading

int rpm; //RPM to be output to terminal screen 
int rpmA; // RPM from sensor A value
int rpmB; // RPM from sensor B value
int avg_rpm; // (RPMA-RPMB)/ 2

boolean currentstateA; // Current state of PSA input scan
boolean prevstateA; // State of PSA sensor in previous scan

boolean currentstateB; // Current state of PSB input scan
boolean prevstateB; // State of PSB sensor in previous scan

void setup() {
    // Set up for the debugging serial monitor
    Serial.begin(9600); //Start serial communication at 9600 for debug statements
    Serial.println("RPM DATA ");

    // Set up for the RPM sensor readings
    pinMode(dataINA,INPUT);
    pinMode(dataINB,INPUT);        
    prevmillis = 0;
    prevstateA = LOW;  
    prevstateB = LOW;  
    Serial.begin(9600);

}

void loop() {
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
   currentstateA = digitalRead(dataINA); // Read RPMA sensor state
   if( prevstateA != currentstateA) // If there is change in input
     {
       if( currentstateA == HIGH ) // If input only changes from LOW to HIGH
         {
           duration = ( micros() - prevmillis ); // Time difference between revolution in microsecond
           rpmA = (60000000/duration); // rpm = (1/ time millis)*1000*1000*60;
           prevmillis = micros(); // store time for nect revolution calculation
         }
       else
        {
        rpmA = 0;
        }
     }
 
    prevstateA = currentstateA; // store this scan (prev scan) data for next scan
    //Serial.println("RPM A .. "); //Uncomment for debugging RPM A
    //Serial.println(rpmA);        //Uncomment for debugging RPM A
  
  
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
        else
         {
           rpmB = 0;
         }
     }
    prevstateB = currentstateB; // store this scan (prev scan) data for next scan
    //Serial.println("RPM B .. ");  //Uncomment for debugging RPM B
    //Serial.println(rpmB);         //Uncomment for debugging RPM B
  
    // Calculating average rpm 
    avg_rpm = (rpmA + rpmB) / 2;
    Serial.print("AVERAGE RPM ");
    Serial.print("\t");
    Serial.println(avg_rpm);

    // Send RPM data to the LCD screen 
    Wire.print("AVERAGE RPM: ");
    Wire.print(avg_rpm);
    delay(500);
    Wire.endTransmission(); //Stop I2C transmission
}
