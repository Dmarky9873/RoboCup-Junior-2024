#include "../components.h"

class Motor : private Component {
public:
  Motor(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name);
  void ControlMotor(int speed, Motor motor);
};

Motor::Motor(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name){

};

Motor::ControlMotor(int speed, Motor motor){
  
};