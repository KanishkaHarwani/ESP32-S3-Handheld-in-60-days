// Topic 04 Starter: PlatformIO toolchain (build, upload, monitor, blink)
//
// Goal: blink the on-board LED, print a serial banner, and learn how a build
// flag in platformio.ini reaches your C++ code.
//
// Workflow to practise:  pio run  ->  pio run -t upload  ->  pio device monitor

#include <Arduino.h>

// TODO 2: give BLINK_MS a default of 1000 if the build flags did not define it.
//         (hint: #ifndef BLINK_MS / #define BLINK_MS 1000 / #endif)

static uint32_t blinkCount = 0;

void setup() {
  Serial.begin(115200);
  delay(1500);  // give the USB serial monitor time to connect

  pinMode(LED_BUILTIN, OUTPUT);

  // TODO 3: print "Hello from the Xiao ESP32S3!" and the build time
  //         (hint: the compiler provides __DATE__ and __TIME__)
  // TODO 4: print the blink interval so you can see which value was used
}

void loop() {
  // NOTE: the Xiao's user LED is active LOW: LOW = on, HIGH = off.
  // TODO 5: turn the LED on, wait BLINK_MS, turn it off, wait BLINK_MS
  // TODO 6: increment blinkCount and print "blink #N"
}
