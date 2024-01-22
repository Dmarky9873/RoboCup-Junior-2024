int ioSelect = 2;
int clockPulse = 3;
int dataOut = 4;

int CHIPSIZE = 8;

void setup() {
  Serial.begin(9600);

  pinMode(ioSelect, OUTPUT);
  pinMode(clockPulse, OUTPUT);
  pinMode(dataOut, INPUT);


}

void loop() {
  int* vals = readChip();
}

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
void clkPulse() {
  digitalWrite(clockPulse, LOW);
  digitalWrite(clockPulse, HIGH);
}

/**
  * Shifts in parallel data to the chip.
  */
void shiftIN() {
  ioType(0);
  clkPulse();
  ioType(1);
}

/**
  * Reads all 8 bits of the serial output of the chip.
  * 
  * @return integer array of size `CHIPSIZE` where each int is a respective chip bit.
  */
int* readChip() {
  shiftIN();
  int* vals = new int[CHIPSIZE];

  for(int j = 0; j < CHIPSIZE; j++) {
    int val = digitalRead(dataOut);

    vals[j] = val;

    clkPulse();
  }

  return vals;
}
