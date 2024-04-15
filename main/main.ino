#include "./components/motor/motor.h"
#include "./components/IR/IRSensor.h"

const int MOVE_SPEED = 150;

Movement m;

void setup() {
  Serial.begin(9600);
  initIR();
  m.initMotor();
}

void loop() {

  String dir = getDirectionToMove();

  if (dir == "north") {
    m.moveNorth(MOVE_SPEED);
  }
  else if (dir == "south-east") {
    m.moveSouthEast(MOVE_SPEED);
  }
  else if (dir == "south-west") {
    m.moveSouthWest(MOVE_SPEED);
  }
  else {
    Serial.println("Direction not found");
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