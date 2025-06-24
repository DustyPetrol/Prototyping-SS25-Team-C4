/**
 * @file Robot.cpp
 * @brief Implementation of the Robot class methods
 * @author Group C4
 * @date 2025
 */

#include "Robot.h"

/**
 * @brief Constructor implementation for Robot class
 * 
 * Initializes all pins and parameters for the robot
 */
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
             uint8_t k)
  : ENA(ENA), ENB(ENB), IN1(IN1), IN2(IN2),
    IN3(IN3), IN4(IN4), IR_LEFT(IR_LEFT), IR_RIGHT(IR_RIGHT),
    SERVO(SERVO), TRIGGER_PIN(TRIGGER_PIN), ECHO_PIN(ECHO_PIN), state(initState),
    S0(S0), S1(S1), S2(S2), S3(S3), sensorOut(sensorOut), k(k), distance(distance), motionState(FORWARD), lastMotionState(FORWARD),lastSeenDirection(FORWARD), avoidMotion(RIGHT) {}


/**
 * @brief Initialize all pins and components
 * 
 * Sets up pin modes for motors, sensors, and initializes servo and LED matrix
 */
void Robot::init() {
  Serial.begin(9600);

  // Set motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set IR sensors as inputs
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Set ultrasonic sensor pins
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set color sensor pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20% for color sensor
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Initialize servo and LED matrix
  myservo.attach(SERVO);
  matrix.begin();

  // Initialize error timer
  timerError = millis();
}

/**
 * @brief Main robot operation function
 * 
 * State machine that controls robot behavior based on current state
 */
void Robot::run() {
  switch (state) {
    case FOLLOW_LINE:
      // Check if obstacle is detected
      if (checkDistance(15)) {
        // Change state to inspect obstacle
        state = INSPECT_OBSTACLE;
        break;
      }
      // Continue following the line
      followLine();
      break;
    case INSPECT_OBSTACLE:
      // Inspect the detected obstacle
      inspectObstacle();
      break;
    case AVOID_OBSTACLE:
      // Avoid the obstacle
      avoidObstacle();
      break;
  }
  // Small delay for stability
  delay(1);
}

/**
 * @brief Line following algorithm implementation
 * 
 * Uses IR sensors to detect the line and adjusts motors accordingly
 */
void Robot::followLine() {
  // Read IR sensor values
  bool left = digitalRead(IR_LEFT);
  bool right = digitalRead(IR_RIGHT);

 if (left && !right) {
  motionState = LEFT;
  lastSeenDirection = LEFT;
} else if (!left && right) {
  motionState = RIGHT;
  lastSeenDirection = RIGHT;
} else if (!left && !right) {
  // Use lastSeenDirection instead
  motionState = lastSeenDirection;
} else {
  // Both on line 
  motionState = FORWARD;
}
  switch (motionState) {
    // Left sensor on line, right sensor off line - turn left
    case LEFT:
      {
        if (lastMotionState != motionState)
          timerError = millis();
        uint8_t speed = int(k * abs(millis() - timerError)) / 1000;
        if (speed >= 30)
          speed = 30;
        motorLeft(30 - speed);      // Left motor backward
        motorRight(-70 + speed);     // Right motor forward
        myservo.write(105);          // Turn servo left
        matrix.loadFrame(leftSign);  // Display left arrow

        lastMotionState = motionState;
        break;
      }
    // Right sensor on line, left sensor off line - turn right, the coefficients change because no two motors are the same in this world
    case RIGHT:
      {
        if (lastMotionState != motionState)
          timerError = millis();
        uint8_t speed = int(k * abs(millis() - timerError)) / 1000;
        if (speed >= 30)
          speed = 30;
        motorLeft(-70 + speed);       // Left motor forward
        motorRight(30 - speed);      // Right motor backward
        myservo.write(75);            // Turn servo right
        matrix.loadFrame(rightSign);  // Display right arrow
        lastMotionState = motionState;
        break;
      }
    // Both sensors off line - go straight
    case FORWARD:
      {
        if (lastMotionState != motionState)
          timerError = millis();
        uint8_t speed = int(k * abs(millis() - timerError)) / 1000;
        if (speed >= 30)
          speed = 30;
        motorLeft(-50 - speed);         // Left motor forward
        motorRight(-50 - speed);        // Right motor forward
        myservo.write(90);              // Center servo
        timerError = millis();          // Reset error timer
        matrix.loadFrame(forwardSign);  // Display forward arrow
        lastMotionState = motionState;
        break;
      }
  }
}

