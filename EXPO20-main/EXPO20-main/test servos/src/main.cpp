//ready not safe STATE
#include <Arduino.h>
#include <Servo.h>
using namespace std;

//Servo's
Servo ServoScrew;
Servo ServoValve;
val = 30;
//code-------------------------------------------------------------|

void setup() {
  ServoScrew.attach(8);
  ServoValve.attach(9);
}

void loop() {
  myservo.write(0);                  // sets the servo position according to the scaled value
  delay(15);          
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
