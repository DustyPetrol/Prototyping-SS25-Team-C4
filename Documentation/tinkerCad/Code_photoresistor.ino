class ModelCar {
  private:
    int _ldrPin;   
    int _ledPin;      
    int _threshold;    

  public:
    ModelCar(int ldrPin, int ledPin, int threshold)
      : _ldrPin(ldrPin), _ledPin(ledPin), _threshold(threshold)
    {}

    void begin(unsigned long baud = 9600) {
      pinMode(_ledPin, OUTPUT);
      Serial.begin(baud);
    }

    bool detectLine() {
      int lightLevel = analogRead(_ldrPin);
      Serial.println(lightLevel);

      bool isDark = (lightLevel < _threshold);
      digitalWrite(_ledPin, isDark ? HIGH : LOW);
      return isDark;
    }
};

ModelCar model_car(A0, 7, 500);

void setup() {
  model_car.begin();
}

void loop() {
  model_car.detectLine();
  delay(200);
}
