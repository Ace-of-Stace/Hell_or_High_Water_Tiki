#include <Adafruit_NeoPixel.h>

class LavaFlow {
  private:
    const uint8_t PIN = 6; // define the pin used to control the LED strip
    const uint16_t NUM_LEDS = 13; // define the number of LEDs in the strip
    Adafruit_NeoPixel strip; // create a new NeoPixel object with the specified number of LEDs, pin number, and color format
    const uint8_t maxBrightness = 255; // define the maximum brightness value for the LEDs

  public:
    LavaFlow() : strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800) {} // initialize the NeoPixel object with the specified number of LEDs, pin number, and color format

    void begin() {
      strip.setBrightness(150); // set the brightness of the LEDs to a low value to prevent them from being too bright
      strip.begin(); // initialize the LED strip
      strip.show(); // turn off all LEDs to start
    }

    void loop() {
      colorWipe(strip.Color(255, 0, 0), 3); // call the colorWipe function with red color and a delay of 50ms
      fadeToBlack(10); // fade the LEDs to off with a delay of 10ms
    }

    // Fill the dots one after the other with a color
    void colorWipe(uint32_t c, uint8_t wait) {
      for(uint16_t i = 0; i < strip.numPixels(); i++) { // loop through each LED in the strip
        for(uint8_t brightness = 0; brightness < maxBrightness; brightness++) { // loop through each brightness level from 0 to the maximum brightness
          strip.setPixelColor(i, strip.Color(brightness, 0, 0, brightness)); // set the color of the LED to a shade of red based on the current brightness level
          strip.show(); // update the LED strip with the new color
          delay(wait); // wait for the specified delay time
        }
      }
    }

    // Fade the LEDs to off
    void fadeToBlack(uint8_t wait) {
      for(int i = maxBrightness; i >= 0; i--) { // loop through each brightness level from the maximum brightness to 0
        for(int j = 0; j < strip.numPixels(); j++) { // loop through each LED in the strip
          strip.setPixelColor(j, strip.Color(i, 0, 0, i)); // set the color of the LED to a shade of red based on the current brightness level
        }
        strip.show(); // update the LED strip with the new color
        delay(wait); // wait for the specified delay time
      }
    }
};

LavaFlow lavaFlow; // create an instance of the LavaFlow class

void setup() {
  lavaFlow.begin(); // call the begin function of the LavaFlow object to initialize the LED strip
}

void loop() {
  lavaFlow.loop(); // call the loop function of the LavaFlow object to animate the LED strip
}
