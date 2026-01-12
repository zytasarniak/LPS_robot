#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "motors.h"
#include "web_page.h"
#include "extras.h"

const char* ssid = "twojeid";
const char* password = "twojehaslo";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  initMotors();
  initExtras();
  
  Serial.println("Test buzzera...");
  beep(100);
  delay(100);
  beep(100);

  WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
}

Serial.print("IP ESP32: ");
Serial.println(WiFi.localIP());

if (MDNS.begin("robot")) {
  Serial.println("mDNS działa: http://robot.local");
}
    
  server.on("/", []() { server.send(200, "text/html", htmlPage); });
  server.on("/forward", []() { forward(); server.send(200); });
  server.on("/backward", []() { backward(); server.send(200); });
  server.on("/left", []() { turnLeft(); server.send(200); });
  server.on("/right", []() { turnRight(); server.send(200); });
  server.on("/stop", []() { setMode(MANUAL); stopAll(); server.send(200); });
  server.on("/miau", []() {miauEffect(); server.send(200);});

  server.on("/auto", []() {
    setMode(AUTO); 
    server.send(200, "text/plain", "AUTO MODE");
});

server.on("/manual", []() {
  setMode(MANUAL);
  server.send(200, "text/plain", "MANUAL MODE");
});

  server.begin();
  Serial.println("Serwer wystartował!");
}

void loop() {
  server.handleClient();
  runAutoModeLoop();

}