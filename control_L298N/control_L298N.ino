#define ENA 8   // Define ENA pin connected to PWM
#define INT1 10 // Define INT1 pin
#define INT2 9  // Define INT2 pin

void setup() {
  // Set motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(INT1, OUTPUT);
  pinMode(INT2, OUTPUT);

  // Initialize the motor direction
  digitalWrite(INT1, HIGH);  // Set INT1 low
  digitalWrite(INT2, LOW); // Set INT2 high to define motor direction
}

void loop() {
  // Increase speed
  for (int speed = 0; speed <= 255; speed += 5) {
    analogWrite(ENA, speed); // Set motor speed
    delay(30);               // Short delay to see the speed increase effect
  }

  // Decrease speed
  for (int speed = 255; speed >= 0; speed -= 5) {
    analogWrite(ENA, speed); // Set motor speed
    delay(30);               // Short delay to see the speed decrease effect
  }

  delay(1000); // Wait for a second before the next speed cycle begins
}
