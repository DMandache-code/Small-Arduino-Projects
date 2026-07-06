/* This is the code for a photoresistor LED nightlight */

const int ldrPin = A6;
const int blueLED = 3;   // PWM-capable pin
const int whiteLED = 5;  // PWM-capable pin

// --- Variables ---
int baseline = 0;
int lightLevel = 0;
int diff = 0;
int tolerance = 50;
int currentBrightness = 0;
int targetBrightness = 0;
int fadeSpeed = 2; // how fast LEDs fade

bool whiteMode = false;  // false = blue LED, true = white LED
bool darkTimerRunning = false;
unsigned long darkStartTime = 0;

unsigned long lastPrint = 0;
const unsigned long printInterval = 1000; // ms

void setup() {
  pinMode(blueLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);
  analogWrite(blueLED, 0);
  analogWrite(whiteLED, 0);

  Serial.begin(9600);
  Serial.println("Calibrating baseline...");

  long total = 0;
  for (int i = 0; i < 50; i++) {
    total += analogRead(ldrPin);
    delay(50);
  }
  baseline = total / 50;
  Serial.print("Baseline light level: ");
  Serial.println(baseline);
  Serial.println("System ready.");
}

void loop() {
  lightLevel = analogRead(ldrPin);
  diff = baseline - lightLevel; // how much darker than baseline

  // --- Mode toggle detection ---
  if (lightLevel < 40) {  // near total darkness
    if (!darkTimerRunning) {
      darkTimerRunning = true;
      darkStartTime = millis();
    } else if (millis() - darkStartTime > 3000) {
      whiteMode = !whiteMode;  // toggle LED mode
      darkTimerRunning = false;
      Serial.print(">>> TOGGLED MODE: ");
      Serial.println(whiteMode ? "WHITE" : "BLUE");
    }
  } else {
    darkTimerRunning = false;
  }

  // --- Determine LED target brightness ---
  if (diff > tolerance) {
    targetBrightness = map(diff, tolerance, 400, 0, 255);
    targetBrightness = constrain(targetBrightness, 0, 255);
  } else {
    targetBrightness = 0;
  }

  // --- Smooth fading ---
  if (currentBrightness < targetBrightness) currentBrightness += fadeSpeed;
  else if (currentBrightness > targetBrightness) currentBrightness -= fadeSpeed;
  currentBrightness = constrain(currentBrightness, 0, 255);

  // --- Apply to correct LED ---
  if (whiteMode) {
    analogWrite(whiteLED, currentBrightness);
    analogWrite(blueLED, 0);
  } else {
    analogWrite(blueLED, currentBrightness);
    analogWrite(whiteLED, 0);
  }

  // --- Serial output every 1s ---
  if (millis() - lastPrint >= printInterval) {
    Serial.print("Light: ");
    Serial.print(lightLevel);
    Serial.print(" | Diff: ");
    Serial.print(diff);
    Serial.print(" | Mode: ");
    Serial.print(whiteMode ? "WHITE" : "BLUE");
    Serial.print(" | Brightness: ");
    Serial.println(currentBrightness);
    lastPrint = millis();
  }

  delay(30);
}

