// Topic 10 Solution: DHT11 single-wire sensor (read, handle failed reads)
//
// Wiring: DHT11 data -> D3, VCC -> 3.3 V, GND -> GND.
// (If you have a bare 4-pin DHT11, add a 10k pull-up between data and 3.3 V.
// Most 3-pin breakout boards already have one.)
//
// The DHT11 is slow (one reading per second at most) and reads can fail.
// A failed read is normal, so the code expects it and keeps the last good value.

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

  dht.begin();
  Serial.println("DHT11 reader");
}

void loop() {
  uint32_t now = millis();
  if (now - lastReadMs < READ_INTERVAL_MS) return;  // non-blocking timing
  lastReadMs = now;

  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Celsius

  if (isnan(h) || isnan(t)) {
    failCount++;
    if (consecutiveFails < 255) consecutiveFails++;
    Serial.printf("read failed (%u in a row)", (unsigned)consecutiveFails);
    if (!isnan(lastTempC)) {
      Serial.printf(", last good: T=%.0f C RH=%.0f %% (%lu s ago)",
                    lastTempC, lastHumidity, (unsigned long)((now - lastGoodMs) / 1000));
    }
    Serial.println();

    if (consecutiveFails >= 5) {
      Serial.println("  hint: check the data wire (D3), 3.3 V power and the pull-up resistor");
    }
    return;
  }

  consecutiveFails = 0;
  okCount++;
  lastTempC = t;
  lastHumidity = h;
  lastGoodMs = now;

  Serial.printf("T=%.0f C  RH=%.0f %%  (ok %lu, failed %lu)\n", t, h, (unsigned long)okCount,
                (unsigned long)failCount);
}
