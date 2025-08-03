// FS-i6 Receiver Reader
// Simple program to read and print FS-i6 receiver values

#define CH1 3   // Right Stick Horizontal CHANEL 1 (left 1983, right 994)
#define CH2 5   // Throttle (Left Stick Vertical) CHANEL 3 (up 1010, down 1987)
#define CH3 7   // Mode selector (if available) CHANEL 5 (up 994, down 1987)

void setup() {
  Serial.begin(115200);
  Serial.println("FS-i6 Receiver Reader Started");
  Serial.println("Reading channels...");
  delay(1000);
}

void loop() {
  // Read raw pulse values
  unsigned long ch1Pulse = pulseIn(CH1, HIGH, 30000);
  unsigned long ch2Pulse = pulseIn(CH2, HIGH, 30000);
  unsigned long ch3Pulse = pulseIn(CH3, HIGH, 30000);
  
  // Check if signals are valid
  bool ch1Valid = (ch1Pulse > 800 && ch1Pulse < 2200);
  bool ch2Valid = (ch2Pulse > 800 && ch2Pulse < 2200);
  bool ch3Valid = (ch3Pulse > 800 && ch3Pulse < 2200);
  
  // Map values to -100 to 100 range
  int ch1Mapped = map(ch1Pulse, 1000, 2000, -100, 100);
  int ch2Mapped = map(ch2Pulse, 1000, 2000, -100, 100);
  int ch3Mapped = map(ch3Pulse, 1000, 2000, -100, 100);
  
  // Print raw values
  Serial.print("CH1 (Right Stick H): ");
  Serial.print(ch1Pulse);
  Serial.print(" us | Mapped: ");
  Serial.print(ch1Mapped);
  Serial.print(" | Valid: ");
  Serial.println(ch1Valid ? "Yes" : "No");
  
  Serial.print("CH2 (Throttle): ");
  Serial.print(ch2Pulse);
  Serial.print(" us | Mapped: ");
  Serial.print(ch2Mapped);
  Serial.print(" | Valid: ");
  Serial.println(ch2Valid ? "Yes" : "No");
  
  Serial.print("CH3 (Mode): ");
  Serial.print(ch3Pulse);
  Serial.print(" us | Mapped: ");
  Serial.print(ch3Mapped);
  Serial.print(" | Valid: ");
  Serial.println(ch3Valid ? "Yes" : "No");
  
  Serial.println("------------------------");
  
  delay(500); // Update every 500ms
} 