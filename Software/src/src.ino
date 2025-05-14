#include "Robot.h"

Robot robot(5, 10, 13, 12, 9, 8, 7, 6, 11, 2, 3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  robot.init();
}
  
void loop() {
  robot.run();
}
