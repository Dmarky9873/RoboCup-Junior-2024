#include "./components/motor/motor.h"
#include "./components/IR/IRSensor.h"

void setup() {
  Serial.begin(9600);
  initIR();
}

Movement m;

void loop() {
  if(isBallInFront()){
    m.moveNorth();
    Serial.println("in front");
  } else {
    m.brake();
    Serial.println("not");
  }
}