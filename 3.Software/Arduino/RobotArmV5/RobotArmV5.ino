// Ethan Lawlor
// 27/05/2024

// Functionality of Code:
// Commands from Serial Monitor
// Commands from Bluetooth - MIT App Inventor
// Set individual servo angles - 0,0,0,0,0,0*/180,180,180,180,180,180*
// Send groups of servo angles through keywords - Home/Ready/Wave
// Set smoothing value - 0#/100#

#include <SoftwareSerial.h>

SoftwareSerial btSerial(2, 4);

#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int gripper;
int servo1pos;
float grippersmoothed;
float gripperPrev;

int switch2;
int servo2pos;
float switch2smoothed;
float switch2Prev;

int switch3;
int servo3pos;
float switch3smoothed;
float switch3Prev;

int switch4;
int servo4pos;
float switch4smoothed;
float switch4Prev;

int switch5;
int servo5pos;
float switch5smoothed;
float switch5Prev;

int switch6;
int servo6pos;
float switch6smoothed;
float switch6Prev;

const int servoPin1 = 3;
const int servoPin2 = 5;
const int servoPin3 = 6;
const int servoPin4 = 9;
const int servoPin5 = 10;
const int servoPin6 = 11;

const int open = 180;
const int close = 50;

char character;
String receivedData;
String angle_1;
String angle_2;
String angle_3;
String angle_4;
String angle_5;
String angle_6;

float smoothing = 0.03;
int servoDelay = 5;

int commaIndex;

void setup() {

  Serial.begin(9600);
  btSerial.begin(9600);

  pinMode(servoPin1, OUTPUT);
  pinMode(servoPin2, OUTPUT);
  pinMode(servoPin3, OUTPUT);
  pinMode(servoPin4, OUTPUT);
  pinMode(servoPin5, OUTPUT);
  pinMode(servoPin6, OUTPUT);

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);
  servo5.attach(servoPin5);
  servo6.attach(servoPin6);

  Serial.println("<Arduino Ready>");
  delay(1000);

  Serial.println("");
  Serial.print("Homing...");

  smoothing = 0.010;
  Serial.print("");
  Serial.print("Smoothing = ");
  Serial.println(smoothing, 3);

  servo6.write(90);
  switch6 = 90;
  servo6pos = 90;
  switch6smoothed = 90;
  switch6Prev = 90;

  servo5.write(180);
  switch5 = 180;
  servo5pos = 180;
  switch5smoothed = 180;
  switch5Prev = 180;

  servo4.write(0);
  switch4 = 0;
  servo4pos = 0;
  switch4smoothed = 0;
  switch4Prev = 0;

  servo3.write(90);
  switch3 = 90;
  servo3pos = 90;
  switch3smoothed = 90;
  switch3Prev = 90;

  servo2.write(90);
  switch2 = 90;
  servo2pos = 90;
  switch2smoothed = 90;
  switch2Prev = 90;

  servo1.write(0);
  gripper = 0;
  servo1pos = 0;
  grippersmoothed = 0;
  gripperPrev = 0;

  ready();
  home();

  smoothing = 0.03;
  Serial.println("");
  Serial.print("Finished Homing...");
  Serial.print("");
  Serial.print("Smoothing = ");
  Serial.println(smoothing);

  Serial.println("");
  Serial.println("<Robot Arm Ready>");
  delay(1000);
}

void loop() {

  readSerialData();

}

void readSerialData() {

  while (Serial.available()) {
    character = Serial.read();
    receivedData = receivedData + character;
    checkAndExecute();
  }

  while (btSerial.available()) {
    character = btSerial.read();
    receivedData = receivedData + character;
    checkAndExecute();
  }
}

