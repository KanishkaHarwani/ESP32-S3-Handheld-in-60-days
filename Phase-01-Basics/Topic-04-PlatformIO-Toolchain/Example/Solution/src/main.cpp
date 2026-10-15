// Topic 04 Solution: PlatformIO toolchain (build, upload, monitor, blink)
//
// Workflow:  pio run  ->  pio run -t upload  ->  pio device monitor

#include <Arduino.h>

// platformio.ini defines BLINK_MS through build_flags (-DBLINK_MS=500).
// This fallback keeps the code building if the flag is removed.
#ifndef BLINK_MS
#define BLINK_MS 1000
#endif

static uint32_t blinkCount = 0;

void setup() {
  Serial.begin(115200);
  delay(1500);  // give the USB serial monitor time to connect

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Hello from the Xiao ESP32S3!");
  Serial.printf("Built: %s %s\n", __DATE__, __TIME__);
  Serial.printf("Blink interval: %d ms\n", BLINK_MS);
}

void loop() {
  // The Xiao's user LED is active LOW: LOW = on, HIGH = off.
  digitalWrite(LED_BUILTIN, LOW);
  delay(BLINK_MS);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(BLINK_MS);

  blinkCount++;
  Serial.printf("blink #%lu\n", (unsigned long)blinkCount);
}
