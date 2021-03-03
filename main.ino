/*
 * This code displays RPM data to the LCD using I2C
 *  * Proximity sensor A 
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
 * By: Syenna Graham   
 * 
 * TO DO:
 * 1. Test pressure sensors
 * 2. Correlate depth data to color in main loop
 * 3. Output data to SD card
 */

#include <Wire.h>

#define DISPLAY_ADDRESS1 0x72 //This is the default address of the OpenLCD

const int dataINA = 3; //Proximity sensor input A (PSA)
const int dataINB = 4; //Proximity sensor input B (PSB) 

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
    Wire.write('|');  //Put LCD into setting mode
    Wire.write('-');  //Send clear display command
    Wire.write(9);    // Enable/disable splash screen
    Wire.write('|');  //Put LCD into setting mode 
    allOFF();         // Turn all backlight colors off
    whiteON();        // Turn backlight to white
    Wire.endTransmission();

    // Set up for the RPM sensor readings
    pinMode(dataINA,INPUT);
    pinMode(dataINB,INPUT);        
    prevmillis = 0;
    prevstateA = LOW;  
    prevstateB = LOW;  
    Serial.begin(9600);
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
        else
         {
           rpmB = 0;
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
