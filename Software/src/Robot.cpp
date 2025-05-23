#include "Robot.h"

Robot::Robot(uint8_t ENA,
             uint8_t ENB,
             uint8_t IN1,
             uint8_t IN2,
             uint8_t IN3,
             uint8_t IN4,
             uint8_t IR_LEFT,
             uint8_t IR_RIGHT,
             uint8_t SERVO,
             uint8_t TRIGGER_PIN,
             uint8_t ECHO_PIN,
             uint8_t S0,
             uint8_t S1,
             uint8_t S2,
             uint8_t S3,
             uint8_t sensorOut,
             RobotState initState,
             uint8_t k,
             uint8_t distance)
  : ENA(ENA), ENB(ENB), IN1(IN1), IN2(IN2),
    IN3(IN3), IN4(IN4), IR_LEFT(IR_LEFT), IR_RIGHT(IR_RIGHT),
    SERVO(SERVO), TRIGGER_PIN(TRIGGER_PIN), ECHO_PIN(ECHO_PIN), state(initState),
    S0(S0), S1(S1), S2(S2), S3(S3), sensorOut(sensorOut), k(k), distance(distance) {}

void Robot::init() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);

  myservo.attach(SERVO);
  matrix.begin();

  timerError = millis();
}

void Robot::run() {
  switch (state) {
    case FOLLOW_LINE:
      if (checkDistance()) {
        matrix.loadFrame(stopSign);
        motorLeft(0);
        motorRight(0);
        state = INSPECT_OBSTACLE;
        break;
      }
      followLine();
      break;
    case INSPECT_OBSTACLE:
      inspectObstacle();
      break;
    case AVOID_OBSTACLE:
      avoidObstacle();
      break;
  }
  delay(1);
}

void Robot::followLine() {
  bool left = digitalRead(IR_LEFT);
  bool right = digitalRead(IR_RIGHT);

  if (left && !right) {
    //uint8_t speed = int(k * abs(millis() - timerError) / 100);
    motorLeft(-50);
    motorRight(50);
    myservo.write(135);
    matrix.loadFrame(leftSign);
  }
  if (!left && right) {
    //uint8_t speed = int(k * abs(millis() - timerError) / 100);
    motorLeft(50);
    motorRight(-50);
    myservo.write(45);
    matrix.loadFrame(rightSign);
  }
  if (!left && !right) {
    motorLeft(50);
    motorRight(50);
    myservo.write(90);
    timerError = millis();
    matrix.loadFrame(forwardSign);
  }
  if (left && right) {
    motorLeft(50);
    motorRight(50);
    myservo.write(90);
    timerError = millis();
    matrix.loadFrame(forwardSign);
  }
}

void Robot::avoidObstacle() {
}

void Robot::inspectObstacle() {
  if (!checkDistance())
    state = FOLLOW_LINE;
}

void Robot::motorLeft(short speed) {
  if (speed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (speed < 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  analogWrite(ENA, abs(speed));
}

void Robot::motorRight(short speed) {
  if (speed > 0) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else if (speed < 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  analogWrite(ENB, abs(speed));
}

bool Robot::checkDistance() {
  // Trigger ultrasonic pulse
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure echo duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  return distance > byte(duration * 0.034 / 2);  // Calculate distance in cm
}

Colors Robot::checkColors() {
}
