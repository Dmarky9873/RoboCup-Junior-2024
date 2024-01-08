#ifndef COMPONENT_H
#define COMPONENT_H

#include <string.h>
#define UNKNOWN_PIN 0xFF


class Component
{
public:
    Component(int pin_numbers[], int modes[], int number_of_pins, String component_name);
    uint8_t getPinMode(uint8_t pin);

private:
    const int num_pins;
    const String name;
    const int *pin_nums;
    const int *mds;
};

#endif