//ready not safe STATE
#include <Arduino.h>
#include <Servo.h>
#include <AccelStepper.h>
#include <Calculations.h> 
using namespace std;

//Servo's
Servo ServoScrew;
Servo ServoValve;


//Stepper motor
const int dirPin = 7;
const int stepPin = 6;
#define stepperEnable 26

const int stepsPerRevolution = 200;
const int RPM = 65;
const float rotationSpeed = (((60*1000000)/RPM)/200)/2;//delay in microseconds

const int angle = 360;

// constants
int stepsDone = 0;


// variabels
double wantedAmount = 0;
double currentAmount = 0;
double minimumCE;
//code-----------------------------------------------------------------------|


void setup() {
  delay(1000);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepperEnable, OUTPUT);   
  digitalWrite(stepperEnable, LOW);
  Serial.begin(9600);
  //close all servos-->
  //calibrate sensors-->
  //stepper motor still-->
  //ready safe STATE-->
}

void loop() {
  while (wantedAmount <= 0){
    Serial.print("How much do you want? (patches of 50g)");
    wantedAmount = Serial.read();
  }
  
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
    //stepsDone = myStepper.currentPosition();
  }
  Serial.print("This is the amount you got dispensed: ");
  Serial.println(currentAmount);
  wantedAmount = 0;
}
