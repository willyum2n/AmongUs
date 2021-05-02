#include "ShieldButton.hpp"

ShieldButton::ShieldButton(int touchPin, int threshold) {
  _touchPin = touchPin;
  _threshold = threshold;
}

void ShieldButton::loop() {
  int sensorValue = 0;  // Raw value from the Touch Sensor
  int touchValue = 0;   // Filtered value from the Touch Sensor sans glitches
  
  // Get the current value of the TouchPad. This value seems to represent the amount of charge/discharge cyles that the underlying circuitry makes
  // The more capacitance in the circuit, the few cycles
  sensorValue = touchRead(_touchPin);
  
  // There are glitches in the touch values when the underlying circuit resets. The glitch drives the value sharply toward 0. We need to ignore 
  // these glitches. These glitches only present once each 10ms loop, so take the higher value of the 2
  if (sensorValue > _lastTouchValue) {
    touchValue = sensorValue;
  } else {
    touchValue = _lastTouchValue;
  }

  // reset the clicked flag
  _clicked = false;
  
  // Did we just go from Untouched ---> Touched?
  if (touchValue < _threshold) {
    // Button is Touched...But was it JUST touched?
    if (_state == false) {
      // Our last state is "not touched" and we are now touched. set the clicked flag!
      _clicked = true;
    }
  }

  // Update all internal states/values
  _lastTouchValue = touchValue;
  
}

bool ShieldButton::clicked() {
  return _clicked;
}

bool ShieldButton::state() {
  return _state;
}

CRGB ShieldButton::activeColor() {
  return _activeColor;
}

CRGB ShieldButton::inactiveColor() {
  return _inactiveColor;
}
