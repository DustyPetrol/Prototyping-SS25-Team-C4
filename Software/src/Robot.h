//
// Created by eggcitedraccoon on 5/14/25.
//

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

enum Colors{
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
  uint8_t k = 2;
  byte distance = 15;
  void followLine();
  void avoidObstacle();
  void inspectObstacle();
  void motorLeft(short speed);
  void motorRight(short speed);
  bool checkDistance();
  Colors checkColors();
public:
  Robot(RobotArgs args);
  void init();
  void run();
};

#endif  //ROBOT_H
