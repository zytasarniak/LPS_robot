#include <Arduino.h>
#include "motors.h"

// ===== Sterownik 1 (tył) =====
int IN1 = 25;
int IN2 = 26;
int ENA = 33;

int IN3 = 27;
int IN4 = 14;
int ENB = 32;

// ===== Sterownik 2 (przód) =====
int IN5 = 22;
int IN6 = 21;
int ENA2 = 23;

int IN7 = 19;
int IN8 = 18;
int ENB2 = 5;

// ===== Odwracanie kierunków =====
bool REVERSE_REAR_LEFT = false;
bool REVERSE_REAR_RIGHT = true;
bool REVERSE_FRONT_LEFT = true;
bool REVERSE_FRONT_RIGHT = false;

void setRear(int a1, int a2, int sp1, int b1, int b2, int sp2) {
  if(REVERSE_REAR_LEFT){ int t=a1; a1=a2; a2=t; }
  if(REVERSE_REAR_RIGHT){ int t=b1; b1=b2; b2=t; }

  digitalWrite(IN1, a1); 
  digitalWrite(IN2, a2); 
  analogWrite(ENA, sp1);
  
  digitalWrite(IN3, b1); 
  digitalWrite(IN4, b2); 
  analogWrite(ENB, sp2);
}

void setFront(int a1, int a2, int sp1, int b1, int b2, int sp2) {
  if(REVERSE_FRONT_LEFT){ int t=a1; a1=a2; a2=t; }
  if(REVERSE_FRONT_RIGHT){ int t=b1; b1=b2; b2=t; }

  digitalWrite(IN5, a1); 
  digitalWrite(IN6, a2); 
  analogWrite(ENA2, sp1);
  
  digitalWrite(IN7, b1); 
  digitalWrite(IN8, b2); 
  analogWrite(ENB2, sp2);
}

void initMotors(){
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(ENA, OUTPUT);
  
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  pinMode(ENB, OUTPUT);

  pinMode(IN5, OUTPUT); 
  pinMode(IN6, OUTPUT); 
  pinMode(ENA2, OUTPUT);
  
  pinMode(IN7, OUTPUT); 
  pinMode(IN8, OUTPUT); 
  pinMode(ENB2, OUTPUT);

  stopAll();

}

void stopAll() {
  setRear(0,0,0, 0,0,0);
  setFront(0,0,0, 0,0,0);
}

void forward() {
  setRear(HIGH, LOW, 255, HIGH, LOW, 255);
  setFront(HIGH, LOW, 255, HIGH, LOW, 255);
}

void backward() {
  setRear(LOW, HIGH, 255, LOW, HIGH, 255);
  setFront(LOW, HIGH, 255, LOW, HIGH, 255);
}

void turnLeft() {
  setRear(LOW, HIGH, 255, HIGH, LOW, 255);
  setFront(HIGH, LOW, 255, LOW, HIGH, 255);
}

void turnRight() {
  setRear(HIGH, LOW, 255, LOW, HIGH, 255);
  setFront(LOW, HIGH, 255, HIGH, LOW, 255);
}