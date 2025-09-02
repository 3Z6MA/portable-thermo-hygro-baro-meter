# Portable Thermo-Hygro-Barometer
A thermo-hygro-barometer based on BME280 and SAMD21 MCU (seeeduino XIAO) with SSD1306 OLED.

It has a single button, pressing it wakes up the MCU from standby and reads temperature, humidity and pressure from the BME280 sensor and displays it for 10s before returning to sleep mode.

Consumes about 3.5mA in standby and about 6-8mA when active, and should run for several days up to a week on a 1300mAh battery.
