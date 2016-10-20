//Check BPM every minute


//This methods maps the BPM to a colour
void pulseColour() {
  if (BPM < 80) {
    colorWipe(strip.Color(255, 0, 0), 50); // Red
  } else if (BPM >= 80 && BPM < 90) {
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
  } else if (BPM >= 90 && BPM < 120) {
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
  } else {
    colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
  }
}

//The uint32_t declaration reserves 32-bytes for the given variable
//NeoPixel color strings are only 24 bytes long, but there isn't a declaration for that.
//This method takes in a colour value in RGB and a wait time in millis
void colorWipe(uintt32_ c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
