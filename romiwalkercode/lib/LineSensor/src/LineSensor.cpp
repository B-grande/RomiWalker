#include "LineSensor.h"

#define DARK_THRESHOLD 700;

void LineSensor::Initialize(void)
{
    pinMode(firstSensorPin, INPUT);
    pinMode(secondSensorPin, INPUT);
    pinMode(thirdSensorPin, INPUT);
    pinMode(fourthSensorPin, INPUT);
    pinMode(fifthSensorPin, INPUT);
    pinMode(sixthSensorPin, INPUT);
}

float LineSensor::CalcError(void) 
{ 
    // return analogRead(leftSensorPin) - analogRead(secondSensorPin); 
    const int sensorPins[6] = {firstSensorPin, secondSensorPin, thirdSensorPin, fourthSensorPin, fifthSensorPin, sixthSensorPin};
    // const float weights[6] = {-1.5, -1.0, -0.5, 0.5, 1, 1.5};
    const float weights[6] = {-2.5, -2, -1, 1, 2, 2.5}; 
    float weightedSum = 0, totalSum = 0;

    for (int i = 0; i < 6; i++) {
        float sensorValue = analogRead(sensorPins[i]);
        weightedSum += sensorValue * weights[i];
        totalSum += sensorValue;
    }

    if (totalSum == 0) {return 0;}
    return (weightedSum / totalSum);
}
    

bool LineSensor::CheckIntersection(void)
{
    bool retVal = false;

    bool isLeftDark = analogRead(firstSensorPin) < DARK_THRESHOLD;
    bool isRightDark = analogRead(sixthSensorPin) < DARK_THRESHOLD;

    bool onIntersection = isLeftDark && isRightDark;
    

    if (onIntersection && !prevOnIntersection){
        
        retVal = true;
        prevOnIntersection = true;
    } else if (!onIntersection){
        prevOnIntersection = false;
    } 

    return retVal;
}