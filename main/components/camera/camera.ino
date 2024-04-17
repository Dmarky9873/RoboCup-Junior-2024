#include "camera.h"

Camera cam;

void setup(){
  Serial.begin(9600);
}

void loop(){
  int direction = cam.getDistanceToCenter();

  Serial.println(direction);

  delay(100);
}