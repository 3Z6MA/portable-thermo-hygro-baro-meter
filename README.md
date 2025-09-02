# Portable Thermo-Hygro-Barometer
A thermo-hygro-barometer based on BME280 and SAMD21 MCU (seeeduino XIAO) with SSD1306 OLED.

It has a single button, pressing it wakes up the MCU from standby and reads temperature, humidity and pressure from the BME280 sensor and displays it for 10s before returning to sleep mode.

Consumes about 3.5mA in standby and about 6-8mA when active, and should run for several days up to a week on a 1300mAh battery.

## Seeeduino XIAO board:
In Arduino IDE got to: `File -> Preferences -> Settings` and add the following URL to Additional boards manager URLs

https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json

## Libraries
- [Arduino Low Power by Arduino v1.2.2](https://docs.arduino.cc/libraries/arduino-low-power/)
- [Adafruit BME280 Library by Adafruit v2.3.0](https://github.com/adafruit/Adafruit_BME280_Library)
- [Adafruit SSD1306 by Adafruit v2.5.15](https://github.com/adafruit/Adafruit_SSD1306)
- [Adafruit SleepyDog Library by Adafruit v1.6.5](https://github.com/adafruit/Adafruit_SleepyDog)
