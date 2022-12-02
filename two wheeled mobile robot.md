# #include<NewPing.h>

#define TRIG A2
#define ECHO A3
#define MAX_DISTANCE 100  // Max Distance = 100
int rightMotor = 3;  // Right Motor
int leftMotor = 5;  // Left Motor
int rightSensor = A0; // right IR Sensor
int leftSensor = A1;  // left IR Sensor

NewPing sonar(TRIG, ECHO, MAX_DISTANCE);

void setup() {
  pinMode(rightMotor, OUTPUT);
  pinMode(leftMotor, OUTPUT);
  pinMode(rightSensor, INPUT);
  pinMode(leftSensor, INPUT);          
}

void loop()
{
  delay(50);
  int distance = sonar.ping_cm();
  if (distance == 0) {
    distance = 20;
    }
    if(distance <=15) {
      Stop();
      delay(500);
      turnLeft();
      delay(300);
      moveForward();
      delay(600);
      turnRight();
      delay(300);
      moveForward();
      delay(800);
      turnRight();
      delay(300);
      moveForward();
      delay(600);
      turnLeft();
      delay(350);
      }
      if ((digitalRead(leftSensor) == 1)&&(digitalRead(rightSensor) == 1)){moveForward();}
      if ((digitalRead(leftSensor) == 1)&&(digitalRead(rightSensor) == 0)){turnRight();}
      if ((digitalRead(leftSensor) == 0)&&(digitalRead(rightSensor) == 1)){turnLeft();}
      if ((digitalRead(leftSensor) == 0)&&(digitalRead(rightSensor) == 0)){Stop();}
}

void Stop() {
  analogWrite(rightMotor, 0);
  analogWrite(leftMotor, 0);
}
void turnRight() {
  analogWrite(rightMotor, 0);
  analogWrite(leftMotor, 255);
}
void turnLeft() {
  analogWrite(rightMotor, 255);
  analogWrite(leftMotor, 0);
}
void moveForward() {
  analogWrite(rightMotor, 255);
  analogWrite(leftMotor, 255);
}
