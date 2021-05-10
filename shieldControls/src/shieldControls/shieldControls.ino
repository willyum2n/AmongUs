/* "Among Us" Shield UI
 *  This code will emulate the Shield UI from the "Among Us" Game so that we can have live action fun times
 */
#include "ShieldButton.hpp"

void(* resetMcu) (void) = 0;  //< declare reset function at address 0

// Serial Communication
const byte COMM_MSGSIZE = 16;
String commMessage = "";      // a String to hold incoming serial data/messages
char msgTerminator1 = '\n';   // signifies the end of a message
char msgTerminator2 = '\r';   // signifies the end of a message

// TCP Communication
// TODO:

// Capacitive Touch
#define BTN_COUNT 7
ShieldButton btns[BTN_COUNT] = {
                          // All the following data was determined experimentally
  ShieldButton(T3, 56),   // Sensor 0   - Untouched=59, 1 Finger=55, 2 Fingers=50, 3 Fingers=48
  ShieldButton(T0, 58),   // Sensor 1   - Untouched=61, 1 Finger=57, 2 Fingers=53, 3 Fingers=49
  ShieldButton(T8, 40),   // Sensor 2   - Untouched=43, 1 Finger=39, 2 Fingers=35, 3 Fingers=33
  ShieldButton(T7, 63),   // Sensor 3   - Untouched=69, 1 Finger=62, 2 Fingers=54, 3 Fingers=51
  ShieldButton(T6, 66),   // Sensor 4   - Untouched=71, 1 Finger=64, 2 Fingers=55, 3 Fingers=51
  ShieldButton(T5, 64),   // Sensor 5   - Untouched=68, 1 Finger=63, 2 Fingers=57, 3 Fingers=53
  ShieldButton(T4, 55),   // Sensor 6   - Untouched=58, 1 Finger=54, 2 Fingers=49, 3 Fingers=47
};

// General Purpose Lighting around the Unit to grab player Attention
#define LIGHTING_COUNT 30

#include <FastLED.h>
#define LED_BUTTONS_PIN 16
#define LED_GENERAL_LIGHTING_PIN 17
CRGB leds_button[BTN_COUNT];
CRGB leds_general[LIGHTING_COUNT];

//-----------------------------------------------------------------------------------------------------------
void setup() {
//-----------------------------------------------------------------------------------------------------------
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("Among Us Shield UI");

  FastLED.addLeds<NEOPIXEL, LED_BUTTONS_PIN>(leds_button, BTN_COUNT);                   // LEDs that are backlighting the Sensors
//  FastLED.addLeds<NEOPIXEL, LED_GENERAL_LIGHTING_PIN>(leds_general, LIGHTING_COUNT, BTN_COUNT);    // LEDs that are general lighting for the entire UI


  btns[0].debugOn = true;
  
}

//-----------------------------------------------------------------------------------------------------------
long ledTimer = 0;  // Used to animate the LEDs to test them
int currentLed = 0;
int dir = 1;
void loop() {
//-----------------------------------------------------------------------------------------------------------

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
  
  // Handle Serial Communications ------------------------------------------------------------
  

  // Handle TCP Communications ------------------------------------------------------------
  
  // Measure all the buttons --------------------------------------------------------------
  int activeCount = 0;
  for(int i=0; i<BTN_COUNT; i++) {

    // Process button 
    btns[i].loop();
    
    // Update button activity
    if (btns[i].clicked()) {
      btns[i].toggleActive();
    }

    if (btns[i].isActive()) {
      activeCount++;
      leds_button[i] = btns[i].inactiveColor();   // Set button color
    } else {
      leds_button[i] = btns[i].activeColor();     // Set button color
    }
     
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
