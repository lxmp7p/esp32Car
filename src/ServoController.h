#pragma once

#include <ESP32Servo.h>

class ServoController {
private:
    Servo servo;
    int pin;
    int rotateStep;
    int defaultAngle;

    int maxServoAngle = 180;
    int minServoAngle = 0;

public:
    ServoController(int pinNumber, int step = 30, int defaultAngle=0);
    void begin();
    void rotate(int angle);
    int getAngle();
    void left();
    void right();
};