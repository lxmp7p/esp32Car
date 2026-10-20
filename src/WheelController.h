#pragma once
#include <Arduino.h>


class WheelController {
private:
    int pinForward;
    int pinBack;

public:
    WheelController(int pinForward, int pinBack);
    void begin();
    void startForward();
    void startBack();
    void stop();
};