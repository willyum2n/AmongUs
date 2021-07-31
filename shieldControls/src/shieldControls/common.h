#pragma once

void(* resetMcu) (void) = 0;  //< declare reset function at address 0

bool buttonMessagesEnabled = false;


void testLeds() {
//  // LED Testing code
//  if (ledTimer < millis()) {
//    Serial.println("testing led");
//    ledTimer += 250;
//
//    // Turn off the currentLed
//    leds_button[currentLed] = CRGB::Black;
//
//    // Move to the next LED
//    currentLed += dir;
//    if (currentLed >= BTN_COUNT) {
//      dir = -1;
//      currentLed = BTN_COUNT - 2;
//    }
//    if (currentLed <= -1) {
//      dir = 1;
//      currentLed = 1;
//    }
//
//    // Light up the current LED
//    leds_button[currentLed] = CRGB::Red; 
//  }  
}
