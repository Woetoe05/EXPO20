#include <Calculations.h>
//#include <AccelStepper.h>
//#include <main.cpp>
//int normalSpeed = 50;
//int slowSpeed = 10;
//int stopSpeed = 0;
//
//void runSpeed(int neededSpeed){
//  myStepper.setSpeed(neededSpeed);
//  myStepper.runSpeed();
//}
//
//void switchSpeed(int theState){
//  switch (theState)
//    {
//    case 10:
//      runSpeed(normalSpeed);
//      break;
//    case 20:
//      runSpeed(slowSpeed);
//      break;
//    case 30:
//      runSpeed(stopSpeed);
//      //close all servo's-->
//      break;
//    case 0:
//      //emergency stop
//      break;
//    default:
//      break;
//    }
//    
//}
#include <Arduino.h>

#define dirPin 7
#define stepPin 6
const int stepsPerRevolution = 200;
//const int RPM = 65;


const int angle = 5;
long degreesToSteps(long degrees)
{
    int steps = map(degrees, 0, 360, 0, 200);
    return steps;    
}
void stepperForward(int RPM)
{
    float rotationSpeed = (((60*1000000)/RPM)/200)/2;//delay in microseconds
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