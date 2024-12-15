#pragma once

#include <Arduino.h>

#define sensorPin1 A0
#define sensorPin2 A1
#define sensorPin3 A2
#define sensorPin4 A3
#define sensorPin5 A4
#define sensorPin6 A6

class LineSensor
{
protected:
    uint8_t firstSensorPin = sensorPin1;
    uint8_t secondSensorPin = sensorPin2;
    uint8_t thirdSensorPin = sensorPin3;
    uint8_t fourthSensorPin = sensorPin4;
    uint8_t fifthSensorPin = sensorPin5;
    uint8_t sixthSensorPin = sensorPin6;


    bool prevOnIntersection = false;

public:
    LineSensor(void) {}
    void Initialize(void);
    float CalcError(void);
    bool CheckIntersection(void);
};