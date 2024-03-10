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
  // Increase from 1500 to 2000
  for (int pulseWidth = 1500; pulseWidth <= 2000; pulseWidth += 50) {
    Serial.print("Increasing high signal to: ");
    Serial.print(pulseWidth);
    if (pulseWidth > 1500) {
      Serial.println(" microseconds, counterclockwise rotation");
    } else {
      Serial.println(" microseconds, neutral position");
    }
    
    esc.writeMicroseconds(pulseWidth); // Set the pulse width
    delay(1000); // Stay on each PWM for 1 second
  }

  // Decrease from 2000 to 1000
  for (int pulseWidth = 1950; pulseWidth >= 1000; pulseWidth -= 50) {
    Serial.print("Decreasing high signal to: ");
    Serial.print(pulseWidth);
    if (pulseWidth >= 1500) {
      Serial.println(" microseconds, counterclockwise rotation");
    } else {
      Serial.println(" microseconds, clockwise rotation");
    }
    
    esc.writeMicroseconds(pulseWidth); // Set the pulse width
    delay(1000); // Stay on each PWM for 1 second
  }
}
