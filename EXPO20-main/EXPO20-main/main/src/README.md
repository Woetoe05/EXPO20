# what the files do

## main.cpp

This is where most variables are declared and here is the setup() initialised and is void loop() running.

then is this the info the user gets before the module starts
```
void loop():
  Serial.print("press '!' to start order.");
  Serial.print("give amount in multiplication of 50grams.");
  //while customer hasnt enterd an amount
  while (wantedAmount <= 0){
    //instructions for customer(more needed)
    accepted = false;
    start = Serial.read();//start scanning
    ...
    }
```

then ...

## calculations.h

## calculations.cpp

