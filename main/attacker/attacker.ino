#include "./components/motor/motor.h"
#include "./components/IR/IRSensor.h"

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

  if (dir == "north") {
    m.moveNorth(MOVE_SPEED);
  }
  else if (dir == "north-east") {
    m.moveNorthEast(MOVE_SPEED);
  }
  else if (dir == "north-west") {
    m.moveNorthWest(MOVE_SPEED);
  }
  else if (dir == "east") {
    m.moveEast(MOVE_SPEED);
  }
  else if (dir == "west") {
    m.moveWest(MOVE_SPEED);
  }
  else if (dir == "south-east") {
    m.moveSouthEast(MOVE_SPEED);
  }
  else if (dir == "south-west") {
    m.moveSouthWest(MOVE_SPEED);
  }
  else if (dir == "south") {
    m.moveSouth(MOVE_SPEED);
  }
  else {
    // Serial.println("Direction not found");
    m.brake();
    //implement search pattern
  }

  // m.test();

  // if(isBallInFront()){
  //   m.moveNorth();
  //   Serial.println("in front");
  // } else {
  //   m.brake();
  //   Serial.println("not");
  // }
}