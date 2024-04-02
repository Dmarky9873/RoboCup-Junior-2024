#include "Arduino.h"
// #include <Adafruit_BNO055.h>

// class Compass : public Component {

//   public:
//     // TODO: Comment these
//     float readCompass();
//     void init();

//     // TODO: Comment this
//     Compass(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name) : 
//     Component(pin_numbers, modes, number_of_pins, component_name) {
      
//     };

//   private:
//     Adafruit_BNO055 bno; // Instance of the Adafruit_BNO055 class (the compass library). 
//   };


// // TODO: Comment this
// void Compass::init() {
//   setUp();
//   bno = Adafruit_BNO055(55);
//   Serial.println("Orientation Sensor Test");
//   Serial.println("");

//   /* Initialise the sensor */
//   if (!bno.begin()) {
//     /* There was a problem detecting the BNO055 ... check your connections */
//     Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR! 🤓🤓🤓");
//     while (1);
//   }


//   bno.setExtCrystalUse(true);
// }

// float Compass::readCompass() {
//   /* Get a new sensor event */
//   sensors_event_t event;
//   bno.getEvent(&event);

//   return event.orientation.x;
// }

#include <Adafruit_BNO055.h>


class Compass {

  public:
    Compass(){
      bno = Adafruit_BNO055(55);
      /* Initialise the sensor */
      // if (!bno.begin() && verbose) {
      //   /* There was a problem detecting the BNO055 ... check your connections */
      //   Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR! 🤓🤓🤓");
      //   while (1);
      // }

      bno.setExtCrystalUse(true);

    }
    
    float readCompass(){
      /* Get a new sensor event */
      sensors_event_t event;
      bno.getEvent(&event);

      return event.orientation.x;
    }

  private:
    Adafruit_BNO055 bno;
    const unsigned int COMPASS_BUFF = 15;
};
