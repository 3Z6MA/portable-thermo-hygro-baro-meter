#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SleepyDog.h>
#include <ArduinoLowPower.h>

#define EXT_INT_PIN 9

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BME280 bme;
Adafruit_Sensor *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor *bme_humidity = bme.getHumiditySensor();

const char *BME_ERR = "BME280 Error!";

const String tempr = "Temperature = ";
const String press = "Pressure = ";
const String humid = "Humidty = ";

volatile bool wakeUp = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1) delay(10);
  }

  display.clearDisplay();
  display.display();

  if (!bme.begin(BME280_ADDRESS_ALTERNATE)) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    drawText(BME_ERR, 0, 0);
    while (1) delay(10);
  }

  pinMode(EXT_INT_PIN, INPUT_PULLUP);
  LowPower.attachInterruptWakeup(EXT_INT_PIN, wakeISR, FALLING);
  USBDevice.detach();
}

void loop() {
  if (wakeUp) {
    sensors_event_t temp_event, pressure_event, humidity_event;
    bme_temp->getEvent(&temp_event);
    bme_pressure->getEvent(&pressure_event);
    bme_humidity->getEvent(&humidity_event);

    display.clearDisplay();

    String t = String("t ") + temp_event.temperature + " C";
    String h = String("h ") + humidity_event.relative_humidity + " %";
    String p = String("p ") + pressure_event.pressure + " hpa";

    drawText(t.c_str());
    drawText(h.c_str(), 0, 12);
    drawText(p.c_str(), 0, 23);

    Watchdog.sleep(10000);
    display.clearDisplay();
    display.display();

    wakeUp = false;
  }
  LowPower.deepSleep();
}

void drawText(const char *text) {
  drawText(text, 0, 0);
}

void drawText(const __FlashStringHelper *ifsh) {
  drawText(reinterpret_cast<const char *>(ifsh), 0, 0);
}

void drawText(const __FlashStringHelper *ifsh, int x, int y) {
  drawText(reinterpret_cast<const char *>(ifsh), x, y);
}

void drawText(const char *text, int x, int y) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.cp437(true);
    char *tmp = (char*)text;
    while ( *tmp != NULL )
      display.print(*tmp++);
    display.display();
}

void wakeISR() {
  if (!wakeUp)
    wakeUp = true;
}
