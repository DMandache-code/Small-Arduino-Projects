# Small-Arduino-Projects
A collection of code for Arduino circuit experiments exploring microcontroller programming, focusing on sensor and human input.

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

### 6. Potentiometer-Controlled Servo Motor
* **Description:** Demonstrates real-time position control of a servo motor using an analog potentiometer with software noise filtering to prevent motor jitter.
* **Key Components:** Servo motor (SG90/MG996R), 10kΩ Potentiometer.
* **Concepts Learned:** Analog-to-digital conversion (ADC), value mapping (map()), Exponential Moving Average (EMA) filtering, pulse-width modulation (PWM) servo timing.

### 7. Shift Register LED Array
* **Description:** Controls an array of 6 LEDs using a 74HC595 shift register, featuring sequential lighting patterns and smooth PWM brightness fading.
* **Key Components:** 74HC595 Shift Register, 6× LEDs, 220Ω resistors.
* **Concepts Learned:** Serial-to-parallel data transfer, bitwise shifting, active-LOW hardware logic, PWM brightness control via Output Enable.
 
