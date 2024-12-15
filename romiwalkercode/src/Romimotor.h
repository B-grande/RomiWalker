#pragma once

#include <Arduino.h>
#include "servo32u4.h"

class RomiMotor
{
public:
    RomiMotor();
    void initESC();               // Initialize the ESCs
    void setSpeed(int16_t speed); // Set speed: -100 to 100
    void turn(int16_t angle);     // Turn by angle in degrees


private:
    Servo32U4Pin9 servoLeft;
    Servo32U4Pin10 servoRight;
};