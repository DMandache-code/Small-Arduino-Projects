# Small-Arduino-Projects
A collection of Arduino circuit experiments exploring microcontroller programming, focusing on sensor and human input.

* **Microcontrollers:** Arduino Uno / Nano
* **Language:** C/C++ (Arduino IDE)

## Projects Overview

Here is a breakdown of the circuits I built so far, ranging from simple sensor tests to interactive games.

### 1. Reaction Time Game
* **Description:** A fun, interactive game that measures user reflex speed using buttons and LEDs, calculating response times in milliseconds.
* **Key Components:** Push buttons, LEDs, piezo buzzer.
* **Concepts Learned:** Timing functions (`millis()`), state management.

### 2. Room Condition Indicator
* **Description:** A monitoring system that tracks temperature and ambient light and provides visual feedback on room conditions.
* **Key Components:** Temperature sensor (Thermistor), Photoresistor (LDR), LEDs/LCD Display.
* **Concepts Learned:** Analog-to-digital conversion (ADC), threshold calibration.

### 3. Ultrasound Proximity Sensor
* **Description:** Utilizes ultrasonic waves to measure distances to nearby objects, triggering different behaviors based on proximity.
* **Key Components:** HC-SR04 Ultrasonic Sensor, LEDs.
* **Concepts Learned:** Pulse timing, signal speed-of-sound calculations.

### 4. LDR Nightlight
* **Description:** An automated nightlight that turns on an LED when ambient light levels drop below a specific threshold.
* **Key Components:** Photoresistor (LDR), LED.
* **Concepts Learned:** Voltage dividers, analog sensor thresholds.

### 5. Buzzer Melody Player
* **Description:** A simple audio project that uses PWM frequencies to play specific musical notes through a buzzer.
* **Key Components:** Piezo buzzer.
* **Concepts Learned:** Tone generation, arrays for notes and durations.
