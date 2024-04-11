#define ENA1 3
#define DIR1A 4
#define DIR1B 5

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set motor control pins as outputs
  pinMode(ENA1, OUTPUT);
  pinMode(DIR1A, OUTPUT);
  pinMode(DIR1B, OUTPUT);

  // Optional: Print a start message
  Serial.println("Motor control program started");
}

void loop() {
  // Example to control the motor speed and direction
  controlWheel(ENA1, DIR1A, DIR1B, 200); // Move forward with speed 200
  delay(5000); // Wait for 5 seconds

  controlWheel(ENA1, DIR1A, DIR1B, -150); // Move backward with speed 150
  delay(5000); // Wait for 5 seconds

  // Add more control logic as needed
}

void controlWheel(int enaPin, int dirPin1, int dirPin2, int speed) {
  bool direction = speed >= 0;
  speed = abs(speed);
  if (speed > 255) speed = 255; // Limit speed to PWM range

  digitalWrite(dirPin1, direction ? HIGH : LOW);
  digitalWrite(dirPin2, !direction ? HIGH : LOW);
  analogWrite(enaPin, speed);
}
