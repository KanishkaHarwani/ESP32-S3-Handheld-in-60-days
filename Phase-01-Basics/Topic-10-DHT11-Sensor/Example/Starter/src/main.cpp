// Topic 10 Starter: DHT11 single-wire sensor (read, handle failed reads)
//
// Wiring: DHT11 data -> D3, VCC -> 3.3 V, GND -> GND.
// (If you have a bare 4-pin DHT11, add a 10k pull-up between data and 3.3 V.
// Most 3-pin breakout boards already have one.)
//
// The DHT11 is slow (one reading per second at most) and reads can fail.
// A failed read is normal, so the code must expect it.

#include <Arduino.h>
#include <DHT.h>

constexpr uint8_t PIN_DHT = D3;
constexpr uint32_t READ_INTERVAL_MS = 2000;

DHT dht(PIN_DHT, DHT11);

static uint32_t lastReadMs = 0;
static uint32_t okCount = 0;
static uint32_t failCount = 0;
static uint8_t consecutiveFails = 0;

// Last good values, so the rest of the program always has something to show.
static float lastTempC = NAN;
static float lastHumidity = NAN;
static uint32_t lastGoodMs = 0;

void setup() {
  Serial.begin(115200);
  delay(1500);

  // TODO 1: start the sensor with dht.begin()
  Serial.println("DHT11 reader");
}

void loop() {
  uint32_t now = millis();
  if (now - lastReadMs < READ_INTERVAL_MS) return;  // non-blocking timing
  lastReadMs = now;

  // TODO 2: read humidity and temperature: dht.readHumidity(), dht.readTemperature()
  float h = NAN;
  float t = NAN;

  // TODO 3: if either value isnan(): count a failure (failCount, consecutiveFails),
  //         print "read failed (N in a row)" and return.
  //         On success: reset consecutiveFails, increment okCount, and store the values
  //         and the time in lastTempC, lastHumidity and lastGoodMs.

  // TODO 4: print "T=24.0 C  RH=45 %  (ok 10, failed 1)"
  (void)h;
  (void)t;

  // TODO 5: if consecutiveFails >= 5, print a hint: check wiring, 3.3 V and the pull-up.
}
