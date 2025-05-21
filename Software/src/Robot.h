#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include <Servo.h>
#include "Arduino_LED_Matrix.h"
#include "screen_matrices.h"

enum RobotState {
  FOLLOW_LINE,
  INSPECT_OBSTACLE,
  AVOID_OBSTACLE
};

enum Colors {
  RED,
  GREEN,
  BLUE
};

class Robot {
private:
  Servo myservo;
  ArduinoLEDMatrix matrix;
  RobotState state;
  uint8_t ENA, ENB, IN1, IN2, IN3, IN4;
  uint8_t IR_LEFT, IR_RIGHT, SERVO;
  uint8_t TRIGGER_PIN, ECHO_PIN;
  uint8_t S0, S1, S2, S3, sensorOut;
  uint32_t timerError;
  uint8_t k;
  uint8_t distance;
  void followLine();
  void avoidObstacle();
  void inspectObstacle();
  void motorLeft(short speed);
  void motorRight(short speed);
  bool checkDistance();
  Colors checkColors();
public:
  Robot(uint8_t ENA,
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
  uint8_t distance);
  void init();
  void run();
};

#endif  //ROBOT_H
