/* 
 *  This example reads a pressure sensor out to an LCD screen using Arduino UNO
 *  
 *  Pins from pressure sensor to Arduino
 *  PS Black to GND
 *  PS Red to 5V
 *  PS Yellow to arduino A1
 *  
 */


void setup()
{
  
  Serial1.begin(9600); //Begin local communication for debug statements
  Serial.begin(9600); //Begin communication with OpenLCD
  Serial1.write(124);
  Serial1.write('-');
  Serial1.write(9);
  allOFF();
  whiteON();

}

void loop()
{

  whiteON();

  float pa = pressure();
  
  float top = 0.75;
  float bottom = 0.40;

  if( bottom < pa > top ) 
  {
    greenON();
  }
  else
  {
    redON();
  }
}

int pressure()
{

//Send the clear command to the display - this returns the cursor to the beginning of the display
  Serial1.write('|'); //Setting character
  Serial1.write('-'); //Clear display  

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
    
    Serial1.print("Pressure: ");
    Serial1.println(pressure_bar);    
    
    delay(3000);
    return pressure_bar;
}

void whiteON() {
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(187); //Set green backlight amount to 0% 
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(217); //Set blue backlight amount to 0% 
  
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(157); //Set white/red backlight amount to 100% 
  delay(3000);
}


void redON() {
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(158); //Set green backlight amount to 0% 
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(188); //Set blue backlight amount to 0% 
  
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(157); //Set white/red backlight amount to 100% 
  delay(3000);
}

void blueON() {
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(158); //Set green backlight amount to 0% 
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(128); //Set red backlight amount to 0%  

  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(217); //Set blue backlight amount to 100%
  delay(3000);
}

void greenON() {
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(188); //Set blue backlight amount to 0% 
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(128); //Set red backlight amount to 0%  

  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(187); //Set green backlight amount to 100%
  delay(3000);
}

void allOFF(void)
{
  
  // Set all colors to 0
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(128); //Set white/red backlight amount to 0%
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(158); //Set green backlight amount to 0% 
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write(188); //Set blue backlight amount to 0%
  Serial1.write('|'); //Put LCD into setting mode
  Serial1.write('-'); //Set blue backlight amount to 0%
  delay(500);

}
