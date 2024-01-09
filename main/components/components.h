#ifndef COMPONENT_H
#define COMPONENT_H

#include <string.h>
#define UNKNOWN_PIN 0xFF

class Component {
public:
  uint8_t getPinMode(uint8_t pin);
  Component(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name);

private:
  const int num_pins;
  const String name;
  const int *pin_nums;
  const uint8_t *mds;
};

Component::Component(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name)
  : num_pins(number_of_pins), name(component_name), pin_nums(pin_numbers), mds(modes) {
  Serial.print("Initializing ");
  Serial.print(name);
  Serial.println("...");
  Serial.println();

  for (int i = 0; i < num_pins; i++) {
    Serial.print("Initializing pin ");
    Serial.print(pin_nums[i]);
    Serial.println();

    pinMode(pin_nums[i], mds[i]);

    Serial.print("Pin ");
    Serial.print(pin_nums[i]);
    Serial.print(" to ");

    if (getPinMode(pin_nums[i]) == INPUT) {
      Serial.println("INPUT");
    } else if (getPinMode(pin_nums[i]) == OUTPUT) {
      Serial.println("OUTPUT");
    } else {
      Serial.println("UNKNOWN PIN");
    }
  }
}


uint8_t Component::getPinMode(uint8_t pin) {
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);

  if (NOT_A_PIN == port) return UNKNOWN_PIN;

  if (0 == bit) return UNKNOWN_PIN;

  if (bit & bit - 1) return UNKNOWN_PIN;

  volatile uint8_t *reg, *out;
  reg = portModeRegister(port);
  out = portOutputRegister(port);

  if (*reg & bit)
    return OUTPUT;
  else if (*out & bit)
    return INPUT_PULLUP;
  else
    return INPUT;
}

#endif