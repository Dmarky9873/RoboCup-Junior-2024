#include "../components/motor/motor.h"
#include "../components/IR/IRSensor.h"

const int MOVE_SPEED = 125;

Movement m;

void setup() {
  Serial.begin(9600);
  initIR();
  m.initMotor();
}

void loop() {
  String dir = getDirectionToMove();
  Serial.println(dir);

  if (dir == "east" || dir == "south-east") {
    m.moveEast(MOVE_SPEED);
  }
  else if (dir == "west" || dir == "south-west") {
    m.moveWest(MOVE_SPEED);
  }
  else {
    // Serial.println("Direction not found");
    m.brake();
    //implement search pattern
  }