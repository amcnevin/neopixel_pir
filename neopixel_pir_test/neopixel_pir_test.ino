#include <Adafruit_NeoPixel.h>
#define PIXEL_PIN  6
#define N_LEDS 144

int PIR = 2;
int PIR_STATE = LOW;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  strip.begin();
}

void loop() {

  if (detect()) {
    //goHokies();
    rainbow(20);
  } else {
    clear();
  }

}

// detect motion
static bool detect() {
  int val = digitalRead(PIR);
  Serial.println(val);
  return val;
}

// chase the strip
static void chase(uint32_t c) {
  for (uint16_t i = 0; i < strip.numPixels() + 4; i++) {
    strip.setPixelColor(i  , c);
    strip.setPixelColor(i - 10, 0);
    strip.show();
    delay(25);
  }
}

// shut off each pixel
static void clear() {
  for (uint16_t i = 0; i < strip.numPixels() + 4; i++) {
    strip.setPixelColor(i, 0);
    strip.show();
  }
}

// execute the rainbow cycle
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// cycle colors
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// chase orange and maroon
void goHokies() {
  chase(strip.Color(255, 102, 00));
  chase(strip.Color(102, 00, 00));
}
