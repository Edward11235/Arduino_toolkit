const int receiverPin = 7;  // Pin connected to the receiver channel
unsigned long duration;
const int threshold = 1500; // Adjust based on your signal characteristics

void setup() {
  Serial.begin(9600);
  pinMode(receiverPin, INPUT);
}

void loop() {
  duration = pulseIn(receiverPin, HIGH);

  Serial.println(duration);
  
  if (duration > threshold) {
    Serial.println("EMERGENCY");
  }
  
  delay(100); // Adjust the delay as needed
}
