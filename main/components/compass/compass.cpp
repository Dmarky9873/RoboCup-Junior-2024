#include "compass.h"

Compass::Compass(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name) 
: Component(pin_numbers, modes, number_of_pins, component_name) {
  // bno = Adafruit_BNO055(55);
  // Serial.begin(9600);
  // Serial.println("Orientation Sensor Test");
  // Serial.println("");

  // /* Initialise the sensor */
  // if (!bno.begin()) {
  //   /* There was a problem detecting the BNO055 ... check your connections */
  //   Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR! 🤓🤓🤓");
  //   while(1);
  // }
  // else {
  //   Serial.println("worked");
  // }

  // delay(1000);

  // bno.setExtCrystalUse(true);
  Serial.println("works");
}