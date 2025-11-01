#include "TimerOne.h"

// Pin definitions for Traffic Light 1
int red1_d3 = A3;
int yellow1_d4 = 4;
int green1_d5 = 5;

// Pin definitions for Traffic Light 2
int red2_d6 = 6;
int yellow2_d7 = 7;
int green2_d8 = 8;

int red_pedestrian_d9 = 9;
int green_pedestrian_d10 = 10;
int red_pedestrian_d11 = 11;
int green_pedestrian_d12 = 12;

// Timing for the phases
#define BLINK_FREQUENCY 1          // Timer interval (1 second)
unsigned long previousMillis = 0;  // Stores the last time for phase change
int trafficLightStatus = 0;        // State of the traffic lights
int button1_c0 = 2;
int button2_c1 = 3;
bool pedestrianRequest1 = false;
bool pedestrianRequest2 = false;

void setup() {
  // Set pins as output
  pinMode(red1_d3, OUTPUT);
  pinMode(yellow1_d4, OUTPUT);
  pinMode(green1_d5, OUTPUT);

  pinMode(red2_d6, OUTPUT);
  pinMode(yellow2_d7, OUTPUT);
  pinMode(green2_d8, OUTPUT);

  pinMode(red_pedestrian_d9, OUTPUT);
  pinMode(green_pedestrian_d10, OUTPUT);
  pinMode(red_pedestrian_d11, OUTPUT);
  pinMode(green_pedestrian_d12, OUTPUT);

  pinMode(button1_c0, INPUT_PULLUP);
  pinMode(button2_c1, INPUT_PULLUP);

  // Start timer with 1-second interval
  Timer1.initialize(BLINK_FREQUENCY * 1000000);  // Initialize timer with 1 second
  Timer1.attachInterrupt(trafficLightPhases);   // Function for traffic light phase interrupt

  // Button interrupts for pedestrian requests
  attachInterrupt(digitalPinToInterrupt(button1_c0), buttonISR1, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2_c1), buttonISR2, FALLING);
}

// ISR for button interrupts (pedestrian requests)
void buttonISR1() {
  pedestrianRequest1 = true;
}

void buttonISR2() {
  pedestrianRequest2 = true;
}

// The function for traffic light phases
void trafficLightPhases() {
  unsigned long currentMillis = millis();
  switch (trafficLightStatus) {
    case 0:
      digitalWrite(red1_d3, HIGH);
      digitalWrite(red2_d6, HIGH);
      digitalWrite(red_pedestrian_d9, HIGH);
      digitalWrite(red_pedestrian_d11, HIGH);
      if (currentMillis - previousMillis >= 1000) {
        trafficLightStatus++;
        previousMillis = currentMillis;
      }
      break;

    case 1:
      digitalWrite(red1_d3, LOW);
      digitalWrite(yellow1_d4, HIGH);
      if (currentMillis - previousMillis >= 1000) {
        trafficLightStatus++;
        previousMillis = currentMillis;
      }
      break;

    case 2:
      digitalWrite(yellow1_d4, LOW);
      digitalWrite(green1_d5, HIGH);
      if (pedestrianRequest2 == true) {
        digitalWrite(red_pedestrian_d11, LOW);
        digitalWrite(green_pedestrian_d12, HIGH);
      }
      if (currentMillis - previousMillis >= 20000) {
        trafficLightStatus++;
        digitalWrite(red_pedestrian_d11, HIGH);
        digitalWrite(green_pedestrian_d12, LOW);
        pedestrianRequest2 = false;
        previousMillis = currentMillis;
      }
      break;

    case 3:
      digitalWrite(green1_d5, LOW);
      digitalWrite(yellow1_d4, HIGH);
      if (currentMillis - previousMillis >= 1000) {
        trafficLightStatus++;
        previousMillis = currentMillis;
      }
      break;

    case 4:
      digitalWrite(red1_d3, HIGH);
      if (currentMillis - previousMillis >= 1000) {
        trafficLightStatus++;
        previousMillis = currentMillis;
      }
      break;

    case 5:
      digitalWrite(yellow1_d4, LOW);
      if (currentMillis - previousMillis >= 5000) {
        trafficLightStatus++;
        previousMillis = currentMillis;
      }
      break;

    case 6:
      digitalWrite(red2_d6, LOW);
      digitalWrite(yellow2_d7, HIGH);
      if (currentMillis - previousMillis >= 1000) {
        trafficLightStatus++;
        previousMillis = currentMillis;
      }
      break;

    case 7:
      digitalWrite(yellow2_d7, LOW);
      digitalWrite(green2_d8, HIGH);
      if (pedestrianRequest1 == true) {
        digitalWrite(red_pedestrian_d9, LOW);
        digitalWrite(green_pedestrian_d10, HIGH);
      }
      if (currentMillis - previousMillis >= 15000) {
        digitalWrite(red_pedestrian_d9, HIGH);
        digitalWrite(green_pedestrian_d10, LOW);
        pedestrianRequest1 = false;
        trafficLightStatus++;
        previousMillis = currentMillis;
      }
      break;

    case 8:
      digitalWrite(green2_d8, LOW);
      digitalWrite(yellow2_d7, HIGH);
      if (currentMillis - previousMillis >= 1000) {
        trafficLightStatus++;
        previousMillis = currentMillis;
      }
      break;

    case 9:
      digitalWrite(red2_d6, HIGH);
      if (currentMillis - previousMillis >= 1000) {
        trafficLightStatus++;
        previousMillis = currentMillis;
      }
      break;

    case 10:
      digitalWrite(yellow2_d7, LOW);
      if (currentMillis - previousMillis >= 5000) {
        trafficLightStatus = 0;
        previousMillis = currentMillis;
      }
      break;
  }
}

void loop() {
  // Empty loop
}
