#include "components.h"

Component::Component(int *pin_numbers, int *states, int number_of_pins) : pin_numbers(new int[number_of_pins]), modes(new int[number_of_pins]), number_of_pins(number_of_pins) {
    for(int i = 0; i < number_of_pins; i++) {
      pinMode(pin_numbers[i], modes[i]);
    }
}