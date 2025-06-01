#define S0 5
#define S1 6
#define S2 7
#define S3 8
#define sensorOut 4

enum Colors {
  RED,
  GREEN,
  BLUE,
  UNKNOWN
};

Colors checkColors() {
  int redFreq, greenFreq, blueFreq;

  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  delay(100);
  redFreq = pulseIn(sensorOut, LOW);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  delay(100);
  greenFreq = pulseIn(sensorOut, LOW);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  delay(100);
  blueFreq = pulseIn(sensorOut, LOW);

  Serial.print("Color Frequencies -> R: ");
  Serial.print(redFreq);
  Serial.print(" G: ");
  Serial.print(greenFreq);
  Serial.print(" B: ");
  Serial.println(blueFreq);

  if (redFreq < greenFreq && redFreq < blueFreq) {
    return RED;
  } else if (greenFreq < redFreq && greenFreq < blueFreq) {
    return GREEN;
  } else if (blueFreq < redFreq && blueFreq < greenFreq) {
    return BLUE;
  } else {
    return UNKNOWN;
  }
}

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  /*Scaling the output frequency
 S0/S1
 LOW/LOW=AUS, LOW/HIGH=2%,
 HIGH/LOW=20%, HIGH/HIGH=100%*/
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  Serial.begin(9600);
}

void loop() {
  switch (checkColors()) {
    case RED:
      Serial.println("RED");
      break;
    case GREEN:
      Serial.println("GREEN");
      break;
    case BLUE:
      Serial.println("BLUE");
      break;
    case UNKNOWN:
      Serial.println("UNKNOWN");
      break;
  }
  delay(5);
}