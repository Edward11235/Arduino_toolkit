#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(0);              // tell servo to go to position in variable 'pos'
  delay(5000);
}

void loop() {
  for (int pos = 0; pos <= 180; pos += 20) { // goes from 0 degrees to 180 degrees
    // in steps of 10 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1000);                     // waits 1s for the servo to reach the position
  }
  
}
