// Topic 09 Solution: I2C (bus scan, read an I2C sensor)
//
// Wiring: sensor SDA -> D4, SCL -> D5, VCC -> 3.3 V, GND -> GND.
// Reads an AHT20 (address 0x38) with raw Wire calls so you see what a driver does
// underneath. If you bought a BME280 instead, the scan will show 0x76 or 0x77:
// reuse the scan, and use that sensor's datasheet or library for the read.

#include <Arduino.h>
#include <Wire.h>

constexpr uint8_t PIN_SDA = D4;
constexpr uint8_t PIN_SCL = D5;
constexpr uint8_t AHT20_ADDR = 0x38;

static void scanBus() {
  Serial.println("Scanning I2C bus...");
  uint8_t found = 0;
  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {  // 0 = a device acknowledged this address
      Serial.printf("  found device at 0x%02X\n", (unsigned)addr);
      found++;
    }
  }
  Serial.printf("%u device(s) found\n", (unsigned)found);
}

static bool aht20Begin() {
  delay(40);  // sensor needs ~40 ms after power-up
  Wire.beginTransmission(AHT20_ADDR);
  Wire.write(0xBE);  // initialise / calibrate command
  Wire.write(0x08);
  Wire.write(0x00);
  if (Wire.endTransmission() != 0) return false;
  delay(10);
  return true;
}

static bool aht20Read(float &tempC, float &humidity) {
  Wire.beginTransmission(AHT20_ADDR);
  Wire.write(0xAC);  // trigger measurement
  Wire.write(0x33);
  Wire.write(0x00);
  if (Wire.endTransmission() != 0) return false;
  delay(80);  // measurement takes ~80 ms

  if (Wire.requestFrom((int)AHT20_ADDR, 7) != 7) return false;
  uint8_t d[7];
  for (uint8_t i = 0; i < 7; i++) d[i] = (uint8_t)Wire.read();

  if (d[0] & 0x80) return false;  // status bit 7 = still busy

  uint32_t rawH = ((uint32_t)d[1] << 12) | ((uint32_t)d[2] << 4) | (d[3] >> 4);
  uint32_t rawT = ((uint32_t)(d[3] & 0x0F) << 16) | ((uint32_t)d[4] << 8) | d[5];

  humidity = rawH * 100.0f / 1048576.0f;  // 2^20 = 1048576
  tempC = rawT * 200.0f / 1048576.0f - 50.0f;
  return true;
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  Wire.begin(PIN_SDA, PIN_SCL);
  scanBus();

  if (!aht20Begin()) {
    Serial.println("AHT20 not responding (check wiring, power and the scan result)");
  }
}

void loop() {
  float t = 0, h = 0;
  if (aht20Read(t, h)) {
    Serial.printf("T = %.1f C, RH = %.1f %%\n", t, h);
  } else {
    Serial.println("read failed");
  }
  delay(2000);
}
