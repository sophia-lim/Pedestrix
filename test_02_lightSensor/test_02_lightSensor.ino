/*
 * Test 2 : Light sensor
 * Description : The following code prints the photocell input
 */

int lightSensor = 1;
int lightReading;
int LEDpin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
}

void loop() {
  //Read photocell
  lightReading = analogRead(lightSensor);

  //Print photocell read
  Serial.print("Analog Read = ");
  Serial.println(lightReading);

  //LED must turn on when light is stronger
  if (lightReading > 300) {
    digitalWrite(LEDpin, HIGH);  
  } else {
    digitalWrite(LEDpin,LOW);
  }
}
