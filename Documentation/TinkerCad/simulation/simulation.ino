#define ENA 10
#define IN1 7
#define IN2 6
#define ENB 11
#define IN3 8
#define IN4 9

#define LEFT_SENSOR A0
#define RIGHT_SENSOR A1
#define THRESHOLD 600

#define MAX_SPEED 200
#define NORMAL_SPEED 150
#define SLOW_SPEED 100
#define STOP 0

#define TRIGGER_PIN 2
#define ECHO_PIN 3

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(LEFT_SENSOR, INPUT);
  pinMode(RIGHT_SENSOR, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Serial.begin(9600);
  Serial.println("Line Follower Robot Initialized");
  
  stopMotors();
  delay(2000);  // Startup delay
}

void loop() {
  long distance = measureDistance();
  
  if (distance < 30) {  // Obstacle detection (30cm threshold)
    stopMotors();
    delay(1000);
  } else {
    // Read sensor values
    double leftSensorValue = analogRead(LEFT_SENSOR);
    double rightSensorValue = analogRead(RIGHT_SENSOR);
    
    // Convert to digital logic (true = black line detected)
    bool leftOnLine = (leftSensorValue < THRESHOLD);
    bool rightOnLine = (rightSensorValue < THRESHOLD);

    // Debug output
    Serial.print("Left Raw: ");
    Serial.print(leftSensorValue);
    Serial.print(" Right Raw: ");
    Serial.print(rightSensorValue);
    Serial.print(" | Left Digital: ");
    Serial.print(leftOnLine);
    Serial.print(" Right Digital: ");
    Serial.println(rightOnLine);
    
    // Line following logic
    if (leftOnLine && rightOnLine) {
      moveForward(NORMAL_SPEED);
    } else if (!leftOnLine && rightOnLine) {
      turnRight(SLOW_SPEED);
    } else if (leftOnLine && !rightOnLine) {
      turnLeft(SLOW_SPEED);
    } else {
      moveForward(SLOW_SPEED);  // Both sensors off line - continue slowly
    }
  }
}

// Motor control functions
void moveForward(int speed) {
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void turnLeft(int speed) {
  // Left motor stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, STOP);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}

void turnRight(int speed) {
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);

  // Right motor stop
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, STOP);
}

void stopMotors() {
  // Stop both motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, STOP);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, STOP);
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
