#include <Adafruit_BNO055.h>

const unsigned int COMPASS_BUFF = 15;  // +/- 15

const unsigned int COMPASS_BUFF = 7;

struct Motor {
  unsigned int s_pin;
  unsigned int dir_pin;
  unsigned int br_pin;

  Motor(unsigned int pin_, unsigned int dir_pin_, unsigned int br_pin_)
      : s_pin(pin_), dir_pin(dir_pin_), br_pin(br_pin_) {
      pinMode(s_pin, OUTPUT);
      pinMode(dir_pin, OUTPUT);
      pinMode(br_pin, OUTPUT);
    }

  void spin(int s) {
    digitalWrite(br_pin, HIGH);
    if (s < 0) {
      analogWrite(s_pin, s * -1);
      digitalWrite(dir_pin, HIGH);
    } else {
      analogWrite(s_pin, s);
      digitalWrite(dir_pin, LOW);
    }
  }

  void brake() {
    analogWrite(s_pin, 0);
    digitalWrite(br_pin, LOW);
  }
};

struct Compass {
  Adafruit_BNO055 bno;

  void initialize() {
    bno = Adafruit_BNO055(55);
    if (!bno.begin()) {
      Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR! 🤓🤓🤓");
      while (1);
    }
    bno.setExtCrystalUse(true);
  }

  float readCompass() {
    sensors_event_t event;
    bno.getEvent(&event);

    int angle = event.orientation.x;

    if (angle > 180) {
      return angle - 360;
    }
    return angle;
  }

  boolean isBetween(int lower, int upper, int x) {
    return lower < x && x < upper;
  }

  boolean isNorth() {
    return isBetween(COMPASS_BUFF * -1, COMPASS_BUFF, readCompass());
  }
};

struct Movement {
  private:
    Motor motor_0{1, 3, 2};
    Motor motor_1{7, 9, 8};
    Motor motor_2{28, 35, 29};
    Motor motor_3{4, 6, 5};
  public:
    
    Motor motors[4] = { motor_0, motor_1, motor_2, motor_3 };

    void rotate(int speed) {
      for (int i = 0; i < 4; i++) {
        motors[i].spin(speed);
      }
    }

    void brake() {
      for (int i = 0; i < 4; i++) {
        motors[i].brake();
      }
    }

    void moveNorth(unsigned int speed/*, Compass &compass*/) {
      // pointNorth(210, compass);

      motors[0].spin(speed);
      motors[1].spin(-speed);
      motors[2].spin(-speed);
      motors[3].spin(speed);
    }

    void moveSouth(unsigned int speed/*, Compass &compass*/) {
      // pointNorth(210, compass);

      motors[0].spin(-speed);
      motors[1].spin(speed);
      motors[2].spin(speed);
      motors[3].spin(-speed);
    }

};











void setup() {
  Serial.begin(9600);

  // compass.initialize();
}

void loop() {
  Movement m;

  m.move_north(50);
  delay(1000);
}


void point_north(int speed) {
  Movement m;
  if (is_between(COMPASS_BUFF*-1, COMPASS_BUFF, readCompass())){
    m.brake();
  } else if (readCompass() > 0){
    m.rotate(210);
  } else {
    m.rotate(-210);
  }
}


boolean is_between(int lower, int upper, int x){
  if (lower < x && x < upper){
    return true;
  }
  return false;
}



void initialize() {
  bno = Adafruit_BNO055(55);

  /* Initialise the sensor */
  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR! 🤓🤓🤓");
    while (1)
      ;
  }


  bno.setExtCrystalUse(true);
}

float readCompass() {
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  int angle = event.orientation.x;

  if (angle > 180){
    return angle - 360;
  }
  return angle;
}
