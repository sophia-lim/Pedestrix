/*
 * Test 4 : Pulse sensor
 * Description: The following code prints out the BPM readings 
 * of the pulse sensor. An LED blinks to user's live heartbeat.
 * Original Pulse Sensor Amped 1.4 code taken from Joel Murphy and Yury Gitman at http://www.pulsesensor.com
 * Edits: The BPM is printed out when a pulse is detected
 */

//Adafruit NeoPixel ring library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // Pin to blink led at each beat
#define PIN 6                     // Pin to blink NeoPixel Ring

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded! 
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat". 
volatile boolean QS = false;        // becomes true when Arduino finds a beat.

void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  Serial.begin(115200);             // we agree to talk fast!
  //Sets up to read Pulse Sensor signal every 2mS
  interruptSetup();
  //Sets up NeoPixel Ring
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop(){
  if (QS == true){                       // Quantified Self flag is true when arduino finds a heartbeat
    Serial.print("BPM = ");
    Serial.println(BPM);
  }
}



