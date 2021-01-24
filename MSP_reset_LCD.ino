 // Reset a SparkFun Serial LCD (16*2)
// Bob Stephens 03/06/2009
// -------------------------------------------------------------------------------

void resetLCD();
void setSplash();


// --------------------------------------------------------
void setup()
{
// start serial port
Serial1.begin(9600); // open serial
// setSplash();
}

// --------------------------------------------------------
void loop()
{
resetLCD();
}

void resetLCD() {
Serial1.write(0x07);
Serial1.write(18);
}

void setSplash() {
clearLCD();
goTo(3);
Serial1.write("Some text");
goTo(17);
Serial1.write("Second line");
delay(100);
Serial1.write(0x7C);
Serial1.write(10);
delay(5000);
clearLCD();
}
