/*
 * This code is for testing RPM with two proximity data sensors and an MSP432
 * Proximity sensor A 
 *    Blue  - GND
 *    Black - P2.6
 *    Brown - 5V
 * Proximity sensor B
 *    Blue  - GND
 *    Black - P2.4
 *    Brown - 5V  
 *    
 *    By: Syenna Graham
 */

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

void setup()
{
  pinMode(dataINA,INPUT);
  pinMode(dataINB,INPUT);        
  prevmillis = 0;
  prevstateA = LOW;  
  prevstateB = LOW;  
  Serial.begin(9600);
}

void loop()
{
  
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

}
