/*
 * Test 2 : Light sensor
 * Description : The following code prints the photocell input
 */

int lightSensor = 0;
int lightReading;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightReading = analogRead(lightSensor);
  Serial.print("Analog Read = ");
  Serial.println(lightReading);
}
