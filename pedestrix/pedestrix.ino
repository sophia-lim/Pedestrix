/*
 * Pedestrix
 * Description: This sketch compiles all the previous test sketches in order to create the Pedestrix.
 * It takes as analog input, both a photo cell and a pulse sensor, and display the pulse through
 * a single LED, and the BPM through the NeoPixel Ring. 
 */

//Arduino Timer Object library
#include <TimerObject.h>

//Adafruit NeoPixel ring library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // Pin to blink led at each beat
int lightSensor = 1;
int lightReading;
#define PIN 6                     // Pin to blink NeoPixel Ring
boolean carNearby;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

// Will call the callback in the interval of 10 seconds
TimerObject *neoPixelTimer = new TimerObject(10000); 

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduino finds a beat.

//Function prototype
void colorWipe(uint32_t c, uint8_t wait);

//The uint32_t declaration reserves 32-bytes for the given variable
//NeoPixel color strings are only 24 bytes long, but there isn't a declaration for that.
//This method takes in a colour value in RGB and a wait time in millis
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    //delay(wait);
  }
}

//Function prototype
void pulseColour(); 

//This methods maps the BPM to a colour
void pulseColour() {
  if (BPM < 80) {
    colorWipe(strip.Color(255, 0, 0), 50); // Red
  } else if (BPM >= 80 && BPM < 90) {
    colorWipe(strip.Color(0, 255, 0), 50); // Green
  } else if (BPM >= 90 && BPM < 120) {
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
  } else {
    colorWipe(strip.Color(255, 255, 255), 50); // White RGBW
  }
}

//This method returns true when a car is nearby, and false when a car is not nearby
//It takes as parameter an integer, which is the analog reading from the photocell at A1

boolean isCarNearby(int lightReading){
  if (lightReading > 300) {
    carNearby = true;
  } else {
    carNearby = false;
  }
  return carNearby;
}

void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  
  //Sets up to read Pulse Sensor signal every 2mS
  interruptSetup();
  
  //Sets up NeoPixel Ring
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  neoPixelTimer->setOnTimer(&pulseColour);
  neoPixelTimer->Start();
}

void loop(){
  
  //Read photocell
  lightReading = analogRead(lightSensor);
  
  //If a car is detected through photocell, update the neoPixelTimer
  if (isCarNearby(lightReading)) {
    neoPixelTimer->Update();
  }
  
  //Print photocell read
  Serial.print("Analog Read = ");
  Serial.println(lightReading);
  
  if (QS == true){                       // Quantified Self flag is true when arduino finds a heartbeat
    Serial.print("BPM = ");
    Serial.println(BPM);
  }
}
