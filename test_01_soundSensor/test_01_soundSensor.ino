/*
 * Test 1 : Sound sensor
 * Description : The following code prints the microphone input
 */

#define MIC A0
int val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(0);
  Serial.println(val);
}
