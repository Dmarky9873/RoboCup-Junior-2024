#include "components.h"

Component::Component(int pin_numbers[], int states[], int number_of_pins) : 
    pin_nums(pin_numbers), modes(new int[number_of_pins]), number_of_pins(number_of_pins), name(component_name){

    Serial.print("Initializing ");
    Serial.print(name);
    Serial.println("...");
    Serial.println()

    for(int i = 0; i < number_of_pins; i++) {
      Serial.print("Initializing pin ");
      Serial.print(pin_numbers[i]);
      Serial.println();

      pinMode(pin_numbers[i], modes[i]);

      Serial.print("Pin ")
      Serial.print(pin_numbers[i]);
      Serial.print(" to ")

      if (getPinMode(pin_numbers[i]) == INPUT) {
        Serial.println("INPUT")
      } else if (getPinMode(pin_numbers[i]) == OUTPUT) {
        Serial.println("OUTPUT")
      } else {
        Serial.println("UNKNOWN PIN")
      }

    }
}

#define UNKNOWN_PIN 0xFF

Component::getPinMode(uint8_t pin)
{
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

