/**
 * @file Robot.h
 * @brief Robot class definition for line-following robot with obstacle detection
 * @author Group C4
 * @date 2025
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include <Servo.h>
#include "Arduino_LED_Matrix.h"
#include "screen_matrices.h"

/**
 * @enum RobotState
 * @brief Defines the possible states of the robot
 */
enum RobotState {
  FOLLOW_LINE,      /**< Robot is following a line */
  INSPECT_OBSTACLE, /**< Robot is inspecting an obstacle */
  AVOID_OBSTACLE    /**< Robot is avoiding an obstacle */
};

/**
 * @enum Colors
 * @brief Defines the colors that can be detected by the color sensor
 */
enum Colors {
  RED,   /**< Red color */
  GREEN, /**< Green color */
  BLUE   /**< Blue color */
};

/**
 * @enum Motion
 * @brief Defines the motion direction of the robot
 */
enum Motion {
  FORWARD,   /**< Forward */
  LEFT, /**< Left */
  RIGHT   /**< Right */
};


/**
 * @class Robot
 * @brief Main robot control class that handles line following, obstacle detection and avoidance
 */
class Robot {
private:
  Servo myservo;                 /**< Servo motor for steering */
  ArduinoLEDMatrix matrix;       /**< LED matrix for displaying status */
  RobotState state;              /**< Current state of the robot */
  uint8_t ENA, ENB, IN1, IN2, IN3, IN4; /**< Motor control pins */
  uint8_t IR_LEFT, IR_RIGHT, SERVO;     /**< IR sensors and servo pins */
  uint8_t TRIGGER_PIN, ECHO_PIN;        /**< Ultrasonic sensor pins */
  uint8_t S0, S1, S2, S3, sensorOut;    /**< Color sensor pins */
  uint32_t timerError;           /**< Timer for error correction */
  uint8_t k;                     /**< Proportional control constant */
  uint8_t distance;              /**< Threshold distance for obstacle detection */
  Motion lastState;
  /**
   * @brief Follow the line using IR sensors
   */
  void followLine();

  /**
   * @brief Avoid detected obstacle
   */
  void avoidObstacle();

  /**
   * @brief Inspect detected obstacle
   */
  void inspectObstacle();

  /**
   * @brief Control the left motor
   * @param speed Motor speed (-100 to 100, negative for reverse)
   */
  void motorLeft(short speed);

  /**
   * @brief Control the right motor
   * @param speed Motor speed (-100 to 100, negative for reverse)
   */
  void motorRight(short speed);

  /**
   * @brief Check distance to obstacle using ultrasonic sensor
   * @return true if obstacle is detected within threshold distance
   */
  bool checkDistance();

  /**
   * @brief Check color using RGB color sensor
   * @return Detected color (RED, GREEN, or BLUE)
   */
  Colors checkColors();
public:
  /**
   * @brief Constructor for Robot class
   * @param ENA Enable pin for left motor
   * @param ENB Enable pin for right motor
   * @param IN1 Direction control pin 1 for left motor
   * @param IN2 Direction control pin 2 for left motor
   * @param IN3 Direction control pin 1 for right motor
   * @param IN4 Direction control pin 2 for right motor
   * @param IR_LEFT Left infrared sensor pin
   * @param IR_RIGHT Right infrared sensor pin
   * @param SERVO Servo motor control pin
   * @param TRIGGER_PIN Ultrasonic sensor trigger pin
   * @param ECHO_PIN Ultrasonic sensor echo pin
   * @param S0 Color sensor frequency scaling selection pin S0
   * @param S1 Color sensor frequency scaling selection pin S1
   * @param S2 Color sensor photodiode selection pin S2
   * @param S3 Color sensor photodiode selection pin S3
   * @param sensorOut Color sensor output pin
   * @param initState Initial state of the robot
   * @param k Proportional control constant
   * @param distance Threshold distance for obstacle detection in cm
   */
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

  /**
   * @brief Initialize robot hardware and pins
   */
  void init();

  /**
   * @brief Main robot operation function, called repeatedly in loop
   */
  void run();
};

#endif  //ROBOT_H
