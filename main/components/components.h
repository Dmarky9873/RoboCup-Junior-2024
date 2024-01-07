#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
    Component(int *pin_numbers, int *modes, int number_of_pins);

private:
    const int *pin_numbers;
    const int *modes;
    const int number_of_pins;
};

#endif