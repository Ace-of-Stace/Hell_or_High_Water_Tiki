#include <Adafruit_NeoPixel.h>

class LavaSmolder {
public:
  LavaSmolder(int numLeds, int numSegments, int segmentSize, int boilTime, int pin);
  void begin();
  void update();

private:
  Adafruit_NeoPixel strip;
  int numLeds;
  int numSegments;
  int segmentSize;
  int boilTime;
  unsigned long previousMillis = 0;

  void generateBoilingEffect();

public:
  static const int NUM_LEDS = 13;
  static const int PIN = 6;
  static const int NUM_SEGMENTS = 6;
  static const int SEGMENT_SIZE = 2;
  static const int BOIL_TIME = 200;
};

LavaSmolder::LavaSmolder(int numLeds, int numSegments, int segmentSize, int boilTime, int pin) :
  strip(numLeds, pin, NEO_GRB + NEO_KHZ800),
  numLeds(numLeds),
  numSegments(numSegments),
  segmentSize(segmentSize),
  boilTime(boilTime)
{}

void LavaSmolder::begin() {
  strip.begin();
  strip.show();
}

void LavaSmolder::update() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= boilTime) {
    previousMillis = currentMillis;
    generateBoilingEffect();
    strip.show();
  }
}

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

LavaSmolder lavaSmolder(LavaSmolder::NUM_LEDS, LavaSmolder::NUM_SEGMENTS, LavaSmolder::SEGMENT_SIZE, LavaSmolder::BOIL_TIME, LavaSmolder::PIN);

void setup() {
  lavaSmolder.begin();
}

void loop() {
  lavaSmolder.update();
}
