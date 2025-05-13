#define ENA 11
#define ENB 10
#define IN1 13
#define IN2 12
#define IN3 9
#define IN4 8
#define IR_LEFT 7
#define IR_RIGHT 6

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

void loop() {
  bool left = digitalRead(IR_LEFT);
  bool right = digitalRead(IR_RIGHT);

  if (left && !right) {
    motorLeft(-100);
    motorRight(100);
  }
  if (!left && right) {
    motorLeft(100);
    motorRight(-100);
  }
  if (!left && !right) {
    motorLeft(200);
    motorRight(200);
  }
  if (left && right) {
    motorLeft(100);
    motorRight(100);
  }
  delay(1);
}
