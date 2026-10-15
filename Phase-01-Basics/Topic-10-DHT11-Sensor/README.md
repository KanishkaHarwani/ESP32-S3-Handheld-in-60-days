# Topic 10: DHT11 Single-Wire Sensor

**Week 3** · The DHT11 is the sensor that ends up in the final handheld, so it is worth understanding properly, including how it fails.

## What it is (and is not)

A cheap temperature and humidity sensor with **one data wire**. It is **not I²C**. It uses its own timing-based protocol: the chip sends a request pulse, and the sensor answers with 40 bits encoded in pulse widths.

| Spec | Value |
| ---- | ----- |
| Temperature accuracy | about ±2 °C |
| Humidity accuracy | about ±5 %RH |
| Maximum read rate | once per second (we read every 2 s) |
| Supply | 3.3 V on the Xiao |

## Wiring

| DHT11 pin | Connect to |
| --------- | ---------- |
| VCC (+) | 3.3 V |
| DATA (S/OUT) | **D3** |
| GND (-) | GND |

A bare 4-pin sensor needs a 10 kΩ pull-up between DATA and 3.3 V. A 3-pin module usually has it built in. Keep wires short.

## Reading it

```ini
; platformio.ini
lib_deps =
    adafruit/DHT sensor library
    adafruit/Adafruit Unified Sensor
```

```cpp
#include <DHT.h>

constexpr uint8_t DHT_PIN = D3;
DHT dht(DHT_PIN, DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float t = dht.readTemperature();   // Celsius
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("DHT11 read failed");
  } else {
    Serial.printf("Temp: %.1f C  Humidity: %.0f %%\n", t, h);
  }
  delay(2000);
}
```

## Reads can fail. That is normal.

A failed read returns `NaN`. Causes: reading faster than once per second, loose wiring, a missing pull-up, or the CPU busy with something else during the bit-timing window. Do not treat it as a crash. Handle it:

```cpp
struct Dht11State {
  float    lastTempC = NAN;
  float    lastHumidity = NAN;
  uint32_t lastGoodMs = 0;
  uint8_t  consecutiveFailures = 0;
};

void updateDht(Dht11State& s) {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    if (s.consecutiveFailures < 255) s.consecutiveFailures++;
    return;                          // keep the last good values
  }
  s.lastTempC = t;
  s.lastHumidity = h;
  s.lastGoodMs = millis();
  s.consecutiveFailures = 0;
}
```

Rules to follow:

- Keep the **last good value** and show it, rather than showing garbage.
- Count consecutive failures. After about 5, report "sensor error" instead of pretending all is well.
- Never block waiting for a good read.
- Use `millis()`, not `delay()`, so the rest of the program keeps running.

## Why timing matters later

The DHT11 protocol is timing-sensitive. In Phase 2 and 3, other work on the same core can disturb it, which is why the final firmware reads it from its own task every 2 seconds.

## Check yourself

- Why is the DHT11 not on the I²C bus?
- What does a `NaN` reading mean, and what should the program do?
- Why show the last good value instead of the latest raw read?

## What's next

Topic 11 covers debugging habits, then Topic 12 combines the DHT11, buttons, LEDs and buzzer into the Phase 1 checkpoint.
