#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("OneRing","RJ");
//variable declaration for control purposes
int typed;
//int battery = 100;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting serial Capture in ESP32");
  bleKeyboard.begin();
  typed = 0;
}

void loop() {
  if(bleKeyboard.isConnected()){
    
  }
}