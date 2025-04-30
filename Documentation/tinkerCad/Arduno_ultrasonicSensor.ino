class ModelCar {
  private:
    int sigPin;

  public:
    ModelCar(int pin) {
      sigPin = pin;
    }

    void begin() {
      Serial.begin(9600);
      pinMode(sigPin, OUTPUT);
    }

    int detectLine() {
      
      digitalWrite(sigPin, LOW);
      delayMicroseconds(4);
      digitalWrite(sigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(sigPin, LOW);

      
      pinMode(sigPin, INPUT);
      int duration = pulseIn(sigPin, HIGH);

      
      int distance = duration / 58;
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      pinMode(sigPin, OUTPUT); 

      delay(500);
      return distance;
    }
};

ModelCar modelCar(7); 

void setup() {
  modelCar.begin();
}

void loop() {
  modelCar.detectLine();
}
