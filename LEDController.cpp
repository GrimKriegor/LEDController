#include <Arduino.h>
#include <LEDController.h>

LEDController::LEDController(uint8_t pin) {
  _pin = pin;
  _status = false;
  pinMode(_pin, OUTPUT);
}

bool LEDController::status() {
  return _status;
}

void LEDController::on() {
  digitalWrite(_pin, HIGH);
  _status = true;
}

void LEDController::off() {
  digitalWrite(_pin, LOW);
  _status = false;
}

void LEDController::toggle() {
  _status = !_status;
  if (_status) {
    this->off();
    return;
  }
  this->on();
}

void LEDController::dim(uint8_t intensity) {
  analogWrite(_pin, intensity);
  _status = true;
}

void LEDController::onOff(int cycle_duration) {
  this->on();
  delay(cycle_duration);
  this->off();
  delay(cycle_duration);
}

void LEDController::stepDim(int cycle_duration, uint8_t begin, uint8_t end) {
  int _delta = end - begin;
  int _steps = abs(_delta);
  int _step_duration = cycle_duration / _steps;
  bool _delta_positive = true;
  if (_delta < 0) {
    _delta_positive = false;
  }
  if (_delta_positive) {
    for (uint8_t i = begin; i < end; i++) {
      this->dim(i);
      delay(_step_duration);
    }
  } else {
    for (uint8_t i = begin; i > end; i--) {
      this->dim(i);
      delay(_step_duration);
    }
  }
}

void LEDController::cycleDim(int cycle_duration, uint8_t min, uint8_t max) {
  this->stepDim(cycle_duration/2, min, max);
  this->stepDim(cycle_duration/2, max, min);
}
