#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LEDS 13
#define NUM_SEGMENTS 6
#define SEGMENT_SIZE 2
#define BOIL_TIME 200 // Time between color changes in ms

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Generate random boiling effect with shades of red
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    int r = random(255);
    int g = 0;
    int b = 0;
    for (int j = i * SEGMENT_SIZE; j < (i + 1) * SEGMENT_SIZE; j++) {
      strip.setPixelColor(j, strip.Color(r, g, b)); // Set color of segment
    }
  }
  strip.show(); // Update LED strip with new colors
  delay(BOIL_TIME); // Wait for a short period of time before updating again
}
