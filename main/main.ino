#include "./components/components.h"
#include "./components/compass/compass.h"

int pins[] = { 1, 2 };
uint8_t modes[] = { OUTPUT, OUTPUT };

Compass compass(pins, modes, 2, "compass");

void setup() {
  Serial.begin(9600);
  // Serial.println("Beginning initialization...");
}

void loop() {
  Serial.println(compass.readCompass());
}
