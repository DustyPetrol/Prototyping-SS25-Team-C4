#define S0 5
#define S1 6
#define S2 7
#define S3 8
#define sensorOut 4

int redMin = 1300, redMax = 1800;
int greenMin = 1400, greenMax = 1750;

const int threshold = 30;  

void setup() {
  pinMode(S0, OUTPUT); pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT); pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, LOW);  // 2% frequency scaling
  digitalWrite(S1, HIGH);

  Serial.begin(9600);
}

int readColorFreq(int s2, int s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  float period = pulseIn(sensorOut, HIGH) + pulseIn(sensorOut, LOW);
  return (period > 0) ? (1.0 / (period / 1000000.0)) : 0;
}

int getColorValue(int freq, int minVal, int maxVal) {
  return constrain(map(freq, maxVal, minVal, 255, 0), 0, 255);
}

String detectColor() {
  int rFreq = readColorFreq(LOW, LOW);     // RED
  int gFreq = readColorFreq(HIGH, HIGH);   // GREEN

  int redColor   = getColorValue(rFreq, redMin, redMax);
  int greenColor = getColorValue(gFreq, greenMin, greenMax);

 
  if (redColor < threshold && greenColor < threshold)
    return "UNKNOWN";

  if (redColor > greenColor)
    return "RED";
  else if (greenColor > redColor)
    return "GREEN";
  else
    return "UNKNOWN";  
}

void loop() {
  String result = detectColor();   
  //Serial.println(result);            
  delay(100);
}