/**
 * @brief Obstacle avoidance algorithm
 * 
 * Controls the robot's movement to navigate around detected obstacles
 */
void Robot::avoidObstacle() {
  switch (avoidMotion) {
    case RIGHT:
      motorLeft(-60);
      motorRight(40);
      if ((millis() - timerError) > 600) {
        avoidMotion = FORWARD;
        timerError = millis();
      }
      break;
    case LEFT:
      motorLeft(0);
      motorRight(-60);
       if (digitalRead(IR_LEFT) || digitalRead(IR_RIGHT)) {
        motorLeft(-60);
        motorRight(60);
        state = FOLLOW_LINE;
      }
      if (checkDistance(20)) {
        avoidMotion = FORWARD;
        timerError = millis();
      }
      if (digitalRead(IR_LEFT) || digitalRead(IR_RIGHT)) {
        motorLeft(-60);
        motorRight(60);
        state = FOLLOW_LINE;
      }
      break;
    case FORWARD:
      motorLeft(-60);
      motorRight(-60);
      if ((millis() - timerError) > 800) {
        avoidMotion = LEFT;
        timerError = millis();
      }
      if (digitalRead(IR_LEFT) || digitalRead(IR_RIGHT)) {
        motorLeft(-60);
        motorRight(60);
        state = FOLLOW_LINE;
      }
      break;
  }
}
/**
 * @brief Inspect detected obstacle
 * 
 * Checks if obstacle is still present, returns to line following if not
 */
void Robot::inspectObstacle() {
  // If obstacle is no longer detected, return to line following
  if (!checkDistance(15))
    state = FOLLOW_LINE;
  else
    switch (checkColor()) {
      case RED:
        motorLeft(60);
        motorRight(80);
        delay(400);
        state = AVOID_OBSTACLE;
        avoidMotion = RIGHT;
        timerError = millis();
        myservo.write(0);
        break;
      case BLUE:
        followLine();
        break;
      case UNKNOWN:
        followLine();
        break;
    }
}

/**
 * @brief Control the left motor
 * @param speed Motor speed (-100 to 100, negative for reverse)
 */
void Robot::motorLeft(short speed) {
  if (speed > 0) {
    // Forward direction
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (speed < 0) {
    // Reverse direction
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    // Stop
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  // Set motor speed using PWM
  analogWrite(ENA, abs(speed));
}

/**
 * @brief Control the right motor
 * @param speed Motor speed (-100 to 100, negative for reverse)
 */
void Robot::motorRight(short speed) {
  if (speed > 0) {
    // Forward direction (note: pins are reversed compared to left motor)
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  } else if (speed < 0) {
    // Reverse direction
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    // Stop
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  // Set motor speed using PWM
  analogWrite(ENB, abs(speed));
}

/**
 * @brief Check distance to obstacle using ultrasonic sensor
 * @return true if obstacle is detected within threshold distance
 */
bool Robot::checkDistance(int distance) {
  // Trigger ultrasonic pulse
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Measure echo duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm and compare with threshold
  // Formula: distance = (duration * speed of sound) / 2
  // Speed of sound = 0.034 cm/µs
  return distance > byte(duration * 0.034 / 2);
}

/**
 * @brief Check color using RGB color sensor
 * @return Detected color (RED, BLUE, or UNKNOWN)
 * 
 * Reads RGB frequencies from the color sensor and determines the dominant color
 */
Colors Robot::checkColor() {
  int redFreq, greenFreq, blueFreq;

  // Read Red frequency
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFreq = pulseIn(sensorOut, LOW);
  delay(10);  // Small delay between readings

  // Read Green frequency
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFreq = pulseIn(sensorOut, LOW);
  delay(10);

  // Read Blue frequency
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFreq = pulseIn(sensorOut, LOW);

  // Simple logic for Red, Blue, or Other
  // Check if red is significantly lower (stronger) than others
  if (redFreq < blueFreq * 0.7 && redFreq < greenFreq * 0.6) {
    return RED;
  }
  // Check if blue is significantly lower (stronger) than others
  else if (blueFreq < redFreq * 0.7 && blueFreq < greenFreq * 0.7) {
    return BLUE;
  }
  // Everything else (including green, white, nothing)
  else {
    return UNKNOWN;  // This represents "OTHER" in your case
  }
}
