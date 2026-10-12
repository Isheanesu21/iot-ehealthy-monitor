# iot-ehealthy-monitor
# IoT E-Health Monitoring System

An IoT-based system that measures [vital signs, e.g. heart rate, temperature] and sends the readings to the cloud so they can be monitored remotely.

## Features
- Real-time readings from MAX30100, DS18B20
- Local display on an LCD
- Data uploaded to ThingSpeak for remote viewing and graphs

## Components
- ESP32 microcontroller
- MAX30100, DS18B20
- LCD display
- Other parts: resistors, breadboard, LEDs, buzzer, jumping wires etc

## How It Works
1. Sensors read the patient data.
2. The ESP32 processes the readings and shows them on the LCD.
3. The ESP32 sends the data over Wi-Fi to ThingSpeak.
4. ThingSpeak displays the readings as live charts.

## Setup
1. Install the Arduino IDE and the ESP32 board package.
2. Install the libraries: LiquidCrystal_I2C, Wire.h, DallasTemperature.h, MAX30100 Library, Wifi.h etc
3. Open `LAST.ino`.
4. Enter your own Wi-Fi name, password and ThingSpeak API key in the code.
5. Upload to the ESP32.

## Screenshots
<img width="1060" height="696" alt="Patient Readings" src="https://github.com/user-attachments/assets/988f2d82-4c87-4ae3-9ca8-8e8f0ee1a498" />


## Author
Isheanesu W Chigerwe, Electronics and Telecommunications Engineering student at the University of Zimbabwe
