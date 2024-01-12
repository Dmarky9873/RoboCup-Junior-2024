#ifndef MOTOR_H
#define MOTOR_H

#include "../components.h"
#include <Wire.h>
#include <Arduino.h>

class Motor : private Component {
public:
  Motor(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name) : Component(pin_numbers, modes, number_of_pins, component_name) {
    init();
  }

  void setDirection(bool forward);
};

void Motor::setDirection(bool forward) {
}

#endif
