#include <Servo.h>
#include "Arduino_LED_Matrix.h"

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

Servo myservo;
ArduinoLEDMatrix matrix;

const uint32_t happy[] = {
  0x19819,
  0x80000001,
  0x81f8000
};
const uint32_t heart[] = {
  0x3184a444,
  0x44042081,
  0x100a0040
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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

void motorLeft(short speed) {
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

void motorRight(short speed) {
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

long measureDistance() {
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

void loop() {
  long distance = measureDistance();

  if (distance < 20) {  // Obstacle detection (30cm threshold)
    motorLeft(0);
    motorRight(0);
    matrix.loadFrame(heart);
    delay(10);
  } else {
    matrix.loadFrame(happy);
    bool left = digitalRead(IR_LEFT);
    bool right = digitalRead(IR_RIGHT);

    if (left && !right) {
      motorLeft(-100);
      motorRight(170);
      myservo.write(135);
    }
    if (!left && right) {
      motorLeft(170);
      motorRight(-100);
      myservo.write(45);
    }
    if (!left && !right) {
      motorLeft(150);
      motorRight(150);
      myservo.write(90);
    }
    if (left && right) {
      motorLeft(100);
      motorRight(100);
      myservo.write(90);
    }
  }
  delay(1);
}
