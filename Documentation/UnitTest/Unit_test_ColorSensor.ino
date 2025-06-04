#define S0 5
#define S1 6
#define S2 7
#define S3 8
#define sensorOut 4


int redMin = 1300, redMax = 1800;
int greenMin = 1400, greenMax = 1750;
int blueMin = 1500, blueMax = 2450;

int redColor, greenColor, blueColor;

void setup() {
  pinMode(S0, OUTPUT); pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT); pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, LOW);  // 2% frequency scaling for stable output
  digitalWrite(S1, HIGH);

  Serial.begin(9600);
}

int readColorFreq(int s2, int s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  float period = pulseIn(sensorOut, HIGH) + pulseIn(sensorOut, LOW);
  return (period > 0) ? (1.0 / (period / 1000000.0)) : 0;  // Convert to Hz
}

int getColorValue(int freq, int minVal, int maxVal) {
  return constrain(map(freq, maxVal, minVal, 255, 0), 0, 255);
}

void loop() {
  Serial.println("UNIT TEST: COLOR SENSOR");

  int rFreq = readColorFreq(LOW, LOW);   // RED
  int gFreq = readColorFreq(HIGH, HIGH); // GREEN
  int bFreq = readColorFreq(LOW, HIGH);  // BLUE

  redColor   = getColorValue(rFreq, redMin, redMax);
  greenColor = getColorValue(gFreq, greenMin, greenMax);
  blueColor  = getColorValue(bFreq, blueMin, blueMax);

  Serial.print("R: "); Serial.print(rFreq); Serial.print(" Hz → "); Serial.println(redColor);
  Serial.print("G: "); Serial.print(gFreq); Serial.print(" Hz → "); Serial.println(greenColor);
  Serial.print("B: "); Serial.print(bFreq); Serial.print(" Hz → "); Serial.println(blueColor);

  if (redColor > greenColor && redColor > blueColor)
    Serial.println("RESULT: RED detected");
  else if (greenColor > redColor && greenColor > blueColor)
    Serial.println("RESULT: GREEN detected");
  else if (blueColor > redColor && blueColor > greenColor)
    Serial.println("RESULT: BLUE detected");
  else
    Serial.println("RESULT: UNKNOWN");

  Serial.println("------------------------------------");
  delay(2000);
}
