/* Drawing a line on an OLED screen using a potentiometer */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaration for SSD1306 display connected using I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int potPin    = A0;
const int buttonPin = 2; // Button pin tied to GND

int xPos = 0;
int prevY = 32;

// EMA Filter to keep the drawn line smooth
float smoothedPot = 512.0;
const float alpha = 0.2;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Button pulls down to LOW when pressed

  // Initialize display with I2C address 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // Loop forever if OLED fails to initialize
  }

  display.clearDisplay();
  display.display();
  
  smoothedPot = analogRead(potPin);
  prevY = map((int)smoothedPot, 0, 1023, SCREEN_HEIGHT - 1, 0);
}

void loop() {
  // 1. Check for Erase Button Press (Active LOW)
  if (digitalRead(buttonPin) == LOW) {
    display.clearDisplay();
    display.display();
    xPos = 0; // Reset X back to left side
    delay(200); // Simple debounce
  }

  // 2. Read and smooth Potentiometer
  int rawPot = analogRead(potPin);
  smoothedPot = (alpha * rawPot) + ((1.0 - alpha) * smoothedPot);

  // Map 0-1023 to Screen Height (63 to 0 so turning knob UP draws UP)
  int yPos = map((int)smoothedPot, 0, 1023, SCREEN_HEIGHT - 1, 0);

  // 3. Draw line segment from last point to current point
  if (xPos < SCREEN_WIDTH) {
    display.drawLine(xPos, prevY, xPos + 1, yPos, SSD1306_WHITE);
    display.display(); // Push drawing buffer to OLED screen
    
    xPos++;
    prevY = yPos;
  } else {
    // Optional: Wrap around back to start automatically, or wait for clear
    // Uncomment next 2 lines to auto-clear when reaching the right edge:
    // display.clearDisplay();
    // xPos = 0;
  }

  delay(30);
}
