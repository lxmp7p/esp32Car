#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include "ServoController.h"
#include "WheelController.h"
#include "creds.h"
#include "frontend.h"

ServoController horizontalServo(19, 30, 90);
ServoController verticalServo(18, 30, 0);

WebServer server(80);

WheelController wheelA(17, 16);
WheelController wheelB(23, 22);
WheelController wheelC(26, 25);
WheelController wheelD(32, 33);

void runWenicle(int pin) {
  delay(100);
  digitalWrite(pin, HIGH);
  Serial.print(">>> КОЛЕСО ВКЛ, пин: ");
  Serial.println(pin);
}

void stop() {
  wheelA.stop();
  wheelB.stop();
  wheelC.stop();
  wheelD.stop();
  server.send(200, "text/plain", "STOP");
}

void runForward() {
  stop();
  wheelA.startForward();
  wheelC.startForward();
  delay(100);
  wheelB.startForward();
  wheelD.startForward();
  server.send(200, "text/plain", "RUN FORWARD");
}

void runBack() {
  stop();
  wheelA.startBack();
  wheelC.startBack();
  delay(100);
  wheelB.startBack();
  wheelD.startBack();
  server.send(200, "text/plain", "RUN BACK");
}

void runRight() {
  stop();
  wheelA.startBack();
  wheelB.startBack();
  delay(100);
  wheelC.startForward();
  wheelD.startForward();
  server.send(200, "text/plain", "RIGHT");
}

void runLeft() {
  stop();
  wheelC.startBack();
  wheelD.startBack();
  delay(100);
  wheelA.startForward();
  wheelB.startForward();
  server.send(200, "text/plain", "LEFT");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  wheelA.begin();
  wheelB.begin();
  wheelC.begin();
  wheelD.begin();

  horizontalServo.begin();
  verticalServo.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.on("/", []() {
    server.send(200, "text/html", INDEX_HTML);
  });

  server.on("/forward", runForward);
  server.on("/back", runBack);
  server.on("/left", runLeft);
  server.on("/right", runRight);
  server.on("/stop", stop);

  server.on("/run_a",  HTTP_GET, []() { 
    wheelA.startForward();
    server.send(200, "text/plain", "run A");
  });
  server.on("/run_b",  HTTP_GET, []() { 
    wheelB.startForward();
    server.send(200, "text/plain", "run B");
  });
  server.on("/run_c",  HTTP_GET, []() { 
    wheelC.startForward();
    server.send(200, "text/plain", "run C");
  });
  server.on("/run_d",  HTTP_GET, []() { 
    wheelD.startForward();
    server.send(200, "text/plain", "run D");
  });

  server.on("/camera_left",  HTTP_GET, []() {
     horizontalServo.left();
     server.send(200, "text/plain", "Horizontal: left");
  });
  server.on("/camera_right",  HTTP_GET, []() {
     horizontalServo.right();
     server.send(200, "text/plain", "Horizontal: right");
  });

  server.on("/camera_down",  HTTP_GET, []() {
     verticalServo.left();
     server.send(200, "text/plain", "Vertical: left");
  });
  server.on("/camera_up",  HTTP_GET, []() {
     verticalServo.right();
     server.send(200, "text/plain", "Vertical: left");
  });


  Serial.println("=== ТЕСТ МОТОРА ===");
  Serial.println("Мотор будет включаться на 2 сек и выключаться на 2 сек");
  Serial.println();
  server.begin(); 
  Serial.println("HTTP-сервер запущен");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}
