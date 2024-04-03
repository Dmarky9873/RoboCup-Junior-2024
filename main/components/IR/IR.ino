int ioSelect = 2;
int clockPulse = 3;
int dataPin = 4;
int NUM_CHIPS = 3;

int CHIPSIZE = 8;

void setup() {
  Serial.begin(9600);

  pinMode(ioSelect, OUTPUT);
  pinMode(clockPulse, OUTPUT);
  pinMode(dataPin, INPUT);
}

void loop() {
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
  delay(1000);
}

/**
  * Sets the chip to accept parallel input or serial input.
  *
  * @param input_type type of input to set chip to. 0 for parallel input, and 1 for serial input.
  */
void ioType(int io_type) {
  digitalWrite(ioSelect, io_type);
}

/**
  * Pulses the clock.
  *
  * Writes the clock pulse to low, then high once, in rapid succession.
  */
void clkPulse() {
  digitalWrite(clockPulse, LOW);
  digitalWrite(clockPulse, HIGH);
}

/**
  * Shifts in parallel data to the shift register.
  */
void chipParallelIn() {
  ioType(0);
  clkPulse();
  ioType(1);
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
