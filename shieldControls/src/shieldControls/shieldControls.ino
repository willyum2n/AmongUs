/* "Among Us" Shield UI
 *  This code will emulate the Shield UI from the "Among Us" Game so that we can have live action fun times
 */
#include "ShieldButton.hpp"
#include "common.h"
#include "serialComm.h"
#include "tcpComm.h"

#include <FastLED.h>

// Button Array
#define BTN_COUNT 7
CRGB buttonLeds[BTN_COUNT];       // LED strip for the Button backlighting
ShieldButton btns[BTN_COUNT] = {    
                          // All the following data was determined experimentally
  ShieldButton(T3, 56, buttonLeds, 0),   // Sensor 0   - Untouched=59, 1 Finger=55, 2 Fingers=50, 3 Fingers=48
  ShieldButton(T0, 58, buttonLeds, 1),   // Sensor 1   - Untouched=61, 1 Finger=57, 2 Fingers=53, 3 Fingers=49
  ShieldButton(T8, 40, buttonLeds, 2),   // Sensor 2   - Untouched=43, 1 Finger=39, 2 Fingers=35, 3 Fingers=33
  ShieldButton(T7, 63, buttonLeds, 3),   // Sensor 3   - Untouched=69, 1 Finger=62, 2 Fingers=54, 3 Fingers=51
  ShieldButton(T6, 66, buttonLeds, 4),   // Sensor 4   - Untouched=71, 1 Finger=64, 2 Fingers=55, 3 Fingers=51
  ShieldButton(T5, 64, buttonLeds, 5),   // Sensor 5   - Untouched=68, 1 Finger=63, 2 Fingers=57, 3 Fingers=53
  ShieldButton(T4, 55, buttonLeds, 6),   // Sensor 6   - Untouched=58, 1 Finger=54, 2 Fingers=49, 3 Fingers=47
};

//-----------------------------------------------------------------------------------------------------------
void setup() {
//-----------------------------------------------------------------------------------------------------------
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("Among Us Shield UI");

//  btns[0].debugOn = true;

//  //TODO: REMOVE
//  for(int i=0; i<BTN_COUNT; i++) {
//    btns[i].enabled(true);
//  }
//  btns[0].currentColor(CRGB::Red);
//  btns[1].currentColor(CRGB::Green);
//  btns[2].currentColor(CRGB::Blue);
//  btns[3].currentColor(CRGB::White);
//  btns[4].currentColor(CRGB::Red);
//  btns[5].currentColor(CRGB::Green);
//  btns[6].currentColor(CRGB::Blue);
  
  // Configure FastLED with Led Strips
  FastLED.addLeds<NEOPIXEL, ShieldButton::LED_PIN>(buttonLeds, BTN_COUNT);                   // LEDs that are backlighting the Sensors
  
}

//-----------------------------------------------------------------------------------------------------------
long ledTimer = 0;  // Used to animate the LEDs to test them
int currentLed = 0;
int dir = 1;
void loop() {
//-----------------------------------------------------------------------------------------------------------
  
  loop_comms();   // Handle Serial Communications

  // Handle TCP Communications ------------------------------------------------------------
  
  // Measure all the buttons --------------------------------------------------------------
  int targetMetCount = 0;
  for(int i=0; i<BTN_COUNT; i++) {

    // Process button 
    btns[i].loop();
    if (btns[i].targetMet())
      targetMetCount++;
  }

//  // Check the entire Shield Tasks state. Did we finish the task?
//  if (activeCount == BTN_COUNT) {
//    // WE WON!
//    CompleteTask();
//    StopTask();
//  }

  FastLED.show();
//  delay(100);
}

/* 
 * This function will cause the Task to Start up. This will include turning on the 
 * General lighting so the task is visble in a dark room and picking a random sequence 
 * of activity states for the shield buttons
 */
void StartTask() {
}

void CompleteTask() {
}

void StopTask() {
}
