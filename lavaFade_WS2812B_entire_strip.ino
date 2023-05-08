#include <Adafruit_NeoPixel.h>

//Code for Test strip of WS2812B

#define PIN 6
#define NUM_LEDS 200

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  for(int i=0; i<NUM_LEDS; i++) {
    // Calculate a sine wave value between 0 and 255
    int val = 128 + 127 * sin(millis() / 6000.0 * 2 * PI);
    strip.setPixelColor(i, strip.Color(val, 0, 0));
  }
  strip.show(); // Update LED strip with new colors
  delay(10); // Wait for a short period of time before updating again
}
