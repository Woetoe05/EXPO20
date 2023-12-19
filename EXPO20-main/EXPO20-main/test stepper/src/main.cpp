#include <Arduino.h>

#define dirPin 7
#define stepPin 6
const int stepsPerRevolution = 200;
const int rotationSpeed = 10000;
const int angle = 180;

long rotate(long degrees)
{
    int steps = map(degrees, 0, 360, 0, 200);
    return steps;    
}

void stepperForward()
{
    // Set motor direction clockwise
    digitalWrite(dirPin, HIGH);
 
    // Spin motor
    for(int x = 0; x < rotate(angle); x++)
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
    for(int x = 0; x < rotate(angle); x++)
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
    delay(100);
}
