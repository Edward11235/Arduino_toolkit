/*
For my bidirectional esc, I found that:
PWM from 1500 to 2000 is counterclockwise rotation
PWM from 1000 to 1500 is clockwise rotation
PWM 1500 is no rotation neutral state
delay 5 second in the setup() to enable the esc
*/
#include <Servo.h>

Servo esc; // Create a servo object to control the ESC
int escPin = 9; // ESC control pin

void setup() {
  esc.attach(escPin); // Attaches the ESC on pin 9 to the servo object
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  
  // Send initial signal to arm the ESC
  esc.writeMicroseconds(1500); // Neutral position for arming, usually 1500 microseconds
  delay(5000); // Wait a bit after sending the arm signal
}

void loop() {
  int pulseWidth = 1450;
  Serial.print("Decreasing high signal to: ");
  Serial.print(pulseWidth);
  Serial.println(" microseconds, counterclockwise rotation");
  esc.writeMicroseconds(pulseWidth); // Set the pulse width
  delay(10000); // Short delay for gradual decrease

  pulseWidth = 1500;
  Serial.print("Decreasing high signal to: ");
  Serial.print(pulseWidth);
  Serial.println(" microseconds, counterclockwise rotation");
  esc.writeMicroseconds(pulseWidth); // Set the pulse width
  delay(10000); // Short delay for gradual decrease
}
