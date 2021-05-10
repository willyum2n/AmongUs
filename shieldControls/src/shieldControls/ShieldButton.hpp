#pragma once
#include <FastLED.h>


class ShieldButton {

  private:
    int _touchPin;          // The Cap Sense pin that this button uses
    int _threshold;         // This is the value at which we can decide if a button has been pressed or not
    int _lastTouchValue;    // There are glitches in the button values each second. Tracking the last value will allow us to filter out these glitches
    bool _isTouched = false;    // Indicates if the button is currently pressed or not
    bool _clicked = false;  // Indicates that the button was JUST press (Positive Edge)
    CRGB _activeColor = CRGB::White;
    CRGB _inactiveColor = CRGB::Red;
    bool _isActive = false;

    int _debounceDuration_ms = 25;  // Software debounce for stopping....well...bouncing during touch
    long _debounceTime = 0;         // The time marking (using millis()) that, until passed, will lock out any button presses
    
  public:
    ShieldButton(int touchPin, int threshold);
    void loop();      // This should be run in the main loop so this class can update its values
    bool clicked();   // This is only triggered when the button is pressed (Positive Edge only)
    bool isTouched();     // Returns if the button is pressed or released
    CRGB activeColor();
    CRGB inactiveColor();

    bool isActive();
    void isActive(bool value);
    void toggleActive();

    bool debugOn = false;
};
