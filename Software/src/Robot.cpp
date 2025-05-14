//
// Created by eggcitedraccoon on 5/14/25.
//
#include "Robot.h"

Robot::Robot(uint8_t ENA, uint8_t ENB, uint8_t IN1, uint8_t IN2,
             uint8_t IN3, uint8_t IN4, uint8_t IR_LEFT, uint8_t IR_RIGHT,
             uint8_t SERVO, uint8_t TRIGGER_PIN, uint8_t ECHO_PIN)
  : ENA(ENA), ENB(ENB), IN1(IN1), IN2(IN2),
    IN3(IN3), IN4(IN4), IR_LEFT(IR_LEFT), IR_RIGHT(IR_RIGHT),
    SERVO(SERVO), TRIGGER_PIN(TRIGGER_PIN), ECHO_PIN(ECHO_PIN), state(FOLLOW_LINE) {}

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

  myservo.attach(SERVO);
  matrix.begin();
}

void Robot::run() {
  switch (state) {
    case FOLLOW_LINE:
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
  long distance = measureDistance();

  if (distance < 20) {  // Obstacle detection (30cm threshold)
    motorLeft(0);
    motorRight(0);
    matrix.loadFrame(stopSign);
    delay(10);
  } else {
    bool left = digitalRead(IR_LEFT);
    bool right = digitalRead(IR_RIGHT);

    if (left && !right) {
      motorLeft(-100);
      motorRight(170);
      myservo.write(135);
      matrix.loadFrame(leftSign);
    }
    if (!left && right) {
      motorLeft(170);
      motorRight(-100);
      myservo.write(45);
      matrix.loadFrame(rightSign);
    }
    if (!left && !right) {
      motorLeft(150);
      motorRight(150);
      myservo.write(90);
      matrix.loadFrame(forwardSign);
    }
    if (left && right) {
      motorLeft(100);
      motorRight(100);
      myservo.write(90);
      matrix.loadFrame(forwardSign);
    }
  }
}

void Robot::avoidObstacle() {
}

void Robot::inspectObstacle() {
}

void Robot::motorLeft(short speed) {
  if (speed > 10) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (speed < -10) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
    return;
  }
  analogWrite(ENA, abs(speed));
}

void Robot::motorRight(short speed) {
  if (speed > 10) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else if (speed < -10) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, 0);
    return;
  }
  analogWrite(ENB, abs(speed));
}

long Robot::measureDistance() {
  // Trigger ultrasonic pulse
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure echo duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  return duration * 0.034 / 2;
}