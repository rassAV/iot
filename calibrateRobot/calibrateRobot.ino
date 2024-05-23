#define DIR_RIGHT 4 // HIGH LOW или вперёд или назад
#define DIR_LEFT 7 // HIGH LOW или вперёд или назад
#define SPEED_RIGHT 5
#define SPEED_LEFT 6

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

int speed = 255;
int calibrateSpeed = 0;
bool rightWheel = true;
bool leftWheel = true;
int step = 1;

void setup() {
  for (int i = 2; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println();
  Serial.println("START calibration high/low");
}

void loop() {
  if (mySerial.available()) {
    int btn = mySerial.read();

    if (btn == 70) {
      move(rightWheel, leftWheel, speed, speed - calibrateSpeed);
    }
    if (btn == 76) {
      move(!rightWheel, leftWheel, speed, speed - calibrateSpeed);
    }
    if (btn == 82) {
      move(rightWheel, !leftWheel, speed, speed - calibrateSpeed);
    }
    if (btn == 66) {
      move(!rightWheel, !leftWheel, speed, speed - calibrateSpeed);
    }
    if (btn == 48) {
      stop();
    }

    if (btn == 83 && step == 0) {
      leftWheel = true;
      step = 1;
      Serial.println("high/low changed");
    } else if (btn == 83 && step == 1) {
      rightWheel = false;
      step = 2;
      Serial.println("high/low changed");
    } else if (btn == 83 && step == 2) {
      leftWheel = false;
      step = 3;
      Serial.println("high/low changed");
    } else if (btn == 83 && step == 3) {
      rightWheel = true;
      step = 0;
      Serial.println("high/low changed");
    }

    if (btn == 67) {
      step = 10;
      Serial.println("START speed calibration");
    }

    if (btn == 83 & step == 10) {
      calibrateSpeed += 1;
      if (calibrateSpeed > 230) calibrateSpeed = 230;
      Serial.print("speed calibration state = ");
      Serial.println(calibrateSpeed);
    }
    if (btn == 67 & step == 10) {
      calibrateSpeed -= 1;
      if (calibrateSpeed < 0) calibrateSpeed = 0;
      Serial.print("speed calibration state = ");
      Serial.println(calibrateSpeed);
    }
  }
}

void move(bool lforward, bool rforward, int lspeed, int rspeed) {
  digitalWrite(DIR_RIGHT, rforward);
  digitalWrite(DIR_LEFT, lforward);
  analogWrite(SPEED_RIGHT, rspeed);
  analogWrite(SPEED_LEFT, lspeed);
}

void stop() {
  move(rightWheel, leftWheel, 0, 0);
}
