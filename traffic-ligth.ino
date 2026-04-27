#include <Wire.h>
#include "SSD1306Wire.h"
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

#define SDA_OLED 17
#define SCL_OLED 18
#define RST_OLED 21
#define Vext     37

#define TMG39931_ADDR 0x39
#define SDA_I2C 41
#define SCL_I2C 42
#define SEALEVELPRESSURE_HPA (1013.25)

SSD1306Wire display(0x3c, SDA_OLED, SCL_OLED);

TwoWire I2C_Sensor = TwoWire(1);

Adafruit_BME680 bme(&I2C_Sensor);

bool showBMEData = false;

void VextON() {
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
}

void displayReset() {
  pinMode(RST_OLED, OUTPUT);
  digitalWrite(RST_OLED, HIGH);
  delay(1);
  digitalWrite(RST_OLED, LOW);
  delay(10);
  digitalWrite(RST_OLED, HIGH);
  delay(10);
}

void setup() {
  Serial.begin(115200);

  VextON();
  displayReset();
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  I2C_Sensor.begin(SDA_I2C, SCL_I2C);

  I2C_Sensor.beginTransmission(TMG39931_ADDR);
  I2C_Sensor.write(0x80);
  I2C_Sensor.write(0x0F);
  I2C_Sensor.endTransmission();
  delay(100);

  if (!bme.begin()) {
    Serial.println(F("Capteur BME680 non trouvé !"));
    display.clear();
    display.drawString(0, 24, "Erreur BME680");
    display.display();
    while (1);
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);

  display.clear();
  display.drawString(0, 24, "Capteurs OK");
  display.display();
  delay(2000);
}

uint16_t readWord(uint8_t reg) {
  I2C_Sensor.beginTransmission(TMG39931_ADDR);
  I2C_Sensor.write(reg);
  I2C_Sensor.endTransmission();
  I2C_Sensor.requestFrom(TMG39931_ADDR, 2);
  
  if (I2C_Sensor.available() < 2) return 0;
  
  uint16_t value = I2C_Sensor.read();
  value |= (I2C_Sensor.read() << 8);
  return value;
}

void loop() {
  uint16_t red   = readWord(0x96);
  uint16_t green = readWord(0x98);
  uint16_t blue  = readWord(0x9A);

  if (!bme.performReading()) {
    Serial.println("Erreur de lecture BME680");
    return;
  }

  display.clear();
  char buffer[25]; 

  if (showBMEData) {
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Environnement");
    display.setFont(ArialMT_Plain_10);
    sprintf(buffer, "T: %.1f C", bme.temperature);
    display.drawString(0, 20, buffer);
    sprintf(buffer, "H: %.1f %%", bme.humidity);
    display.drawString(0, 31, buffer);
    sprintf(buffer, "P: %.0f hPa", bme.pressure / 100.0);
    display.drawString(0, 42, buffer);
    sprintf(buffer, "Gaz: %.1f kOhm", bme.gas_resistance / 1000.0);
    display.drawString(0, 53, buffer);
  } else {
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Lumiere (RGB)");
    display.setFont(ArialMT_Plain_10);
    sprintf(buffer, "Rouge: %d", red);
    display.drawString(0, 24, buffer);
    sprintf(buffer, "Vert:  %d", green);
    display.drawString(0, 38, buffer);
    sprintf(buffer, "Bleu:  %d", blue);
    display.drawString(0, 52, buffer);
  }
  
  display.display();

  showBMEData = !showBMEData;

  delay(2500);
}
