/* Servo motor controlled by potentiometer with smoothing */

#include <Servo.h>

Servo myServo;

const int potPin   = A0;
const int servoPin = 9;

// EMA Filter variables
float smoothedVal = 0.0;
const float alpha = 0.15; // Filter factor (0.05 = super smooth/slower, 0.3 = faster response/less smooth)

void setup() {
  myServo.attach(servoPin);
  smoothedVal = analogRead(potPin); // Initialize with first reading
}

void loop() {
  int rawVal = analogRead(potPin);

  // Exponential Moving Average formula: Smoothed = (alpha * Raw) + ((1 - alpha) * Previous)
  smoothedVal = (alpha * rawVal) + ((1.0 - alpha) * smoothedVal);

  // Map the smoothed value to servo range (0 - 180 degrees)
  int angle = map((int)smoothedVal, 0, 1023, 0, 180);

  myServo.write(angle);
  delay(15);
}
