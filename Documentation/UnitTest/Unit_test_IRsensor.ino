#include <Arduino.h>

enum RobotState {
  FOLLOW_LINE,
  INSPECT_OBSTACLE,
  AVOID_OBSTACLE
};

class Robot {
  private:
    uint8_t irLeftPin;
    uint8_t irRightPin;
    RobotState state;

  public:
    // Constructor
    Robot(uint8_t left, uint8_t right, RobotState initState)
      : irLeftPin(left), irRightPin(right), state(initState) {}

    // Initialize IR pins and Serial
    void init() {
      pinMode(irLeftPin, INPUT);
      pinMode(irRightPin, INPUT);
      Serial.begin(9600);
      Serial.println("IR Sensor Unit Test...");
    }

    // Test function for IR sensors
    void testIR() {
      bool leftDetected = digitalRead(irLeftPin);
      bool rightDetected = digitalRead(irRightPin);

      Serial.print("Left IR [D7]: ");
      Serial.print(leftDetected ? "LINE DETECTED" : "NO LINE");
      Serial.print(" | Right IR [D6]: ");
      Serial.println(rightDetected ? "LINE DETECTED" : "NO LINE");

      delay(200);
    }
};

#define IR_LEFT 7
#define IR_RIGHT 6

Robot myRobot(IR_LEFT, IR_RIGHT, FOLLOW_LINE);

void setup() {
  myRobot.init();  // Initialize pins and serial
}

void loop() {
  myRobot.testIR();  // Continuously run IR sensor test
}
