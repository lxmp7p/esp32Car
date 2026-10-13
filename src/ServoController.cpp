#include "ServoController.h"

ServoController::ServoController(int pinNumber, int step, int startAngle) {
    pin = pinNumber;
    rotateStep = step;
    defaultAngle = startAngle;
}

void ServoController::begin() {
    servo.attach(pin);
    servo.write(defaultAngle);
};

void ServoController::rotate(int angle) {
    if (angle > maxServoAngle) {
      angle = maxServoAngle;
    }
    if (angle < minServoAngle) {
      angle = minServoAngle;
    }
    servo.write(angle);
};

int ServoController::getAngle() {
    return servo.read();
};

void ServoController::right() {
    int currentAngle = getAngle();
    rotate(currentAngle+rotateStep);
};

void ServoController::left() {
    int currentAngle = getAngle();
    rotate(currentAngle-rotateStep);
};
