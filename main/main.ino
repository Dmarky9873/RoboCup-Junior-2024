#include "./components/components.h"
#include "./components/motor/motor.h"
#include "./components/compass/compass.h"
#include "./components/shift-register/shift-register.h"

// int pins[] = { 1, 2 };
// uint8_t modes[] = { OUTPUT, OUTPUT };

// Compass compass(pins, modes, 2, "compass");

void setup() {
  Serial.begin(9600);

  //initialize compass
  // compass.init(); //initializes bno sensor
  pinMode(A0, INPUT);
}

void loop() {
  // Serial.print("Compass Reading: ");
  // Serial.println(compass.readCompass());
  Serial.println(analogRead(A0));
}