/*
 * Test 1 : Sound sensor
 * Description : The following code prints the microphone input
 */

#define MIC A0
int val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
}

void led() {
 val = analogRead(MIC)*50;
 if (val>1)  {
  digitalWrite(2, HIGH);
 } else {
  digitalWrite(2, LOW);
 }
}

void loop() {
  // put your main code here, to run repeatedly:
  //val = analogRead(0);
  //Serial.println(val);
  led();
}
