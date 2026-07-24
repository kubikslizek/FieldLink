# FieldLink
A tactical field communication and navigation device built on the popular ESP32 microcontroller. Its main goal is to serve as a compact outdoor tool that everyone can use and understand. All of the features are listed below. Some of the features arent actually implemented yet, as I am currently working on them and ensuring they are going to work perfectly.


# FEATURES:
- Live GPS tracking
- nRF24 chat communication
- Navigation to the other device
- Waypoint navigation
- Compass mode
- Smooth UI with audio feedback


# PARTS LIST:

CORE ELECTRONICS:
- ESP32 DevKit
- nRF24L01 radio module with antenna
- NEO-6M GPS module
- QMC5883L magnetometer module

UI
- Analog joystick
- Water resistant buttons
- ST7735 1.8" TFT color screen
- Piezo buzzer

POWER
- 18650 4.2 V Li-ion cell
- TP4056 battery charger
- ON/OFF switch
- Female USB type C port extender
- Boost converter + stabiliser

WIRING & ASSEMBLY
- Dupont wires
- Pin headers
- Heat shrink tubing
- Screws
- Custom 3D printed enclosure


# PINOUT

| Function        | ESP32 GPIO |
| --------------- | ---------: |
| TFT SCK         |         18 |
| TFT MOSI        |         23 |
| TFT CS          |          5 |
| TFT DC          |          2 |
| TFT RST         |          4 |
| Joystick X      |         26 |
| Joystick Y      |         27 |
| Joystick Button |         13 |
| GPS RX          |         16 |
| GPS TX          |         17 |
| Compass SDA     |         21 |
| Compass SCL     |         22 |
| nRF24 CE        |         15 |
| nRF24 CSN       |         14 |
| Battery ADC     |         34 |

























