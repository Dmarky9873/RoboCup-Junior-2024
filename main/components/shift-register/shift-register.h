class Shift_Register {

  public: 
    /**
      * Constructor for the `Shift_Register` class.
      *
      * @param ioSelect_ the pin which will tell the shift register whether to accept input or produce output.
      *
      * @param clockPulse_ the clock pin.
      *
      * @param dataPin_ the data-bus pin.
      *
      * @returns void
      */
    Shift_Register(int ioSelect_, int clockPulse_, int dataPin_) {
      ioSelect = ioSelect_;
      clockPulse = clockPulse_;
      dataPin = dataPin_;
      Serial.println("Shift Register initialized.");
    }

    /**
      * Reads the values stored in a set of daisy-chained shift registers.
      * 
      * @param numOfChips the number of chips daisy-chained.
      *
      * @param sizeOfChips the size of the chips.
      *
      * @returns a 2D integer array with dimentions [`numOfChips` x `sizeOfChips`] where each value is a value once stored on the corresponding chips address.
      */
    int** readChips(int numOfChips, int sizeOfChips) {
      int** chipValues = new int*[numOfChips];
      for (int i = 0; i < numOfChips; ++i) {
        chipValues[i] = new int[sizeOfChips];
      }
      
      chipParallelIn();
      for (int chip = 0; chip < numOfChips; chip++) {
        chipValues[chip] = readChip(sizeOfChips);
      }

      return chipValues;
    }
    /**
      * Nicely formats and prints the 2D array read in the daisy-chained shift registers.
      * 
      * @param miliSecondsDelay the number of miliseconds to delay in between print statements (recommended to be >= 10)
      */
    void printChips(int secondsDelay){
      int** chipValues = readChips(NUM_CHIPS, CHIPSIZE);
      for (int chip = 0; chip < NUM_CHIPS; chip++) {
        Serial.print("Chip #");
        Serial.print(chip + 1);
        Serial.print(": [ ");
        for (int addr = 0; addr < CHIPSIZE; addr++) {
          Serial.print(chipValues[chip][addr]);
          Serial.print(" ");
        }
        Serial.print("]");
        Serial.println();
      }
      delay(miliSecondsDelay*1000);
    }

  private:
    /**
      * Sets the chip to accept parallel input or produce serial output.
      *
      * @param input_type type of input to set chip to. 0 for parallel input 1 for serial.
      */
    void ioType(int io_type) {
      digitalWrite(ioSelect, io_type);
    }

    /**
      * Pulses the clock.
      *
      * Writes the clock pulse to low, then high once, in rapid succession.
      */
    void clkPulse(){
      digitalWrite(clockPulse, LOW);
      digitalWrite(clockPulse, HIGH);
    }

    /**
      * Reads all 8 bits of the serial output of a shift register.
      *
      * @param sizeOfChips the size of the chips being read
      * 
      * @return integer array of size `CHIPSIZE` where each int is a respective chip bit.
      */
    int* readChip(int sizeOfChips) {
      int* vals = new int[sizeOfChips];

      for(int j = 0; j < sizeOfChips; j++) {
        int val = digitalRead(dataPin);

        vals[j] = val;

        clkPulse();
      }

      return vals;
    }

    /**
      * Shifts in parallel data to the shift register.
      */
    void chipParallelIn() {
      ioType(0);
      clkPulse();
      ioType(1);
    }

    // VARIABLES

    int ioSelect;
    int clockPulse;
    int dataPin;

    const int NUM_CHIPS = 2;
    const int CHIPSIZE = 8;

};