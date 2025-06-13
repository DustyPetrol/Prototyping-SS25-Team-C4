/**
 * @file src.ino
 * @brief Main Arduino sketch for line-following robot with obstacle detection
 * @author Group C4
 * @date 2025
 */
#include "Robot.h"

// Motor control pins
#define ENA 5         /**< Enable pin for left motor (PWM) */
#define ENB 10        /**< Enable pin for right motor (PWM) */
#define IN1 13        /**< Direction control pin 1 for left motor */
#define IN2 12        /**< Direction control pin 2 for left motor */
#define IN3 9         /**< Direction control pin 1 for right motor */
#define IN4 8         /**< Direction control pin 2 for right motor */

// Sensor pins
#define IR_LEFT 7     /**< Left infrared sensor pin */
#define IR_RIGHT 6    /**< Right infrared sensor pin */
#define SERVO 11      /**< Servo motor control pin */
#define TRIGGER_PIN 2 /**< Ultrasonic sensor trigger pin */
#define ECHO_PIN 3    /**< Ultrasonic sensor echo pin */

// Color sensor pins (not connected in current implementation)
#define S0 A0        /**< Color sensor frequency scaling selection pin S0 */
#define S1 A1        /**< Color sensor frequency scaling selection pin S1 */
#define S2 A2        /**< Color sensor photodiode selection pin S2 */
#define S3 A3        /**< Color sensor photodiode selection pin S3 */
#define sensorOut A4 /**< Color sensor output pin */

// Robot parameters
#define initState FOLLOW_LINE /**< Initial state of the robot */
#define k 80               /**< Proportional control constant */
#define distance 10           /**< Threshold distance for obstacle detection in cm */

/**
 * @brief Robot instance with all pin and parameter configurations
 */
Robot robot(ENA, ENB, IN1, IN2, IN3, IN4, IR_LEFT, IR_RIGHT, SERVO, TRIGGER_PIN, ECHO_PIN, S0, S1, S2, S3, sensorOut, initState, k, distance);

/**
 * @brief Setup function, runs once at startup
 * 
 * Initializes serial communication and robot hardware
 */
void setup() {
  Serial.begin(9600);  // Initialize serial communication
  robot.init();        // Initialize robot hardware
}

/**
 * @brief Main loop function, runs repeatedly
 * 
 * Calls the robot's run method to execute the state machine
 */
void loop() {
  robot.run();  // Run the robot's state machine
}
