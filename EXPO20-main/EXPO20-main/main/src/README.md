# what the files do

## main.cpp

This is where most variables are declared and here is the setup() initialised and is void loop() running.

then is this the info the customer gets before the module starts
```cpp
void loop(){
  Serial.print("press '!' to start order.");
  Serial.print("give amount in multiplication of 50grams.");
  Serial.print("You have 5 seconds after you typ '!'");
  //while customer hasnt enterd an amount
  while (wantedAmount <= 0){
    //instructions for customer(more needed)
    accepted = false;
    start = Serial.read();//start scanning
```
when the customer has started it with '!' then:

the amount of grams is asked with a timeframe of 5 seconds
```cpp
    if (start == '!'){
      //ask for input
      Serial.println("How many grams do you want?");
      wantedAmount = Serial.parseInt();

      Serial.setTimeout(50000);//give 5 seconds to react
      Serial.print(wantedAmount);
      Serial.println("done!");
      delay(2000);
```

when the customer is too slow it will start over
```cpp
      if (wantedAmount==0){
        Serial.println("too late, start over.");
        Serial.print("press '!' to start order.");
        Serial.print("give amount in multiplication of 50grams.");
        Serial.print("You have 5 seconds after you typ '!'");
      }
```
If the customer exceeds the limits it will correct to its limits.
```cpp
       //if it exceeded limit, limit it 
      else if (wantedAmount>= 1000){
        wantedAmount = 1000;//grams
      }
      else if(wantedAmount<=50 && wantedAmount > 0){
        wantedAmount = 50;//grams
      }
      Serial.println(wantedAmount);
    
```

If the user isn't satisfied with their amount of grams then they can 
```cpp
      if(wantedAmount>0){
        Serial.print("Is this the amount you wanted? ");
        Serial.print(wantedAmount);
        Serial.println(" grams.");
        Serial.println("answer with y/n");
        char choice = 'c';
        while(choice != 'y' || choice != 'n'){
          choice = Serial.read();
          if (choice == 'n'){
            wantedAmount = 0;
            Serial.print("press '!' to start order.");
            Serial.print("give amount in multiplication of 50grams.");
            Serial.print("You have 5 seconds after you typ '!'");
          }
        }
      }
    }
  }
```

scale is reset to 0 grams.
```cpp
  Serial.print("remove everything from the scale.");
  delay(3000);
  LoadCell.tareNoDelay();
  Serial.print("Place your container on the scale");
  delay(3000);
```

While the currentAmount hasnt reached the wantedAmount keep filling the container/bag.
```cpp
  while (currentAmount < wantedAmount){
```

update scale
```cpp
    LoadCell.update();
    currentAmount = LoadCell.getData();//
    Serial.println(currentAmount);
```

open the screw
```cpp
    ServoScrew.write(open);
```

get the RPM depending on how full it is. see 'changeState.cpp'
```cpp
    int RPM = whichState(currentAmount, wantedAmount, minimumCE);
```

the RPM is used with the stepperForward(RPM) to change the speed. see 'speed.cpp'
```cpp
    stepperForward(RPM);
    if (RPM == 0){
      //close all servo's
      ServoScrew.write(close);
      //finished state
      break;
    }
    //stepsDone = myStepper.currentPosition();
  }
```

at the end the amounts are displayed and compared with eachother. To check if the tolerance is ok.
```cpp
  Serial.print("This is the amount you got dispensed: ");
  Serial.println(currentAmount);
  Serial.print("This is the amount you wanted: ");
  Serial.println(wantedAmount);
  currentAmount = 0;
  wantedAmount = 0;
  LoadCell.tareNoDelay();
  LoadCell.refreshDataSet();
  LoadCell.getData();
  LoadCell.tareNoDelay();
}
```

## calculations.h
here are all the functions

## changeState.cpp
here it changes the state to change the speed later.
```
int whichState(double currentAmount, double wantedAmount, double minimumCE){
  
  if (currentAmount <= 0.8*wantedAmount && currentAmount >= 0.5*wantedAmount && wantedAmount <= 400){
    return 40;
  } 
  else if (currentAmount <= 0.8*wantedAmount){//normal speed under risk amount
    return 100;
  }
  else if (currentAmount >= wantedAmount){//stop when above wanted amount
    return 0;
  }
  else if (currentAmount >= minimumCE){//slow down a lot when in CE range
    return 5;
  }
  else if (currentAmount >= 0.8*wantedAmount){//slower speed above risk amount
    return 20;
  }
  
  
  return 0;
}
```
## Speed.cpp
here it changes the speed according to states.

convert degrees to steps
```
long degreesToSteps(long degrees)
{
    int steps = map(degrees, 0, 360, 0, 200);
    return steps;    
}
```
uses the rpm from the state to change the speed of the stepper motor
```
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
```
