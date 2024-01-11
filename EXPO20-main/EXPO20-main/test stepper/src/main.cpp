#include <Arduino.h>

#define dirPin 7
#define stepPin 6
const int stepsPerRevolution = 200;
const int RPM = 65;
const float rotationSpeed = (((60*1000000)/RPM)/200)/2;//delay in microseconds

const int angle = 360;

long degreesToSteps(long degrees)
{
    int steps = map(degrees, 0, 360, 0, 200);
    return steps;    
}

void stepperForward()
{
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH);
    Serial.print(rotationSpeed);
    // Spin motor
    for(int x = 0; x < degreesToSteps(angle); x++)
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(rotationSpeed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(rotationSpeed);
    }
}

void stepperBackward()
{
    // Set motor direction counterclockwise
    digitalWrite(dirPin, LOW);
 
    // Spin motor
    for(int x = 0; x < degreesToSteps(angle); x++)
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(rotationSpeed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(rotationSpeed);  
    }
}

void setup() {
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    Serial.begin(9600);
}

void loop() { 
    // Your loop code here, including calls to stepperForward, stepperBackward, etc.
    stepperForward();
    
}