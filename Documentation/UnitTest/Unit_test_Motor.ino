enum RobotState {
  FOLLOW_LINE,
  INSPECT_OBSTACLE,
  AVOID_OBSTACLE
};

class Robot {
private:
  uint8_t ENA, ENB, IN1, IN2, IN3, IN4;

public:
  Robot(uint8_t ENA, uint8_t ENB,
        uint8_t IN1, uint8_t IN2,
        uint8_t IN3, uint8_t IN4,
        uint8_t, uint8_t, uint8_t,
        uint8_t, uint8_t,
        uint8_t, uint8_t, uint8_t,
        uint8_t, uint8_t,
        RobotState, uint8_t, uint8_t)
    : ENA(ENA), ENB(ENB), IN1(IN1), IN2(IN2), IN3(IN3), IN4(IN4) {}

  void init() {
    pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  }

  void motorLeft(short speed) {
    if (speed > 0) {
      digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
    } else if (speed < 0) {
      digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
    } else {
      digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    }
    analogWrite(ENA, abs(speed));
  }

  void motorRight(short speed) {
    if (speed > 0) {
      digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
    } else if (speed < 0) {
      digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
    } else {
      digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    }
    analogWrite(ENB, abs(speed));
  }
};

// ===== PIN DEFINITIONS =====
#define ENA 5
#define ENB 10
#define IN1 13
#define IN2 12
#define IN3 9
#define IN4 8

// ===== CREATE ROBOT OBJECT WITH VALUES FOR UNUSED PINS =====
Robot testBot(
  ENA, ENB,
  IN1, IN2, IN3, IN4,
  0, 0, 0, 0, 0,
  0, 0, 0, 0, 0,
  FOLLOW_LINE, 0, 0
);

// ===== SETUP FUNCTION =====
void setup() {
  Serial.begin(9600);
  testBot.init();

  Serial.println("MOTOR UNIT TEST START");

  // Left Motor Test
  Serial.println("Left Motor: FORWARD");
  testBot.motorLeft(80);
  delay(1000);

  Serial.println("Left Motor: REVERSE");
  testBot.motorLeft(-80);
  delay(1000);

  Serial.println("Left Motor: STOP");
  testBot.motorLeft(0);
  delay(1000);

  // Right Motor Test
  Serial.println("Right Motor: FORWARD");
  testBot.motorRight(80);
  delay(1000);

  Serial.println("Right Motor: REVERSE");
  testBot.motorRight(-80);
  delay(1000);

  Serial.println("Right Motor: STOP");
  testBot.motorRight(0);
  delay(1000);

  Serial.println("MOTOR UNIT TEST COMPLETE");
}

void loop() {

}
