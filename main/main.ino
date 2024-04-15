#include "./components/motor/motor.h"
#include "./components/IR/IRSensor.h"

Movement m;

void setup() {
  Serial.begin(9600);
  initIR();
  m.initMotor();
}

void loop() {
  

  // m.test();

  // if(isBallInFront()){
  //   m.moveNorth();
  //   Serial.println("in front");
  // } else {
  //   m.brake();
  //   Serial.println("not");
  // }
}