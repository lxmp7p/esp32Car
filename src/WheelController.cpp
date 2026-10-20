#include "WheelController.h"

WheelController::WheelController(int pinForwardNumber, int pinBackNumber) {
    pinForward = pinForwardNumber;
    pinBack = pinBackNumber;
}

void WheelController::begin() {
    pinMode(pinForward, OUTPUT);
    pinMode(pinBack, OUTPUT);
    digitalWrite(pinForward, LOW);
    digitalWrite(pinBack, LOW);
    Serial.print("Колесо готово к работе. Pin Forward: ");
    Serial.print(pinForward);
    Serial.print(".Pin Back: " + pinBack);
    Serial.print(pinBack);
    Serial.print("\n");
};

void WheelController::startForward() {
    digitalWrite(pinBack, LOW);
    digitalWrite(pinForward, HIGH);
    Serial.print("Колесо крутится вперед. Pin Forward: ");
    Serial.print(pinForward);
    Serial.print(".Pin Back: " + pinBack);
    Serial.print(pinBack);
    Serial.print("\n");
}

void WheelController::startBack() {
    digitalWrite(pinForward, LOW);
    digitalWrite(pinBack, HIGH);
    Serial.print("Колесо крутится назад. Pin Forward: ");
    Serial.print(pinForward);
    Serial.print(".Pin Back: " + pinBack);
    Serial.print(pinBack);
    Serial.print("\n");
}

void WheelController::stop() {
    digitalWrite(pinForward, LOW);
    digitalWrite(pinBack, LOW);
    Serial.print("Колесо остановилось. Pin Forward: ");
    Serial.print(pinForward);
    Serial.print(".Pin Back: " + pinBack);
    Serial.print(pinBack);
    Serial.print("\n");
}