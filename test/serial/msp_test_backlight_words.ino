/*
 * This example changes the colors on the LCD screen with an MSP-EXP432P401R
 */
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); 
  Serial1.write(124);
  Serial1.write('-');
  Serial1.write(9);
  allOFF();
  whiteON();
}

void loop() {

    Serial1.write(124);
    Serial1.write('-');
    Serial1.print("monkey boat");
    Serial.println("monkey boat");
    delay(2000);
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
