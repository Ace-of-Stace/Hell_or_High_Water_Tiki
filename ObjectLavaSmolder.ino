#include <Adafruit_NeoPixel.h>

class LavaSmolder {
public:
  LavaSmolder(int numLeds, int numSegments, int segmentSize, int boilTime, int pin); // Constructor
  void begin(); // Initializes the LED strip
  void update(); // Updates the LED strip with a new boiling effect

private:
  Adafruit_NeoPixel strip; // The LED strip object
  int numLeds; // The number of LEDs in the strip
  int numSegments; // The number of segments to divide the strip into
  int segmentSize; // The size of each segment
  int boilTime; // The time between color changes in ms
  unsigned long previousMillis = 0; // The time at which the last update occurred

  void generateBoilingEffect(); // Generates a random boiling effect with shades of red

public:
  static const int NUM_LEDS = 13; // The number of LEDs in the strip as a static constant
  static const int PIN = 6; // The pin number used to control the LED strip as a static constant
  static const int NUM_SEGMENTS = 6; // The number of segments to divide the strip into as a static constant
  static const int SEGMENT_SIZE = 2; // The size of each segment as a static constant
  static const int BOIL_TIME = 200; // The time between color changes in ms as a static constant
};

// Constructor implementation
LavaSmolder::LavaSmolder(int numLeds, int numSegments, int segmentSize, int boilTime, int pin) :
  strip(numLeds, pin, NEO_GRB + NEO_KHZ800),
  numLeds(numLeds),
  numSegments(numSegments),
  segmentSize(segmentSize),
  boilTime(boilTime)
{}

// Initializes the LED strip
void LavaSmolder::begin() {
  strip.begin();
  for (int i = 0; i < numLeds; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // Set the initial color of each LED to black
  }
  strip.show();
}


// Updates the LED strip with a new boiling effect
void LavaSmolder::update() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= boilTime) {
    previousMillis = currentMillis;
    generateBoilingEffect();
    strip.show();
  }
}

// Generates a random boiling effect with shades of red
void LavaSmolder::generateBoilingEffect() {
  for (int i = 0; i < numSegments; i++) {
    int r = random(255);
    int g = 0;
    int b = 0;
    for (int j = i * segmentSize; j < (i + 1) * segmentSize; j++) {
      strip.setPixelColor(j, strip.Color(r, g, b));
    }
  }
}

LavaSmolder lavaSmolder(LavaSmolder::NUM_LEDS, LavaSmolder::NUM_SEGMENTS, LavaSmolder::SEGMENT_SIZE, LavaSmolder::BOIL_TIME, LavaSmolder::PIN); // Creates an instance of the LavaSmolder class with the specified parameters

void setup() {
  lavaSmolder.begin(); // Initializes the LED strip
}

void loop() {
  lavaSmolder.update(); // Updates the LED strip with a new boiling effect
}
