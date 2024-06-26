int pins[] = { 41, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 26, 27, 40 };
int NUM_IR_PINS = 14;

template <typename T, size_t N>
size_t arrayLength(const T (&)[N]);

void setup() {
  Serial.begin(9600);
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    pinMode(pins[i], INPUT);
  }
}

void loop() {
  // printPWsArr();
  // printReadingsArr();
  printReadingsArr();
  delay(50);
}

bool isBallInFront() {
  int* readings = getReadingsArr();
  return (readings[14] == 1) && (readings[13] == 1);
}

int* getReadingsArr() {
  int* pinReadings = new int[NUM_IR_PINS];
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

double* getPWsArr() {
  double* pinReadings = new double[NUM_IR_PINS];
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    pinReadings[i] = pulseIn(pins[i], HIGH, 500);
  }
  return pinReadings;
}

template <typename T, size_t N>
size_t arrayLength(const T (&)[N]) {
  return N;
}

void printReadingsArr() {
  int* arr = getReadingsArr();
  Serial.print("[ ");
  for(int i = 0; i < NUM_IR_PINS; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("]");
}

void printPWsArr() {
  double* arr = getPWsArr();
  Serial.print("[ ");
  for(int i = 0; i < NUM_IR_PINS; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("]");
}
/*
 *  north:      Directly in front; move forward.
 *  north-east: Front and to the right of the robot; move east/right.
 *  south-east: Back and to the right of the robot; move south-east/back-right.
 *  south:      Directly behind the robot; move south-east/back-right (this is up to 
                interpretation - the robot could move south-west and it would have the same effect)
 *  south-west: Back and to the left of the robot; move south-west/back-left.
 *  north-west: Front and to the left of the robot; move west/left.
 */
// String getDirectionToMove() {
//   String location = "No ball detected";
//   int* readings = getReadingsArr();

//   if (readings[1] && readings[2]){
//     location = "north";
//   } 
//   else if (
//     (readings[5] && readings[6]) || 
//     (readings[9] && readings[10] && readings[8]) || 
//     (readings[9] && readings[8]) || 
//     (readings[7] && readings[8]) ||
//     (readings[3] && readings[4]) || (readings[2] && readings[2] && readings[3])
//   ) {
//     location = "south-east";
//   }
//   else if (
//     (readings[11] && readings[10]) || 
//     (readings[11] || readings[12] || readings[13])
//   ){
//     location = "south-west";
//   }

//   return location;
// }

