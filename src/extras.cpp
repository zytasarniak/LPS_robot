#include <Arduino.h>
#include "extras.h"
#include "motors.h"

const int RED_LED_PIN = 4;
const int GREEN_LED_PIN = 16;
const int BLUE_LED_PIN = 17;

const int BUZZER_PIN = 13;

const int TRIG_PIN = 12;
const int ECHO_PIN = 34;

RobotMode currentMode = MANUAL;
const int OBSTACLE_DISTANCE_CM = 30; 

void initExtras() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
}

void setModeLed(RobotMode mode) {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, HIGH);

    if (mode == MANUAL) {
        digitalWrite(GREEN_LED_PIN, LOW);
    } 
    else if (mode == AUTO) {
        digitalWrite(BLUE_LED_PIN, LOW);
    }
}

void setMode(RobotMode newMode) {
    currentMode = newMode;

    stopAll();
    activateObstacleAlert(false);
    setModeLed(newMode); 

    Serial.printf(
        "Tryb zmieniony na: %s\n",
        (newMode == MANUAL ? "MANUALNY" : "AUTOMATYCZNY")
    );
}

void activateObstacleAlert(bool activate) {
    if (activate) {
        digitalWrite(RED_LED_PIN, LOW);
        digitalWrite(GREEN_LED_PIN, HIGH);
        digitalWrite(BLUE_LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
        setModeLed(currentMode);
    }
}

void beep(int durationMs) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(durationMs);
    digitalWrite(BUZZER_PIN, LOW);
}

void miauEffect() {
  int pattern[] = {100, 75, 50, 75, 100}; 
  for (int i = 0; i < 5; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(pattern[i]);  
    digitalWrite(BUZZER_PIN, LOW);
    delay(pattern[i]); 
  }
}

long measureDistance() {
digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);

    if (duration == 0) return 400; 
    
    long distance = duration * 0.034 / 2;
    
    return distance;
}

void runAutoModeLoop() {
    if (currentMode != AUTO) {
        return;
    }

long distance = measureDistance();
    
    if (distance > 0 && distance < OBSTACLE_DISTANCE_CM) {
        beep(200); 
        activateObstacleAlert(true);
        stopAll();
        delay(500);
        
        Serial.printf("Przeszkoda: %ld cm! Cofam.\n", distance);
        backward();
        delay(600);
        
        if (random(2) == 0) turnLeft(); else turnRight();
        delay(700); 

        stopAll();
        delay(200);
        activateObstacleAlert(false);
    } else {
        activateObstacleAlert(false);
        forward();
    }
    
    delay(50);
}