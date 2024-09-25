int pins[] = { 41, 14, 10, 16, 17, 18, 19, 20, 21, 22, 23, 26, 27, 40 };
int NUM_IR_PINS = 14;

template <typename T, size_t N>
size_t arrayLength(const T (&)[N]);
int* getReadingsArr();

void initIR() {
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    pinMode(pins[i], INPUT);
  }
}

// get filtered readings (1s and 0s)
int* getReadingsArr() {
  int* pinReadings = new int[NUM_IR_PINS];
  double reading;
  for (unsigned int i = 0; i < arrayLength(pins); i++) {
    reading = pulseIn(pins[i], HIGH, 500);
    // reading filtering
    if (reading > 0.05){
      pinReadings[i] = 1;
    } else {
      pinReadings[i] = 0;
    }
  }
  return pinReadings;
}

// get analog pin readings
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

// printing filtered readings array
void printReadingsArr() {
  int* arr = getReadingsArr();
  Serial.print("[ ");
  for(int i = 0; i < NUM_IR_PINS; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("]");
}

// print analog readings array
void printPWsArr() {
  double* arr = getPWsArr();
  Serial.print("[ ");
  for(int i = 0; i < NUM_IR_PINS; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("]");
}

// detect readings from front IRs
int frontDetection() {
  int* arr = getReadingsArr();
  int count = 0;
  // loop through front IRs
  for(int i = 0; i < 3; i++) {
    if (arr[i] == 1) {
      count++;
    }
  }
  
  return count;
}

// detect readings from left IRs
int leftDetection() {
  int* arr = getReadingsArr();
  int count = 0;
  // loop through left IRs
  for(int i = 11; i <= 13; i++) {
    if (arr[i] == 1) {
      count++;
    }
  }
  
  return count;
}

// detect readings from right IRs
int rightDetection() {
  int* arr = getReadingsArr();
  int count = 0;
  // loop through right IRs
  for(int i = 4; i <= 7; i++) {
    if (arr[i] == 1) {
      count++;
    }
  }
  
  return count;
}

// detect readings from south IRs
int southDetection() {
  int* arr = getReadingsArr();
  int count = 0;
  // loop through south IRs
  for(int i = 8; i <= 10; i++) {
    if (arr[i] == 1) {
      count++;
    }
  }
  
  return count;
}

// if the robot sees ANYTHING
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
  printReadingsArr();

  delay(10); //combat motor overheating (the larger the delay, the less accurate)

  //detect indirectly south
  if (isDetected() && frontDetection() < 1 && southDetection() == 1) {
    return "south";
  }
  
  //detect direct south
  else if (frontDetection() < 1 && southDetection() >= 2) {
    return "south-east";
  }

  //detect far/close diagonal
  else if (isDetected() && readings[3] == 0 && readings[0] == 1 && leftDetection() < 2) {
    return "north-west";
  }

  else if (isDetected() && readings[0] == 0 && readings[3] == 1 && rightDetection() < 2) {
    return "north-east";
  }

  else if (readings[0] == 0 && readings[3] == 1 && rightDetection() >= 1) {
    return "east";
  }

  //detect north (far and close)
  else if ((readings[0] == 1 || readings[1] == 1) && (readings[2] == 1 || readings[3] == 1)) {
    return "north";
  }

  else if (rightDetection() >= 2) {
    return "south-east";
  }

  else if (readings[3] == 0 && readings[0] == 1 && leftDetection() >= 2) {
    return "west";
  }

  else if (leftDetection() >= 1) {
    return "south-west";
  }

  return "none";
}