void checkAndExecute() {

  if (receivedData == "Home") {
    receivedData = "";
    home();
  }

  if (receivedData == "Ready") {
    receivedData = "";
    ready();
  }

  if (receivedData == "Wave") {
    wave();
    receivedData = "";
  }

  if (receivedData == "Screwdriver") {
    receivedData = "";
    screwdriver();
  }

  if (receivedData == "Circles") {
    receivedData = "";
    circles();
  }

  if (receivedData == "Diagonals") {
    receivedData = "";
    diagonals();
  }

  if (receivedData == "Worm") {
    receivedData = "";
    worm();
  }

  if (receivedData == "Demo") {
    receivedData = "";
    demo();
  }


  else if (character == '#') {

    Serial.println("");
    Serial.println(receivedData);
    receivedData = receivedData.substring(0, receivedData.length() - 1);  // Remove the last character '*'
    int receivedStr = receivedData.toInt();
    float smoothingRaw = map(receivedStr, 0, 100, 1, 90);
    smoothing = smoothingRaw / 1000;
    Serial.print("");
    Serial.print("Smoothing = ");
    Serial.println(smoothing, 3);

    receivedData = "";

  }

  else if (character == '*') {
    Serial.println("");
    Serial.println(receivedData);
    receivedData = receivedData.substring(0, receivedData.length() - 1);  // Remove the last character '*'
    commaIndex = receivedData.indexOf(',');
    angle_1 = receivedData.substring(0, commaIndex);
    receivedData = receivedData.substring(commaIndex + 1);

    commaIndex = receivedData.indexOf(',');
    angle_2 = receivedData.substring(0, commaIndex);
    receivedData = receivedData.substring(commaIndex + 1);

    commaIndex = receivedData.indexOf(',');
    angle_3 = receivedData.substring(0, commaIndex);
    receivedData = receivedData.substring(commaIndex + 1);

    commaIndex = receivedData.indexOf(',');
    angle_4 = receivedData.substring(0, commaIndex);
    receivedData = receivedData.substring(commaIndex + 1);

    commaIndex = receivedData.indexOf(',');
    angle_5 = receivedData.substring(0, commaIndex);
    angle_6 = receivedData.substring(commaIndex + 1);

    gripper = angle_1.toInt();
    switch2 = angle_2.toInt();
    switch3 = angle_3.toInt();
    switch4 = angle_4.toInt();
    switch5 = angle_5.toInt();
    switch6 = angle_6.toInt();

    receivedData = "";

    moveServos();
  }
}

void moveServos() {

  Serial.println("");
  Serial.print("Moving...");
  Serial.print("");
  Serial.print("Smoothing = ");
  Serial.println(smoothing, 3);

  while (servo1pos != gripper || servo2pos != switch2 || servo3pos != switch3 || servo4pos != switch4 || servo5pos != switch5 || servo6pos != switch6) {

    readSerialData();

    // **   smoothing **  //

    grippersmoothed = (gripper * smoothing) + (gripperPrev * (1 - smoothing));
    gripperPrev = grippersmoothed;
    servo1pos = round(grippersmoothed);

    switch2smoothed = (switch2 * smoothing) + (switch2Prev * (1 - smoothing));
    switch2Prev = switch2smoothed;
    servo2pos = round(switch2smoothed);

    switch3smoothed = (switch3 * smoothing) + (switch3Prev * (1 - smoothing));
    switch3Prev = switch3smoothed;
    servo3pos = round(switch3smoothed);

    switch4smoothed = (switch4 * smoothing) + (switch4Prev * (1 - smoothing));
    switch4Prev = switch4smoothed;
    servo4pos = round(switch4smoothed);

    switch5smoothed = (switch5 * smoothing) + (switch5Prev * (1 - smoothing));
    switch5Prev = switch5smoothed;
    servo5pos = round(switch5smoothed);

    switch6smoothed = (switch6 * smoothing) + (switch6Prev * (1 - smoothing));
    switch6Prev = switch6smoothed;
    servo6pos = round(switch6smoothed);

    // ** end of smoothing  **  //

    servo1.write(servo1pos);
    servo2.write(servo2pos);
    servo3.write(servo3pos);
    servo4.write(servo4pos);
    servo5.write(servo5pos);
    servo6.write(servo6pos);

    delay(servoDelay);
  }
}

void home() {

  Serial.println("");
  Serial.println("Home");
  gripper = close;
  switch2 = 90;
  switch3 = 90;
  switch4 = 0;
  switch5 = 180;
  switch6 = 90;
  moveServos();
}

void ready() {

  Serial.println("");
  Serial.println("Ready");
  gripper = 0;
  switch2 = 0;
  switch3 = 135;
  switch4 = 90;
  switch5 = 135;
  switch6 = 90;
  moveServos();
}

