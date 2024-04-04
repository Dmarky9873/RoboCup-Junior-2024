#include <Adafruit_BNO055.h>

const unsigned int COMPASS_BUFF = 15; 

Adafruit_BNO055 bno;

struct Motor {
  private:
    unsigned int s_pin;
    unsigned int dir_pin;
    unsigned int br_pin;

  public:

    Motor(unsigned int pin_, unsigned int dir_pin_, unsigned int br_pin_)
      : s_pin(pin_), dir_pin(dir_pin_), br_pin(br_pin_) {
      pinMode(s_pin, OUTPUT);
      pinMode(dir_pin, OUTPUT);
      pinMode(br_pin, OUTPUT);
    }

    // When facing the wheel, positive int = clockwise (left) and negative int = counterclockwise (right).
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

struct Movement {
  private:
    // Motor motor_0(3 /* Speed pin */, 4 /* Direction pin */, 2 /* Brake pin */);
    // Motor motor_1(6 /* Speed pin */, 7 /* Direction pin */, 5 /* Brake pin */);
    // Motor motor_2(9 /* Speed pin */, 10 /* Direction pin */, 8 /* Brake pin */);
    // Motor motor_3(12 /* Speed pin */, 13 /* Direction pin */, 11 /* Brake pin */);
    Motor motor_0{3, 4, 2};
    Motor motor_1{6, 7, 5};
    Motor motor_2{9, 10, 8};
    Motor motor_3{12, 13, 11};

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

    void move_north(unsigned int speed) {
      motors[0].spin(-speed);
      motors[1].spin(-speed);
      motors[2].spin(speed);
      motors[3].spin(speed);
    }

    void move_south(unsigned int speed) {
      motors[0].spin(speed);
      motors[1].spin(speed);
      motors[2].spin(-speed);
      motors[3].spin(-speed);
    }

};

//Moved movement out of loop function
Movement m;

void setup() {
  Serial.begin(9600);

  initialize();
}

void loop() {
  if(isNorth()){
    m.move_north(150);
  } else{
    point_north(230);
  }
}


void point_north(int baseSpeed) {
  Movement m;
  int speed = 0;
  while (!is_between(COMPASS_BUFF*-1, COMPASS_BUFF, readCompass())){
    speed = (int)(baseSpeed - abs(abs(readCompass()) - COMPASS_BUFF) * 0.3);
    Serial.println(readCompass());
    Serial.println(speed);
    if (readCompass() > 0) {
      m.rotate(speed);
    } 
    else {
      m.rotate(-speed);
    }
  }

  m.brake();
  Serial.println("end");
}


boolean is_between(int lower, int upper, int x){
  return lower < x && x < upper;
}

boolean isNorth(){
  return is_between(COMPASS_BUFF*-1, COMPASS_BUFF, readCompass());
}

void initialize() {
  bno = Adafruit_BNO055(55);

  /* Initialise the sensor */
  if (!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR! 🤓🤓🤓");
    while (1);
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
