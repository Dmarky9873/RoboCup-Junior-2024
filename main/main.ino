#include "./components/components.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Beginning initialization...");

  int pins[] = {1, 2};
  uint8_t modes[] = {OUTPUT, OUTPUT};

  Component x(pins, modes, 2, "motor");
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
