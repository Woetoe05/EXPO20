# what the files do

## main.cpp

This is where most variables are declared and here is the setup() initialised and is void loop() running.

then is this the info the customer gets before the module starts
```
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
```
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
```
      if (wantedAmount==0){
        Serial.println("too late, start over.");
        Serial.print("press '!' to start order.");
        Serial.print("give amount in multiplication of 50grams.");
        Serial.print("You have 5 seconds after you typ '!'");
      }
```
If the customer exceeds the limits it will correct to its limits.
```
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
```
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
```
  Serial.print("remove everything from the scale.");
  delay(3000);
  LoadCell.tareNoDelay();
  Serial.print("Place your container on the scale");
  delay(3000);
```

While the currentAmount hasnt reached the wantedAmount keep filling the container/bag.
```
  while (currentAmount < wantedAmount){
```

update scale
```
    LoadCell.update();
    currentAmount = LoadCell.getData();//
    Serial.println(currentAmount);
```

open the screw
```
    ServoScrew.write(open);
```

get the RPM depending on how full it is. see 'changeState.cpp'
```
    int RPM = whichState(currentAmount, wantedAmount, minimumCE);
```

the RPM is used with the stepperForward(RPM) to change the speed. see 'speed.cpp'
```
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
```
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

## changeState.cpp

## Speed.cpp

