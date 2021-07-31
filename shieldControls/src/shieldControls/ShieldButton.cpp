#pragma once

#include "ShieldButton.hpp"
#include <FastLED.h>

ShieldButton::ShieldButton(int touchPin, int threshold, CRGB *ledStrip, int stripIndex) {
  _touchPin = touchPin;
  _threshold = threshold;
  _ledStrip = ledStrip;
  _stripIndex = stripIndex;
  _enabled = false;
  _currentColor = CRGB::Black;
  _targetMet = false;
}

void ShieldButton::loop() {

  if ( ! _enabled) {
    // Button is not enabled. No need to process anything
    return;
  }
    
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
      // Update the button color because of this click

      // Get the single value of the Color so it can be compared to predefined colors
      unsigned int colorVal = (_currentColor.r << 16) + (_currentColor.g << 8) + _currentColor.b;

      switch (colorVal) {
        case CRGB::Red:
          currentColor(CRGB::Green);
          break;
        case CRGB::Green:
          currentColor(CRGB::Blue);
          break;
        case CRGB::Blue:
          currentColor(CRGB::White);
          break;
        case CRGB::White:
          currentColor(CRGB::Red);
          break;
        default:
          currentColor(CRGB::Yellow);
          break;

      }
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

CRGB ShieldButton::currentColor() {
  return _currentColor;
}
void ShieldButton::currentColor(CRGB newColor) {
  if (_enabled) {
    _currentColor = newColor;
    Serial.println("ShieldButton::currentColor() [" + String(_stripIndex) + "] = " + String(newColor));
    _ledStrip[_stripIndex] = _currentColor;
  }
}

CRGB ShieldButton::targetColor() {
  return _targetColor;
}
void ShieldButton::targetColor(CRGB newTarget) {
  _targetColor = newTarget;
}

bool ShieldButton::targetMet() {
  return (_enabled && (_targetColor == _currentColor));
}

bool ShieldButton::enabled() {
  return _enabled;
}

void ShieldButton::enabled(bool value) {
  _enabled = value;
  if ( ! _enabled) {
    _currentColor[0] = CRGB::Black;
  }
}
