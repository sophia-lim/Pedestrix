/*
 * Test 1 : Sound sensor
 * Description : The following code prints the microphone input
 */

#define MIC A0
int val = 0;

void setup() {
  // put your setup code here, to run once:
  
 Serial.begin(9600);
 Serial.println("Start");
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(MIC);
  Serial.print("Microphone read: ");
  Serial.println(val); 
 val = analogRead(MIC)*50;
 if (val>1)  {
  digitalWrite(2, HIGH);
 } else {
  digitalWrite(2, LOW);
 }
} 
