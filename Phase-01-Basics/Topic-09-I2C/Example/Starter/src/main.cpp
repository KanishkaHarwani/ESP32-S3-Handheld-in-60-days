// Topic 09 Starter: I2C (bus scan, read an I2C sensor)
//
// Wiring: sensor SDA -> D4, SCL -> D5, VCC -> 3.3 V, GND -> GND.
// This example reads an AHT20 (address 0x38) with raw Wire calls so you see what a
// driver does underneath. If you bought a BME280 instead, the scan will show 0x76
// or 0x77: reuse the scan, and use that sensor's datasheet or library for the read.

#include <Arduino.h>
#include <Wire.h>

constexpr uint8_t PIN_SDA = D4;
constexpr uint8_t PIN_SCL = D5;
constexpr uint8_t AHT20_ADDR = 0x38;

static void scanBus() {
  Serial.println("Scanning I2C bus...");
  uint8_t found = 0;
  // TODO 2: for address 1..126: Wire.beginTransmission(addr);
  //         if Wire.endTransmission() == 0 a device ACKed -> print "found 0x%02X" and count it.
  Serial.printf("%u device(s) found\n", (unsigned)found);
}

static bool aht20Begin() {
  delay(40);  // sensor needs ~40 ms after power-up
  // TODO 3: send the initialisation command bytes 0xBE, 0x08, 0x00 to AHT20_ADDR
  //         (beginTransmission, write x3, endTransmission). Return false if it did not ACK.
  delay(10);
  return false;
}

static bool aht20Read(float &tempC, float &humidity) {
  // TODO 4: trigger a measurement: write 0xAC, 0x33, 0x00 to AHT20_ADDR. Return false on NACK.
  delay(80);  // measurement takes ~80 ms

  // TODO 5: request 7 bytes (Wire.requestFrom((int)AHT20_ADDR, 7)). Return false if fewer arrive.
  //         Read them into uint8_t d[7].
  //         If d[0] & 0x80 the sensor is still busy: return false.

  // TODO 6: convert (the datasheet packs two 20-bit values into d[1..5]):
  //   rawH = (d[1] << 12) | (d[2] << 4) | (d[3] >> 4)
  //   rawT = ((d[3] & 0x0F) << 16) | (d[4] << 8) | d[5]
  //   humidity = rawH * 100.0 / 1048576.0
  //   tempC    = rawT * 200.0 / 1048576.0 - 50.0
  (void)tempC;
  (void)humidity;
  return false;
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  // TODO 1: start the bus with Wire.begin(PIN_SDA, PIN_SCL)
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
