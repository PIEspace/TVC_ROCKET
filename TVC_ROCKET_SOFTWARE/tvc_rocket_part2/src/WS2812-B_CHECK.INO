#include <FastLED.h>

#define LED_PIN     2   // Change this to the pin where your data line is connected
#define NUM_LEDS    1  // Change this to the number of LEDs in your strip

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // Fill the entire strip with a color (red in this case)
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(500);  // Pause for 500 milliseconds

  // Fill the entire strip with another color (green in this case)
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(500);  // Pause for 500 milliseconds
}
