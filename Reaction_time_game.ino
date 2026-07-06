/* * Reaction Time Game - Passive Buzzer & Anti-Cheat
 * LED: Red = Wait, Green = GO
 * Threshold: 300ms */

// Pin Definitions
const int reactionButton = 3;
const int rgbRed = 5;
const int rgbGreen = 6;
const int rgbBlue = 7;
const int buzzer = 11;

// Variables
unsigned long startTime;
unsigned long reactionTime;
unsigned long totalReactionTime = 0;
int trials = 0;

// --- CONFIGURATION ---
// Set this to 'true' if your LED is Common Anode (Long pin to 5V)
// Set this to 'false' if your LED is Common Cathode (Long pin to GND) <--- I am using this one
bool isCommonAnode = false; 

void setup() {
  Serial.begin(9600);
  pinMode(reactionButton, INPUT_PULLUP);
  pinMode(rgbRed, OUTPUT);
  pinMode(rgbGreen, OUTPUT);
  pinMode(rgbBlue, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  // Start with everything OFF
  noTone(buzzer);
  setColor(0, 0, 0);
  Serial.println("Get ready...");
  delay(1000);
}

void loop() {
  // 1. START TRIAL - SET TO RED (WAIT)
  noTone(buzzer);
  setColor(120, 0, 0); 
  Serial.println("Status: RED - Wait...");

  unsigned long waitDuration = random(2000, 5000);
  unsigned long waitStart = millis();
  
  // Anti-Cheat
  while (millis() - waitStart < waitDuration) {
    if (digitalRead(reactionButton) == LOW) {
      Serial.println("!! CHEAT DETECTED !!");
      playCheatSound();
      return; 
    }
  }

  // 2. TRIGGER - SET TO GREEN (GO!)
  setColor(0, 120, 0); 
  Serial.println("Status: GREEN - PRESS NOW!");
  startTime = millis();

  // 3. Wait for press
  while (digitalRead(reactionButton) == HIGH) { }
  
  reactionTime = millis() - startTime;
  setColor(0, 0, 0); // Turn off after press
  
  // 4. Feedback & Stats
  trials++;
  totalReactionTime += reactionTime;
  
  Serial.print("Trial "); Serial.print(trials);
  Serial.print("/5 | Time: "); Serial.print(reactionTime); Serial.println(" ms");

  // Buzzer Feedback
  if (reactionTime <= 300) tone(buzzer, 1000);
  else tone(buzzer, 250);
  
  delay(1000); 
  noTone(buzzer);

  if (trials >= 5) {
    Serial.print(">> AVERAGE: ");
    Serial.print(totalReactionTime / 5);
    Serial.println(" ms <<");
    trials = 0;
    totalReactionTime = 0;
    delay(3000);
  }
  delay(1000);
}

// Fixed setColor function
void setColor(int r, int g, int b) {
  if (isCommonAnode) {
    // Reverse the numbers for Common Anode
    analogWrite(rgbRed, 120 - r);
    analogWrite(rgbGreen, 120 - g);
    analogWrite(rgbBlue, 120 - b);
  } else {
    // Normal logic for Common Cathode
    analogWrite(rgbRed, r);
    analogWrite(rgbGreen, g);
    analogWrite(rgbBlue, b);
  }
}

void playCheatSound() {
  for(int i=0; i<3; i++) {
    tone(buzzer, 150); delay(150); noTone(buzzer); delay(100);
  }
}
