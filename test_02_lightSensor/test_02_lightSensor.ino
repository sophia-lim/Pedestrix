/*
 * Test 2 : Light sensor
 * Description : The following code prints the photocell input
 */

int lightSensor = 0;
int lightReading;
int LEDpin = 11;
int LEDstrength;

void setup() {
  Serial.begin(9600);
}

void loop() {
  //Read photocell
  lightReading = analogRead(lightSensor);

  //Print photocell read
  Serial.print("Analog Read = ");
  Serial.println(lightReading);

  //LED must turn on when light is weaker
  lightReading = 1023 - lightReading;
  LEDstrength = map(lightReading, 0, 1023, 0, 255);
  analogWrite(LEDpin, LEDstrength);
}
