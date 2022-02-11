/* Pitch Controls (Up and Down)
 * Two buttons which control the position of the elevator fins
 * Controlled with one stepper motor for both fins
 * One button pushes the fins down which will cause the sub to pitch downward
 * One button pushes the fins up which will cause the sub to pitch upwards
 */
/* Yaw Controls (Left and Right)
 * Two buttons which control the position of the Rudder fins
 * Controlled with one stepper motor for both fins
 * One button pushes the fins Left which will cause the sub to yaw leftward
 * One button pushes the fins Right which will cause the sub to yaw rightward
 */
/* Autonomous controls button
 * One button that will switch the sub into autonomous mode and the sub will make course adjustments using the gyro scope
 * The switch turns the mode on and off
 */
// Gyro
// 2 stepper motors (Step Pulse Control and Direction Control)
// 
// Defin pins
 
#define pitchDirPin 2
#define pitchStepPin 3
#define yawDirPin 4
#define yawStepPin 5
#define pitchUp 6
#define pitchDown 7
#define yawLeft 8
#define yawRight 9
 
// Variables
int pd = 250; // Pulse Delay period (Sensativity of motor)
boolean setPitchDir = LOW; // Set Pitch Direction
boolean setYawDir = LOW; // Set Pitch Direction
void checkPitchUp() {
  boolean mode = digitalRead(pitchUp);
  if (mode == HIGH) {
    setPitchDir = HIGH; //Clockwise
    while (mode == HIGH) {
      digitalWrite(pitchDirPin, setPitchDir);
      digitalWrite(pitchStepPin, HIGH);
      delayMicroseconds(pd);
      digitalWrite(pitchStepPin, LOW);
      delayMicroseconds(pd);
      
      mode = digitalRead(pitchUp);
    }
    return;
  }
  else {
    return;
  }
}
void checkPitchDown() {
  boolean mode = digitalRead(pitchDown);
  if (mode == HIGH) {
    setPitchDir = LOW; //Counter Clockwise
    while (mode == HIGH) {
      digitalWrite(pitchDirPin, setPitchDir);
      digitalWrite(pitchStepPin, HIGH);
      delayMicroseconds(pd);
      digitalWrite(pitchStepPin, LOW);
      delayMicroseconds(pd);
      
      mode = digitalRead(pitchDown);
    }
    return;
  }
  else {
    return;
  }
}
void checkYawLeft() {
  boolean mode = digitalRead(yawLeft);
  if (mode == HIGH) {
    setYawDir = HIGH; //Clockwise
    while (mode == HIGH) {
      digitalWrite(yawDirPin, setYawDir);
      digitalWrite(yawStepPin, HIGH);
      delayMicroseconds(pd);
      digitalWrite(yawStepPin, LOW);
      delayMicroseconds(pd);
      
      mode = digitalRead(yawLeft);
    }
    return;
  }
  else {
    return;
  }
}
void checkYawRight() {
  boolean mode = digitalRead(yawRight);
  if (mode == HIGH) {
    setYawDir = LOW; //Counter Clockwise
    while (mode == HIGH) {
      digitalWrite(yawDirPin, setYawDir);
      digitalWrite(yawStepPin, HIGH);
      delayMicroseconds(pd);
      digitalWrite(yawStepPin, LOW);
      delayMicroseconds(pd);
      
      mode = digitalRead(yawRight);
    }
    return;
  }
  else {
    return;
  }
}
/*
 * void checkAuthnomous() {
 * 
 * }
 */
void setup() {
  pinMode (pitchDirPin, OUTPUT);
  pinMode (pitchStepPin, OUTPUT);
  pinMode (yawDirPin, OUTPUT);
  pinMode (yawStepPin, OUTPUT);
  pinMode (pitchUp, INPUT);
  pinMode (pitchDown, INPUT);
  pinMode (yawLeft, INPUT);
  pinMode (yawRight, INPUT);
}
void loop() {
  checkPitchUp();
  checkPitchDown();
  checkYawLeft();
  checkYawRight();
  // checkAuthnomous();
}
