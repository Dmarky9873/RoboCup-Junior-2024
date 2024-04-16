int pins[] = { 41, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 26, 27, 40 };
int NUM_IR_PINS = 14;

template <typename T, size_t N>
size_t arrayLength(const T (&)[N]);
int* getReadingsArr();

void initIR() {
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    pinMode(pins[i], INPUT);
  }
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

int frontDetection() {
  int* arr = getReadingsArr();
  int count = 0;
  for(int i = 0; i < 4; i++) {
    if (arr[i] == 1) {
      count++;
    }
  }
  
  return count;
}

int leftDetection() {
  int* arr = getReadingsArr();
  int count = 0;
  for(int i = 9; i <= 12; i++) {
    if (arr[i] == 1) {
      count++;
    }
  }
  
  return count;
}

int rightDetection() {
  int* arr = getReadingsArr();
  int count = 0;
  for(int i = 4; i <= 7; i++) {
    if (arr[i] == 1) {
      count++;
    }
  }
  
  return count;
}

bool isDetected() {
  int* arr = getReadingsArr();
  for(int i = 0; i < NUM_IR_PINS; i++) {
    if (arr[i] == 1) {
      return true;
    }
  }

  return false;
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
String getDirectionToMove() {
  int* readings = getReadingsArr();
  // printReadingsArr();

  delay(5); //combat motor overheating (the larger the delay, the less accurate)

  //detect north
  if ((readings[0] == 1 && readings[3] == 1) && (readings[1] == 1 || readings[2] == 1)) {
    return "north";
  }

  //detect backwards motion
  else if (isDetected() && frontDetection() < 1) {
    return "south";
  }

  //detect ~150 degrees direction
  else if (rightDetection() >= 1) {
    return "south-east";
  }
  else if (leftDetection() >= 1) {
    return "south-west";
  }

  //detect far ~150 degree directions
  else if (isDetected() && readings[3] == 0 && readings[0] == 1 && leftDetection() < 1) {
    return "west";
  }

  else if (isDetected() && readings[0] == 0 && readings[3] == 1 && rightDetection() < 1) {
    return "east";
  }

  //detect if far and north (front-sensors should detect at least one)
  else if (frontDetection() > 0) {
    return "north";
  }

  return "none";

  // String location = "No ball detected";
  // int* readings = getReadingsArr();

  // printReadingsArr();

  // if (readings[1] && readings[2]){
  //   location = "north";
  // } 
  // else if (
  //   (readings[5] && readings[6]) || 
  //   (readings[9] && readings[10] && readings[8]) || 
  //   (readings[9] && readings[8]) || 
  //   (readings[7] && readings[8]) ||
  //   (readings[3] && readings[4]) || (readings[2] && readings[2] && readings[3])
  // ) {
  //   location = "south-east";
  // }
  // else if (
  //   (readings[11] && readings[10]) || 
  //   (readings[11] || readings[12] || readings[13])
  // ){
  //   location = "south-west";
  // }

  // delay(5);

  // return location;
}

