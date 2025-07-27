#include <Servo.h>

#define CH1 3   // Right Stick Horizontal
#define CH2 5   // Throttle (Left Stick Vertical)

const int LEFT_PIN = 9;
const int RIGHT_PIN = 11;
const int PWM_STOP = 1500;
const int DEADZONE = 20;
const int PWM_MIN = 1400;
const int PWM_MAX = 1600;

Servo leftESC, rightESC;

// Single-point signal reading
struct Signal {
  int throttle;
  int rotation;
  bool valid;
};

Signal readSignals() {
  Signal sig;

  // Read raw pulses first
  unsigned long rotPulse = pulseIn(CH1, HIGH, 30000);
  unsigned long thrPulse = pulseIn(CH2, HIGH, 30000);

  sig.valid = (rotPulse > 800 && rotPulse < 2200) && 
              (thrPulse > 800 && thrPulse < 2200);

  // Map values only once
  sig.rotation = map(rotPulse, 1000, 2000, -100, 100);
  sig.throttle = map(thrPulse, 1000, 2000, -100, 100);

  return sig;
}

void setup() {
  Serial.begin(115200);
  leftESC.attach(LEFT_PIN);
  rightESC.attach(RIGHT_PIN);
  leftESC.writeMicroseconds(PWM_STOP);
  rightESC.writeMicroseconds(PWM_STOP);
  delay(5000);
}

void loop() {
  Signal sig = readSignals();

  if (!sig.valid) {
    leftESC.writeMicroseconds(PWM_STOP);
    rightESC.writeMicroseconds(PWM_STOP);
    Serial.println("Signal error!");
    return;
  }

  // Deadzone handling
  if(abs(sig.throttle) < DEADZONE) sig.throttle = 0;
  if(abs(sig.rotation) < DEADZONE) sig.rotation = 0;

  // Single calculation path
  int basePWM = map(sig.throttle, -100, 100, PWM_MIN, PWM_MAX);
  int diff = map(sig.rotation, -100, 100, -50, 50);

  leftESC.writeMicroseconds(constrain(basePWM + diff, 1100, 1900));
  rightESC.writeMicroseconds(constrain(basePWM - diff, 1100, 1900));

  Serial.print("T:"); Serial.print(sig.throttle);
  Serial.print(" R:"); Serial.println(sig.rotation);

  delay(20);
}
