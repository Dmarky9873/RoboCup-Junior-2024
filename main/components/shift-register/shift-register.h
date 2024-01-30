#include "../components.h"

class Shift_Register : public Component {

  public: 
  
    /**
    * Reads the values stored in a set of daisy-chained shift registers.
    * 
    * @param numOfChips the number of chips daisy-chained.
    *
    * @param sizeOfChips the size of the chips.
    *
    * @returns a 2D integer array with dimentions [`numOfChips` x `sizeOfChips`] where each value is a value once stored on the corresponding chips address.
    */
    int** readChips();

    /**
    * Constructor, sets private variables to params.
    *
    * @param `pin_numbers[]` integer array of pin-numbers that relate to an instance of the component class.
    * @param `modes[]` integer array where modes[n] is the mode for pin_numbers[n].
    * @param `number_of_pins` number of elements in the modes[] and pin_numbers[] arrays.
    * @param `component_name` name of this component as a string.
    */
    Shift_Register(int pin_numbers[], uint8_t modes[], int number_of_pins, String component_name) : 
    Component(pin_numbers, modes, number_of_pins, component_name){

  };

  private:
    int CHIPSIZE; // Number of bits of data that the chip can manage.

    /**
      * Sets the chip to accept parallel input or produce serial output.
      *
      * @param input_type type of input to set chip to. 0 for parallel input 1 for serial.
      */
    void ioType(int io_type);

    /**
      * Pulses the clock.
      *
      * Writes the clock pulse to low, then high once, in rapid succession.
      */
    void clkPulse();

    /**
      * Shifts in parallel data to the chip.
      */
    void shiftIN();

    // VARIABLES

};


void ioType(int io_type) {
  digitalWrite(ioSelect, io_type);
}

void clkPulse() {
  digitalWrite(clockPulse, LOW);
  digitalWrite(clockPulse, HIGH);
}

void shiftIN() {
  ioType(0);
  clkPulse();
  ioType(1);
}

int* readChip() {
  shiftIN(); // Shifts in the parallel data.

  int* vals = new int[CHIPSIZE]; // Creates new integer array of size `CHIPSIZE` in which we will store the values of the shift register.

  for(int j = 0; j < CHIPSIZE; j++) {
    int val = digitalRead(dataOut); // Reads the current register of the chip.

    vals[j] = val; // Stores the value inside the array.

    clkPulse(); // Pulses the clock to shift the register by one.
  }

  return vals;
}