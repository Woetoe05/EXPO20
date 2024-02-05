#include <Calculations.h>
#include <Arduino.h>

#define dirPin 7
#define stepPin 6
const int stepsPerRevolution = 200;
//const int RPM = 65;


const int angle = 9;
long degreesToSteps(long degrees)
{
    int steps = map(degrees, 0, 360, 0, 200);
    return steps;    
}
void stepperForward(int RPM)
{
    digitalWrite(dirPin, HIGH);
    float rotationSpeed = (((60*1000000)/RPM)/200)/2;//delay in microseconds
    // Set motor direction counterclockwise
    
    Serial.print("speed: ");
    Serial.println(rotationSpeed);
    // Spin motor
    for(int x = 0; x < degreesToSteps(angle); x++)
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(rotationSpeed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(rotationSpeed);
    }
}
