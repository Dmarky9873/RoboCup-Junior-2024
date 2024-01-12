<<<<<<< Updated upstream
#include "./components/components.h"
#include "./components/compass/compass.h"

int pins[] = { 1, 2 };
uint8_t modes[] = { OUTPUT, OUTPUT };

Compass compass(pins, modes, 2, "compass");
=======
// #include "./components/components.h"
#include "./components/motor/motor.h"
>>>>>>> Stashed changes

void setup() {
  Serial.begin(9600);
  // Serial.println("Beginning initialization...");
<<<<<<< Updated upstream
=======

  // int pins[] = { 1, 2 };
  // uint8_t modes[] = { OUTPUT, OUTPUT };

  
  Motor::ControlMotor(int speed, Motor motor){
    
  }

>>>>>>> Stashed changes
}

void loop() {
  Serial.println(compass.readCompass());
}
