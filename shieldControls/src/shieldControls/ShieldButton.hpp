#pragma once
#include <FastLED.h>


class ShieldButton {

  private:
    int _touchPin;                    // The Cap Sense pin that this button uses
    int _ledIndex;                    // The index of the LED in the WS2812 strip
    int _threshold;                   // This is the value at which we can decide if a button has been pressed or not
    int _lastTouchValue;              // There are glitches in the button values each second. Tracking the last value will allow us to filter out these glitches
    int _debounceDuration_ms = 25;    // Software debounce for stopping....well...bouncing during touch
    long _debounceTime = 0;           // The time marking (using millis()) that, until passed, will lock out any button presses

    bool _isTouched = false;          // Indicates if the button is currently pressed or not
    bool _clicked = false;            // Indicates that the button was JUST press (Positive Edge)
    CRGB* _ledStrip;                   // The array used by FastLED to render color
    int _stripIndex;                   // The index into the array where this button lives
    CRGB _currentColor = CRGB::Black; // The color that is currently shining
    CRGB _targetColor = CRGB::Black;  // The color that this button should be to have the target met
    bool _targetMet = false;          // returns whether this button is the correct color
    bool _enabled = false;            // Enables/Disables the button
    
    
  public:
    const static int LED_PIN = 16;    // The PIN that all Button LEDs are connected to
    
    ShieldButton(int touchPin, int threshold, CRGB *ledStrip, int stripIndex);
    void loop();          // This should be run in the main loop so this class can update its values
    bool clicked();       // This is only triggered when the button is pressed (Positive Edge only)
    bool isTouched();     // Returns if the button is pressed or released
    CRGB currentColor();
    void currentColor(CRGB newColor);
    CRGB targetColor();
    void targetColor(CRGB newTarget);
    bool targetMet();     // Returns whether this button has met it's target

    bool enabled();
    void enabled(bool value);

    bool debugOn = false;
};
