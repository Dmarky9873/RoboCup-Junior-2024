#include "./components/motor/motor.h"
#include "./components/IR/IRSensor.h"

void setup() {
  Serial.begin(9600);
  initIR();
}

Movement m;

void loop() {
  m.pointNorth(200, Compass &compass)

  // m.moveNorth(150);
  // delay(750);
  // m.brake();

  // m.moveEast(150);
  // delay(750);
  // m.brake();

  // m.moveSouth(150);
  // delay(750);
  // m.brake();

  // m.moveWest(150);
  // delay(750);
  // m.brake();

  // if(isBallInFront()){
  //   m.moveNorth();
  //   Serial.println("in front");
  // } else {
  //   m.brake();
  //   Serial.println("not");
  // }
}