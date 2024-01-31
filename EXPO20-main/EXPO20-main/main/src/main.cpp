//ready not safe STATE
#include <Arduino.h>
#include <Servo.h>
#include <AccelStepper.h>
#include <Calculations.h> 
using namespace std;

//Servo's
Servo ServoScrew;
Servo ServoValve;


//Arm define
int moveDir = 1;
const float stepsPerDeg = (6400.0/360.0); // 6400 = 360 deg
const float degPerStep = (360.0/6400.0);

//Stepper motor
const int dirPin = 7;
const int stepPin = 6;
#define stepperEnable 26
#define motorInterfaceType 1
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);
bool stopped = false;

// constants
int stepsDone = 0;
int normalSpeed = 50;
int slowSpeed = 10;
int stopSpeed = 0;

// variabels
double wantedAmount;
double currentAmount = 0;
double minimumCE;
//code-------------------------------------------------------------|

//Alles van Arm----------------------------------------------------|
void runSpeed(int neededSpeed){
  myStepper.setSpeed(normalSpeed);
  myStepper.runSpeed();
}
void switchSpeed(int theState){
  switch (theState)
    {
    case 10:
      runSpeed(normalSpeed);
      break;
    case 20:
      runSpeed(slowSpeed);
      break;
    case 30:
      runSpeed(stopSpeed);
      //close all servo's-->
      break;
    case 0:
      //emergency stop
      break;
    default:
      break;
    }
    
}
//Alles van weight-------------------------------------------------|


void setup() {
   //Arm void setup----------------------------------------------------------|
  delay(1000);
  myStepper.setMaxSpeed(1000);
  myStepper.setAcceleration(1000);
  myStepper.setCurrentPosition(0);
  pinMode(stepperEnable, OUTPUT);   
  digitalWrite(stepperEnable, LOW);
  Serial.begin(9600);
  //close all servos-->
  //calibrate sensors-->
  //stepper motor still-->
  //ready safe STATE-->
}

void loop() {
  wantedAmount = Serial.read();
  minimumCE = 0.98 *wantedAmount;
  //dispensing STATE
  //check if there is a bag | not necesserry for our project-->
  while (currentAmount < minimumCE){
    currentAmount = checkCurrentAmount(currentAmount);
    int theState = whichState(currentAmount, wantedAmount, minimumCE);
    switchSpeed(theState);
    if (theState == 30){
      //close all servo's
      //finished state
      break;
    }
    stepsDone = myStepper.currentPosition();
  }
  Serial.print("This is the amount you got dispensed: ");
  Serial.println(currentAmount);

}
