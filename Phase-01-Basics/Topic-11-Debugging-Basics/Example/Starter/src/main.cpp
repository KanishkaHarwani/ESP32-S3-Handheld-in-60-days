// Topic 11 Starter: debugging basics (serial prints, multimeter, break-it-on-purpose)
//
// This program contains four deliberate bugs. Pick one with BUG_MODE, run it, and
// diagnose it using only the tools from this topic.
//
//   BUG_MODE 0 : no bug (heartbeat only)
//   BUG_MODE 1 : null pointer write      -> crash + backtrace (read it with the exception decoder)
//   BUG_MODE 2 : integer divide by zero  -> crash + backtrace
//   BUG_MODE 3 : off-by-one array write  -> silent memory corruption (no crash!)
//   BUG_MODE 4 : LED pin never set as OUTPUT -> LED stays off; use the multimeter on D0
//
// Wiring: Green LED + resistor -> D0.

#include <Arduino.h>

#define BUG_MODE 0
#define LOG_LEVEL 4  // 1 error, 2 warn, 3 info, 4 debug

constexpr uint8_t PIN_LED = D0;

// TODO 1: write a LOG(level, fmt, ...) macro that prints
//         "[millis] file:line message" only when level <= LOG_LEVEL.
//         (hint: do { ... } while (0), Serial.printf, __FILE__, __LINE__, ##__VA_ARGS__)
//         Then define LOGE / LOGW / LOGI / LOGD on top of it for levels 1..4.
#define LOGE(...)
#define LOGW(...)
#define LOGI(...)
#define LOGD(...)

static void bugNullPointer() {
  volatile int *p = nullptr;
  *p = 42;  // TODO 2: run BUG_MODE 1, read the backtrace, then add a guard
}

static void bugDivideByZero() {
  volatile int divisor = 0;
  volatile int result = 100 / divisor;  // TODO 3: run BUG_MODE 2, read the backtrace, then guard
  (void)result;
}

struct Guarded {
  int buf[4];
  uint32_t canary;
};

static void bugOffByOne() {
  Guarded g = {{0, 0, 0, 0}, 0xCAFEBABE};
  volatile int *raw = g.buf;
  for (int i = 0; i <= 4; i++) {  // TODO 4: the bug is in this loop condition
    raw[i] = i;
  }
  // TODO 5: after the loop, check that g.canary is still 0xCAFEBABE and print an error if not.
  //         A canary like this is how you catch silent corruption early.
}

static void bugMissingPinMode() {
  // TODO 6: the LED never lights. Use the multimeter on D0 to confirm the pin never
  //         goes high, then fix it in the right place.
  digitalWrite(PIN_LED, HIGH);
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  LOGI("Debugging demo, BUG_MODE=%d", BUG_MODE);

#if BUG_MODE == 1
  bugNullPointer();
#elif BUG_MODE == 2
  bugDivideByZero();
#elif BUG_MODE == 3
  bugOffByOne();
#elif BUG_MODE == 4
  bugMissingPinMode();
#endif

  LOGI("setup finished");
}

void loop() {
  LOGD("heartbeat, free heap %lu", (unsigned long)ESP.getFreeHeap());
  delay(2000);
}
