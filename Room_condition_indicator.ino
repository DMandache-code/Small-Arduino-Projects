/* Monitors light and temperature to provide visual status alerts. Uses a thermistor and ldr. */

// Pin Definitions
const int LDR_PIN = A1;
const int TEMP_PIN = A2;
const int WARNING_LED = 7;
const int RESET_BUTTON = 5;

// --- NTC Constants ---
const float BETA = 3950;
const int ROOM_RESISTANCE = 10000;
const int RESISTOR_VALUE = 10000;

// --- Global Variables for Baseline ---
float baseTemp = 0;
int baseLight = 0;

// Tolerance ranges (Deviation from baseline)
const float TEMP_TOLERANCE = 3.0; // +/- 3 degrees C
const int LIGHT_TOLERANCE = 150;  // +/- 150 units

// Helper function for the NTC math
float calculateTemp() {
  int analogVal = analogRead(TEMP_PIN);
  float resistance = RESISTOR_VALUE / (1023.0 / analogVal - 1.0);
  float temp;
  temp = resistance / ROOM_RESISTANCE;
  temp = log(temp);
  temp /= BETA;
  temp += 1.0 / (25.0 + 273.15);
  temp = 1.0 / temp;
  return temp - 273.15;
}

// Function to set or reset the room's "normal" state
void calibrate() {
  Serial.println(">>> CALIBRATING BASELINE...");
  
  long lightSum = 0;
  float tempSum = 0;
  
  for(int i = 0; i < 5; i++) {
    lightSum += analogRead(LDR_PIN);
    tempSum += calculateTemp();
    delay(50);
  }
  
  baseLight = lightSum / 5;
  baseTemp = tempSum / 5.0;
  
  Serial.print("Baseline Set. Light: "); Serial.print(baseLight);
  Serial.print(" | Temp: "); Serial.println(baseTemp);
}

void setup() {
  Serial.begin(9600);
  pinMode(WARNING_LED, OUTPUT);
  pinMode(RESET_BUTTON, INPUT_PULLUP); 

  calibrate(); // Set initial baseline on startup
}

void loop() {
  // 1. Check for Reset Button (Pressed = LOW)
  if (digitalRead(RESET_BUTTON) == LOW) {
    calibrate();
    delay(200); // Debounce
  }

  // 2. Read Sensors
  int currentLight = analogRead(LDR_PIN);
  float currentTemp = calculateTemp();

  // 3. Logic: Check for deviations
  bool tooHot = (currentTemp > baseTemp + TEMP_TOLERANCE);
  bool tooCold = (currentTemp < baseTemp - TEMP_TOLERANCE);
  bool tooBright = (currentLight > baseLight + LIGHT_TOLERANCE);
  bool tooDark = (currentLight < baseLight - LIGHT_TOLERANCE);

  // 4. Output Control (Only Red LED)
  if (tooHot || tooCold || tooBright || tooDark) {
    digitalWrite(WARNING_LED, HIGH);
  } else {
    digitalWrite(WARNING_LED, LOW);
  }

  // 5. Logging
  Serial.print("L: "); Serial.print(currentLight);
  Serial.print(" | T: "); Serial.print(currentTemp);
  
  if (digitalRead(WARNING_LED) == HIGH) {
    Serial.println(" [WARNING]");
  } else {
    Serial.println(" [OK]");
  }

  delay(500);
}

