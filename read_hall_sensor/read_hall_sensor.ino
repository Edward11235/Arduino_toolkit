// Define the pins connected to the encoder signals
const int encoderPinA = 2; // Change as per your setup
const int encoderPinB = 3; // Change as per your setup, even if not used in this example

// Variables to hold the current and last encoder state
volatile int encoderState;
volatile int lastEncoderState;

// Counter for encoder pulses
volatile unsigned long pulseCount = 0;

// Calculate rotations
volatile float rotations = 0;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Configure the encoder pins as inputs
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  // Attach an interrupt to encoderPinA on CHANGE
  attachInterrupt(digitalPinToInterrupt(encoderPinA), countPulse, CHANGE);
}

void loop() {
  // Calculate the number of rotations
  rotations = pulseCount / 16.0;

  // Print the number of rotations
  Serial.print("Rotations: ");
  Serial.println(rotations, 2); // Print with 2 decimal places

  // Small delay to avoid spamming the Serial Monitor
  delay(1000);
}

void countPulse() {
  int readingA = digitalRead(encoderPinA);

  // Only count on one edge (e.g., rising or falling) to avoid counting twice
  if (readingA != lastEncoderState) {
    pulseCount++;
    lastEncoderState = readingA;
  }
}
