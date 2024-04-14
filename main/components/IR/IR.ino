int pins[] = {41, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 };

template <typename T, size_t N>
size_t arrayLength(const T (&)[N]);

void setup() {
  Serial.begin(9600);
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    pinMode(pins[i], INPUT);
  }
}

void loop() {
  int* readings = getReadingsArr();
  for(int i = 0; i<15; i++) {
    Serial.println(readings[i]);
  }

}

bool isBallInFront() {
  int* readings = getReadingsArr();
  return (readings[14] == 1) && (readings[13] == 1);
}

int* getReadingsArr() {
  int* pinReadings = new int[15];
  double reading;
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    reading = pulseIn(pins[i], HIGH, 500);
    if (reading > 0.05){
      pinReadings[i] = 1;
    } else {
      pinReadings[i] = 0;
    }
  }
  return pinReadings;
}

template <typename T, size_t N>
size_t arrayLength(const T (&)[N]) {
  return N;
}

void printIntArr(int* arr) {
  Serial.print("[ ");
  for(int i = 0; i < 15; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("]");
}