void wave() {

  Serial.println("");
  Serial.println("Wave");
  gripper = close;
  switch2 = 0;
  switch3 = 135;
  switch4 = 90;
  switch5 = 135;
  switch6 = 90;
  moveServos();

  gripper = open;
  switch2 = 180;
  switch6 = 105;
  moveServos();

  gripper = close;
  switch2 = 0;
  switch6 = 75;
  moveServos();
}

void circles() {
  Serial.println("");
  Serial.println("Circles");

  // Initial positions to start drawing circles
  switch6 = 90;
  switch5 = 130;  // Base position - slightly rotate if needed for better motion
  switch4 = 90;   // Elbow - mid position
  switch3 = 90;   // Wrist - starting position
  moveServos();
  delay(1000);  // Wait a bit before starting the circles

  float previousValue = smoothing;
  smoothing = previousValue * 25;

  for (int i = 0; i < 5; i++) {                      // Draw 5 circles
    for (int angle = 0; angle < 360; angle += 10) {  // Complete a circle in steps
      // Simulate circular motion by adjusting elbow and wrist
      switch4 = 90 + 10 * cos(angle * PI / 180);  // Elbow - adjust for circular motion
      switch3 = 90 + 10 * sin(angle * PI / 180);  // Wrist - adjust for circular motion

      // Optionally, slightly rotate the base to enhance the circular drawing effect
      switch5 = 90 + 10 * cos(angle * PI / 180);  // Base - slight rotation
      switch6 = 90 + 30 * sin(angle * PI / 180);  // Base - slight rotation

      moveServos();
    }
  }
  smoothing = previousValue;
}

void worm() {
  Serial.println("");
  Serial.println("Worm");

  switch6 = 90;
  switch5 = 130;
  switch4 = 90;
  switch3 = 90;
  moveServos();
  delay(1000);

  float previousValue = smoothing;
  smoothing = 0.50;

  for (int i = 0; i < 5; i++) {  // Draw 5 circles
    for (int angle = 0; angle < 360; angle += 10) {

      switch4 = 90 + 30 * cos(angle * PI / 180);
      switch3 = 90 + 30 * sin(angle * PI / 180);
      switch5 = 90 + 15 * sin(angle * PI / 180);

      moveServos();
    }
  }
  smoothing = previousValue;
}

void diagonals() {
  Serial.println("");
  Serial.println("Diagonals");

  switch6 = 90;
  switch5 = 130;  // Base position - slightly rotate if needed for better motion
  switch4 = 90;   // Elbow - mid position
  switch3 = 90;   // Wrist - starting position
  moveServos();
  delay(1000);  // Wait a bit before starting the circles

  float previousValue = smoothing;
  smoothing = 0.50;

  for (int i = 0; i < 5; i++) {  // Draw 5 circles
    for (int angle = 0; angle < 360; angle += 10) {

      switch3 = 90 + 15 * sin(angle * PI / 180);
      switch6 = 90 + 30 * sin(angle * PI / 180);
      moveServos();
    }
  }
  smoothing = previousValue;
}

void screwdriver() {

  Serial.println("");
  Serial.println("Screw Driver");
  gripper = 180;
  switch2 = 90;
  switch3 = 180;
  switch4 = 140;
  switch5 = 45;
  switch6 = 0;
  moveServos();

  switch3 = 160;
  switch4 = 120;
  switch5 = 30;
  moveServos();

  gripper = 0;
  moveServos();

  smoothing = 0.01;
  delay(500);

  switch4 = 140;
  switch5 = 45;
  moveServos();

  switch3 = 70;
  switch4 = 90;
  switch5 = 110;
  switch6 = 90;
  moveServos();
  delay(1000);

  gripper = 0;
  switch2 = 90;
  switch3 = 120;
  switch4 = 90;
  switch5 = 110;
  switch6 = 90;
  moveServos();

  gripper = 180;
  moveServos();

  smoothing = 0.03;
}

void demo() {
  home();
  ready();
  home();
  ready();
  home();
  ready();
  home();
  diagonals();
  worm();
  circles();
}