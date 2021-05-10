#include "ShieldButton.hpp"

ShieldButton::ShieldButton(int touchPin, int threshold) {
  _touchPin = touchPin;
  _threshold = threshold;
}

void ShieldButton::loop() {

  _clicked = false;   // Reset our clicked flag. This will only be true on the rising edge of the button being clicked.
  
  // If we are in the middle of a debounce...exit any further processing
  if (millis() < _debounceTime) {
    return;
  }

  // Get the current value of the TouchPad. This value seems to represent the amount of charge/discharge cyles that the underlying circuitry makes
  // The more capacitance in the circuit, the few cycles
  int currentTouch = touchRead(_touchPin);
  int touchValue = 0;
  // There are glitches in the touch values when the underlying circuit resets. The glitch drives the value sharply toward 0. We need to ignore 
  // these glitches. These glitches only present once each 10ms loop, so take the higher value of the 2
  if (currentTouch > _lastTouchValue) {
    touchValue = currentTouch;
  } else {
    touchValue = _lastTouchValue;
  }

  bool isTouched = touchValue < _threshold;
  // Did our button state change?
  if (isTouched != _isTouched) {
    // Our touch state has changed. But which way? Are we moving to touched or are we moving to untouched?
    _clicked = (touchValue < _threshold);
    if (_clicked) {
      _debounceTime = millis() + _debounceDuration_ms;   // The button was just clicked. Start debouncing
    }
  } else {
    _clicked = false;
  }

  if (debugOn) {
    Serial.println("touchValue=" + String(touchValue) + ", isTouched(" + String(isTouched) + "," + String(_isTouched) + "), _clicked=" + String(_clicked));
  }

  _isTouched = isTouched;
  _lastTouchValue = currentTouch;
  
}

bool ShieldButton::clicked() {
  return _clicked;
}

bool ShieldButton::isTouched() {
  return _isTouched;
}

CRGB ShieldButton::activeColor() {
  return _activeColor;
}

CRGB ShieldButton::inactiveColor() {
  return _inactiveColor;
}

bool ShieldButton::isActive() {
  return _isActive;
}

void ShieldButton::isActive(bool value) {
  _isActive = value;
}

void ShieldButton::toggleActive() {
  _isActive = ! _isActive;
}
