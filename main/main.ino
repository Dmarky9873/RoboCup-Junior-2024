#include "./components/components.h"
// #include "./components/motor/motor.h"
#include "./components/compass/compass.h"
#include "./components/shift-register/shift-register.h"

/*
 * Uncomment lines marked with "// *" to test compass indivitually
 * Uncomment lines marked with "// **" to test shift registers/IR sensors individually
 */


// int pins[] = { 1, 2 };// *
// uint8_t modes[] = { OUTPUT, OUTPUT };// *



// Compass compass(pins, modes, 2, "compass");// *


/**
  * Teensy Pins for Shift Register:
  * clockPulse: pin 33
  * ioSelect: pin 34
  * dataPin: pin 32
  */
Shift_Register shiftRegister(34 /* ioSelect */, 33 /* clockPulse */, 32 /* dataPin */); // **

void setup() {
  Serial.begin(9600);


  // compass.init(); // *
}

int n = 0;

void loop() {
  // Serial.print("Compass Reading: ");// *
  // Serial.println(compass.readCompass());// *

  Serial.print("Reading number ");
  Serial.println(n);
  shiftRegister.printChips(250);
  n++;
}