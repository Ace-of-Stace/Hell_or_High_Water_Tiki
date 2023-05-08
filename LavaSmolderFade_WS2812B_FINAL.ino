#include <Adafruit_NeoPixel.h>  // Include the Adafruit_NeoPixel library

#define PIN 6                   // Define the pin number used to control the LED strip
#define NUM_LEDS 13             // Define the number of LEDs in the strip
#define NUM_SEGMENTS 6          // Define the number of segments to divide the strip into
#define SEGMENT_SIZE 2          // Define the size of each segment
#define BOIL_TIME 200           // Define the time between color changes in ms

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);  // Create a new instance of the Adafruit_NeoPixel class

void setup() {
  strip.begin();      // Initialize the LED strip
  strip.show();       // Set all pixels to 'off'
}

void loop() {
  // Generate random boiling effect with shades of red
  for (int i = 0; i < NUM_SEGMENTS; i++) {                 // Iterate through each segment of the LED strip
    int r = random(255);                                   // Generate a random shade of red
    int g = 0;                                              // Set green and blue values to 0 for a red-only effect
    int b = 0;
    for (int j = i * SEGMENT_SIZE; j < (i + 1) * SEGMENT_SIZE; j++) {    // Iterate through each LED in the segment
      strip.setPixelColor(j, strip.Color(r, g, b));        // Set the color of the LED to the random shade of red
    }
  }
  strip.show();         // Update the LED strip with the new colors
  delay(BOIL_TIME);     // Wait for a short period of time before updating again
}
