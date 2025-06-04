class Robot {
  private:
    uint8_t trigPin;
    uint8_t echoPin;
    uint8_t thresholdCM;

  public:
    Robot(uint8_t trig, uint8_t echo, uint8_t threshold)
      : trigPin(trig), echoPin(echo), thresholdCM(threshold) {}

    void begin() {
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
      Serial.begin(9600);
      Serial.println("Ultrasonic Unit Test Started...");
    }

    float readDistance() {
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      long duration = pulseIn(echoPin, HIGH);
      return duration * 0.034 / 2.0;
    }

    void testUltrasonic() {
      float d = readDistance();
      Serial.print("Distance: ");
      Serial.print(d);
      Serial.print(" cm → ");
      Serial.println(d < thresholdCM ? "Obstacle" : "Clear");
      delay(500);
    }
};

Robot robot(2, 3, 15); // TRIG = D2, ECHO = D3

void setup() {
  robot.begin();
}

void loop() {
  robot.testUltrasonic();
}
