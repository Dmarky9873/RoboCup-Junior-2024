#include "./components/components.h"
#include "./components/motor/motor.h"
#include "./components/compass/compass.h"

int pins[] = { 1, 2 };
uint8_t modes[] = { OUTPUT, OUTPUT };

Compass compass(pins, modes, 2, "compass");

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  Serial.print("Compass Reading: ");
  Serial.println(compass.readCompass("hi"));
}

