/* Ultrasound proximity sensor, which triggers an buzzer alarm and led if an object gets too close */

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 5;
const int ledPin = 7;

// Variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600); // Start serial monitor
}

void loop() {
  // 1. Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 2. Trigger the sensor by sending a 10 microsecond pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 3. Read the echoPin (returns the sound wave travel time in microseconds)
  duration = pulseIn(echoPin, HIGH);

  // 4. Calculate the distance (Speed of sound is 0.034 cm/us)
  distance = duration * 0.034 / 2;

  // 5. Print to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 6. Logic for Buzzer and LED
  if (distance <= 3) {
    // CRITICAL ZONE: Constant ON
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
  } 
  else if (distance > 3 && distance <= 30) {
    // WARNING ZONE: Beeping faster as it gets closer
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(10); // Short pulse
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    
    // The delay is proportional to the distance
    // Closer = smaller delay = faster beeps
    delay(distance * 15); 
  } 
  else {
    // SAFE ZONE: Everything off
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }

  delay(50); // Small stability delay
}
