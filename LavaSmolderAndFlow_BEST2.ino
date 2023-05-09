#include <Adafruit_NeoPixel.h> // Include the Adafruit NeoPixel library

#define PIN 6 // The pin number of the LED strip
#define NUM_LEDS 13 // The number of LEDs in the strip
#define NUM_SEGMENTS 6 // The number of segments to divide the strip into for the smolder animation
#define SEGMENT_SIZE 2 // The number of LEDs per segment for the smolder animation
#define BOIL_TIME 200 // The time between color changes during the smolder animation, in milliseconds
#define LAVA_SMOLDER_DELAY 5000 // The delay between the smolder and flow animations, in milliseconds
#define LED_RED 50 // The amount of red color to use for the lava flow animation
#define LED_GREEN 0 // The amount of green color to use for the lava flow animation
#define LED_BLUE 0 // The amount of blue color to use for the lava flow animation
#define FLOW_TIME 300 // The time between each step of the lava flow animation, in milliseconds

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800); // Create a new Adafruit NeoPixel object

bool isLavaFlowTime = false; // A boolean flag to keep track of whether it's time to play the lava flow animation
bool hasLavaFlowed = false; // A boolean flag to keep track of whether the lava flow animation has been played
unsigned long previousTime = 0; // The time at which the previous animation was played
const unsigned long LAVA_SMOLDER_TIME = 5000; // The duration of the smolder animation, in milliseconds

void setup() {
  strip.begin(); // Initialize the LED strip
  strip.show(); // Turn off all LEDs
  strip.setBrightness(255); // Set the brightness to full
}

void loop() {
  unsigned long currentTime = millis(); // Get the current time
  
  if (isLavaFlowTime) { // If it's time to play the lava flow animation
    if (!hasLavaFlowed) { // If the lava flow animation hasn't been played yet
      lavaFlow(); // Play the lava flow animation
      hasLavaFlowed = true; // Set the flag variable to indicate that the animation has been played
    }
    if (currentTime - previousTime >= FLOW_TIME * NUM_LEDS) { // If it's been long enough since the lava flow animation started
      isLavaFlowTime = false; // Set the flag variable to indicate that it's no longer time to play the lava flow animation
      hasLavaFlowed = false; // Reset the flag variable to prepare for the next time the animation is played
      previousTime = currentTime; // Update the previous time
    }
  } else { // If it's not time to play the lava flow animation
    lavaSmolder(); // Play the smolder animation
    if (currentTime - previousTime >= LAVA_SMOLDER_TIME) { // If it's been long enough since the smolder animation started
      strip.clear(); // Turn off all LEDs
      strip.show(); // Update the LED strip with the new colors
      previousTime = currentTime; // Update the previous time
      delay(2000); // Add a delay of 2 seconds
      isLavaFlowTime = true; // Set the flag variable to indicate that it's time to play the lava flow animation
    }
  }
}

void lavaSmolder() {
  unsigned long currentTime = millis(); // Get the current time
  unsigned long elapsedTime = 0; // Initialize the elapsed time
  
  while (elapsedTime < LAVA_SMOLDER_DELAY) { 

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

    // Wait for the desired duration
    delay(BOIL_TIME);
    elapsedTime += BOIL_TIME;
  }
  strip.clear();
  strip.show();
}

void lavaFlow() {
  // Define the LED color
  uint32_t ledColor = strip.Color(LED_RED, LED_GREEN, LED_BLUE); // Set the LED to a shade of red

  // Shift the LED color downward, with a delay between each step
  for (int j = 0; j < NUM_LEDS; j++) { // repeat for all LEDs
    for (int i = NUM_LEDS - 1; i >= 1; i--) {
      strip.setPixelColor(i, strip.getPixelColor(i - 1));
     }
    strip.setPixelColor(0, ledColor);
    strip.show(); // Show the updated pixel colors
    delay(FLOW_TIME); // Pause for a short period between each lava flow step
  }
  strip.clear(); // Turn off all LEDs at the end of the animation loop
}  
