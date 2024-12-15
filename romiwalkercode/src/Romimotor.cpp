// RomiMotor.cpp
#include "RomiMotor.h"

RomiMotor::RomiMotor()
{
    // Constructor implementation (if needed)
}

void RomiMotor::initESC()
{
    Serial.println("Initializing ESCs...");
    // Initialize the ESCs by attaching the servos and sending neutral signals
    servoLeft.attach();
    servoRight.attach();

    // Send neutral signal to initialize ESCs
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);

    delay(5000); // Extended delay to allow ESCs to arm

    Serial.println("ESCs Initialized.");
}

void RomiMotor::setSpeed(int16_t speed)
{
    // Clamp speed to -100 to 100
    speed = constrain(speed, -100, 100);

    // Map speed from -100 to 100 to pulse widths (1000 to 2000)
    uint16_t pulseLeft = map(speed, -100, 100, 1000, 2000);
    uint16_t pulseRight = map(speed, -100, 100, 2000, 1000); // Reverse for right motor

    Serial.print("Setting Speed: ");
    Serial.print(speed);
    Serial.print(" | Pulse Left: ");
    Serial.print(pulseLeft);
    Serial.print(" | Pulse Right: ");
    Serial.println(pulseRight);

    servoLeft.writeMicroseconds(pulseLeft);
    servoRight.writeMicroseconds(pulseRight);
}

void RomiMotor::turn(int16_t angle)
{
    // Simple turn implementation based on angle sign
    if (angle > 0)
    {
        // Turn right
        setSpeed(50);   // Adjust values as needed for turning
    }
    else if (angle < 0)
    {
        // Turn left
        setSpeed(-50);  // Adjust values as needed for turning
    }
    else
    {
        // Stop or go straight
        setSpeed(0);
    }
}