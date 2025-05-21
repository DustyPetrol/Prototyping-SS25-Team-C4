#include "Robot.h"

struct RobotArgs {
  uint8_t ENA = 5;
  uint8_t ENB = 10;
  uint8_t IN1 = 13;
  uint8_t IN2 = 12;
  uint8_t IN3 = 9;
  uint8_t IN4 = 8;
  uint8_t IR_LEFT = 7;
  uint8_t IR_RIGHT = 6;
  uint8_t SERVO = 11;
  uint8_t TRIGGER_PIN = 2;
  uint8_t ECHO_PIN = 3;
  uint8_t S0 = 0;
  uint8_t S1 = 0;
  uint8_t S2 = 0;
  uint8_t S3 = 0;
  uint8_t sensorOut = 0;
  RobotState initState = FOLLOW_LINE;
};

Robot robot({});

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  robot.init();
}

void loop() {
  robot.run();
}
