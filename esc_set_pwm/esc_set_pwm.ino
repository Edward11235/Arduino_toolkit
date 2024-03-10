#include <Servo.h>

Servo esc; // Create a servo object to control the ESC
int escPin = 9; // ESC control pin

void setup() {
  esc.attach(escPin); // Attaches the ESC on pin 9 to the servo object
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  
  // It's essential to start with a known state; 1500 microseconds is typical for neutral.
  esc.writeMicroseconds(500); // Neutral position for arming, usually 1500 microseconds
  delay(5000); // Wait a bit after sending the arm signal
}

void loop() {
  // Iterate from 0 to 5000 in increments of 100
  for (int pulseWidth = 1400; pulseWidth <= 1600; pulseWidth += 10) {
    Serial.print("Setting pulse width to: ");
    Serial.println(pulseWidth);
    
    esc.writeMicroseconds(pulseWidth); // Set the pulse width
    delay(1000); // Wait for 1 second before changing the pulse width
  }

  // After reaching 5000, you might want to reset, pause, or stop. Adjust as necessary.
  delay(10000); // Example: Wait for 10 seconds before restarting the loop or add your logic here.
}
