//ready not safe STATE
#include <Arduino.h>
#include <Servo.h>
#include <AccelStepper.h>
#include <Calculations.h> 

#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif
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


// variabels amounts
int wantedAmount = 0;
double currentAmount = 0;
double minimumCE;

//scale
const int HX711_dout = 3; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;
int weight = 0;
//code-----------------------------------------------------------------------|


void setup() {
  delay(1000);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepperEnable, OUTPUT);   
  digitalWrite(stepperEnable, LOW);
  //Serial.begin(9600);

  //begin scale:---------------------------------------------------------------------------------------------------------------
  Serial.begin(57600); delay(10);
  Serial.println();
  Serial.println("Starting...");
  LoadCell.begin();
  LoadCell.setSamplesInUse(4);
  //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  
  if (LoadCell.getTareTimeoutFlag() || LoadCell.getSignalTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(483.82); // +- 0.05
    Serial.println("Startup scale is complete");
  }
  //while (!LoadCell.update());
  //calibrate(); //start calibration procedure
  //end scale---------------------------------------------------------------------------------------------------------------------
  
  //close all servos-->
  //calibrate sensors-->
  //stepper motor still-->
  //ready safe STATE-->
}
bool accepted = false;
byte start = ',';
//memset(inputSeveral, 0, sizeof(inputSeveral));
void loop() {
  Serial.print("press '!' to start order.");
  Serial.print("give amount in multiplication of 50grams.");
  //while customer hasnt enterd an amount
  while (wantedAmount <= 0){
    //instructions for customer(more needed)
    

    accepted = false;
    start = Serial.read();//start scanning
    if (start == '!'){
      //ask for input
      Serial.print("How many grams do you want?");
      wantedAmount = Serial.parseInt();
      Serial.setTimeout(5000);//give 5 seconds to react
      Serial.print("done!");
     
      if (wantedAmount==0){
        Serial.println("too late, start over.");
        Serial.print("press '!' to start order.");
        Serial.print("give amount in multiplication of 50grams.");
      }
       //if it exceeded limit, limit it 
      else if (wantedAmount>= 1000){
        wantedAmount = 1000;//grams
      }
      else if(wantedAmount<=50){
        wantedAmount = 50;//grams
      }
      Serial.println(wantedAmount);
    }
  }
  Serial.print("This is the final amount you got dispensed:  ");
  Serial.println(wantedAmount);
  Serial.print("grams.");
  minimumCE = 0.98 *wantedAmount;
  
  //dispensing STATE
  //check if there is a bag | not necesserry for our project
  //when the bag is there, reset the scale and open the servos.--------->\/
  LoadCell.tareNoDelay();

  while (currentAmount < minimumCE){
    //weight = LoadCell.getData();\/
    currentAmount = LoadCell.getData();//
    Serial.println(currentAmount);
    int RPM = whichState(currentAmount, wantedAmount, minimumCE);
    stepperForward(RPM);
    if (RPM == 0){
      //close all servo's
      //finished state
      break;
    }
    //stepsDone = myStepper.currentPosition();
  }
  Serial.print("This is the amount you got dispensed: ");
  Serial.println(currentAmount);
  currentAmount = 0;
  wantedAmount = 0;
}
