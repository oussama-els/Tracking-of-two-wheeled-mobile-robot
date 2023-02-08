#include <NewPing.h>

#define MAX_DISTANCE 100

// Left Ultrasonic sensor
#define TrigPinL A0 
#define EchoPinL A1 

//Front Ultrasonic sensor
#define TrigPinF A2
#define EchoPinF A3

//Left Motor
#define Lm1 5 
#define Lm2 6

//Right Motor
#define Rm1 10
#define Rm2 11

// Left and Right IR sensor
#define Lsensor A4
#define Rsensor A5

boolean noDistanceFL, line;

NewPing sonarLeft(TrigPinL, EchoPinL, MAX_DISTANCE);
NewPing sonarFront(TrigPinF, EchoPinF, MAX_DISTANCE);

void lineFollowing() {
if ((digitalRead(Lsensor) == 1) && (digitalRead(Rsensor) == 1)) {
line_forward();
line = true;
}
if ((digitalRead(Lsensor) == 1) && (digitalRead(Rsensor) == 0)) {
turn_leftL();
line = true;
}
if ((digitalRead(Lsensor) == 0) && (digitalRead(Rsensor) == 1)) {
turn_rightL();
line = true;
}
}

void setup() {
Serial.begin(9600);
pinMode (Lm1, OUTPUT);
pinMode (Lm2, OUTPUT);
pinMode (Rm1, OUTPUT);
pinMode (Rm2, OUTPUT);
pinMode (TrigPinL, OUTPUT);
pinMode (EchoPinL, INPUT);
pinMode (TrigPinF, OUTPUT);
pinMode (EchoPinF, INPUT);
pinMode (Rsensor, INPUT);
pinMode (Lsensor, INPUT);
}

void loop() {
delay(50);
lineFollowing();

int distanceL = sonarLeft.ping_cm();
if (distanceL == 0) {
distanceL = 50;
}
int distanceF = sonarFront.ping_cm();
if (distanceF == 0) {
distanceF = 50;
}

if ((digitalRead(Lsensor) == 0) && (digitalRead(Rsensor) == 0)) {
line = false;
}

delay(50);

if ((distanceL >= 30) && (distanceF >= 30)) {
noDistanceFL = true;
} else {
noDistanceFL = false;
}

if ((distanceF <= 15) && (distanceL > 25)) {
StopF();
delay(500);
Serial.println("Stop");
turn_right();
delay(370);
drive_forward();
delay(70);
}

if ((distanceL < 20) && (distanceF > 30)) {
delay(50);
forward();
}

if ((distanceL <= 5) && (distanceF > 30)) {
delay(50);
drive_forward();
delay(100);
turn_right();
delay(100);
turn_left();
delay(100);
drive_forward();
delay(100);
}

if (((distanceL > 30) && (distanceF > 30)) && (line == true)) {
delay(50);
lineFollowing();
}

if (((distanceL <= 27) && (distanceF > 30)) && (line == true)) {
delay(50);
turn_right();
delay(300);
}

if (noDistanceFL = false) {
StopF();
delay(500);
Serial.print("Stop");
turn_right();
delay(300);
}

if ((noDistanceFL = false) && (line == true)) {
lineFollowing();
}

if ((distanceL > 30) && (line == false)) {
delay(50);
turn();
}
}

void turn() {
analogWrite(Lm1, 255);
analogWrite(Rm1, 110);
}

void Stop() {
digitalWrite(Lm1, LOW);
digitalWrite(Lm2, LOW);
digitalWrite(Rm1, LOW);
digitalWrite(Rm2, LOW);
}

void StopF() {
digitalWrite(Lm1, LOW);
digitalWrite(Lm2, LOW);
digitalWrite(Rm1, LOW);
digitalWrite(Rm2, LOW);
}

void line_forward() {
analogWrite(Lm1, 180);
analogWrite(Lm2, LOW);
analogWrite(Rm1, 180);
analogWrite(Rm2, LOW);
}

void drive_forward() {
analogWrite(Lm1, 230);
analogWrite(Lm2, LOW);
analogWrite(Rm1, 230);
analogWrite(Rm2, LOW);
}

void forward() {
analogWrite(Lm1, 160);
analogWrite(Lm2, LOW);
analogWrite(Rm1, 160);
analogWrite(Rm2, LOW);
}

void drive_backward() {
digitalWrite(Lm1, LOW);
digitalWrite(Lm2, HIGH);
digitalWrite(Rm1, LOW);
digitalWrite(Rm2, HIGH);
}

void turn_left() {
digitalWrite(Lm1, HIGH);
digitalWrite(Lm2, LOW);
digitalWrite(Rm1, LOW);
digitalWrite(Rm2, HIGH);
}

void turn_leftL() {
analogWrite(Lm1, 180);
digitalWrite(Lm2, LOW);
digitalWrite(Rm1, LOW);
digitalWrite(Rm2, LOW);
}

void turn_right() {
digitalWrite(Lm1, LOW);
digitalWrite(Lm2, HIGH);
digitalWrite(Rm1, HIGH);
digitalWrite(Rm2, LOW);
}

void turn_rightL() {
digitalWrite(Lm1, LOW);
digitalWrite(Lm2, LOW);
analogWrite(Rm1, 180);
digitalWrite(Rm2, LOW);
}
