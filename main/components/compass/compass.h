#include "../components.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Compass : private Component {

public:
  float readCompass(void);
  void init();

  //constructor
  Compass(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name)
  : Component(pin_numbers, modes, number_of_pins, component_name)
  {
    init();
  }

private:
  Adafruit_BNO055 bno;
};

void Compass::init() {
  bno = Adafruit_BNO055(55);
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test");
  Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR! 🤓🤓🤓");
    while (1);
  }

  delay(1000);

  bno.setExtCrystalUse(true);
}

float Compass::readCompass(void) {
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
  // Serial.print("X: ");
  // Serial.print(event.orientation.x, 4);
  // Serial.print("\tY: ");
  // Serial.print(event.orientation.y, 4);
  // Serial.print("\tZ: ");
  // Serial.print(event.orientation.z, 4);
  // Serial.println("");
  
  delay(100);

  return event.orientation.z;
}