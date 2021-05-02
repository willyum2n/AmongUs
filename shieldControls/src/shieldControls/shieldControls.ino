/* "Among Us" Shield UI
 *  This code will emulate the Shield UI from the "Among Us" Game so that we can have live action fun times
 */
#include <FastLED.h>
#define NUM_LEDS 7
#define DATA_PIN 16
CRGB leds[NUM_LEDS];

#define LED 2

#include "ShieldButton.hpp"
#define BTN_COUNT 7
ShieldButton btns[BTN_COUNT] = {
  ShieldButton(T0, 35),
  ShieldButton(T2, 35),
  ShieldButton(T3, 35),
  ShieldButton(T4, 35),
  ShieldButton(T5, 35),
  ShieldButton(T6, 35),
  ShieldButton(T7, 35),
};


void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("Among Us Shield UI");

  pinMode(LED,OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  
}

void loop() {

  // Handle TCP Communications ------------------------------------------------------------
  
  // Measure all the buttons --------------------------------------------------------------
  for(int i=0; i<BTN_COUNT; i++) {
    btns[i].loop();
    if (btns[i].clicked()) {
      leds[i] = (btns[i].state() ? btns[i].activeColor() : btns[i].inactiveColor());
    }
  }

  FastLED.show();
  
  delay(10);
}
