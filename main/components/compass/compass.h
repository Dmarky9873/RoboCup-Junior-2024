#include "../components.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Compass : public Component {

  public:
    float readCompass();
    void init();

    //constructor 
    Compass(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name) : 
    Component(pin_numbers, modes, number_of_pins, component_name) {
      
    };

  private:
    Adafruit_BNO055 bno;
  };

void Compass::init() {
  setUp();
  bno = Adafruit_BNO055(55);
  Serial.println("Orientation Sensor Test");
  Serial.println("");

  /* Initialise the sensor */
  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR! 🤓🤓🤓");
    while (1);
  }


  bno.setExtCrystalUse(true);
}

float Compass::readCompass() {
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  return event.orientation.x;
}