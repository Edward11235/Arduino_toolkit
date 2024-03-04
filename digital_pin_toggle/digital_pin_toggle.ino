void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH); // Set the pin high
  delay(1000);            // Wait for a second
  digitalWrite(13, LOW);  // Set the pin low
  delay(1000);            // Wait for a second
}
