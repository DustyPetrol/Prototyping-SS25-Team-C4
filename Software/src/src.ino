#include "Robot.h"
#define ENA 5
#define ENB 10
#define IN1 13
#define IN2 12
#define IN3 9
#define IN4 8
#define IR_LEFT 7
#define IR_RIGHT 6
#define SERVO 11
#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define S0 0
#define S1 0
#define S2 0
#define S3 0
#define sensorOut 0
#define initState FOLLOW_LINE
#define k 10
#define distance 15

Robot robot(ENA, ENB, IN1, IN2, IN3, IN4, IR_LEFT, IR_RIGHT, SERVO, TRIGGER_PIN, ECHO_PIN, S0, S1, S2, S3, sensorOut, initState, k, distance);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  robot.init();
}

void loop() {
  robot.run();
}
