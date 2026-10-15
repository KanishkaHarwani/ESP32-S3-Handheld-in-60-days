// Topic 11 Solution: debugging basics (serial prints, multimeter, break-it-on-purpose)
//
// Four deliberate bugs, each selectable with BUG_MODE. Set APPLY_FIXES to 0 to see
// the bug happen (crash, corruption or dark LED), and to 1 to see the fixed behaviour.
//
//   BUG_MODE 0 : no bug (heartbeat only)
//   BUG_MODE 1 : null pointer write      -> crash. Backtrace points at bugNullPointer().
//   BUG_MODE 2 : integer divide by zero  -> crash. Backtrace points at bugDivideByZero().
//   BUG_MODE 3 : off-by-one array write  -> silent corruption, caught by the canary check
//   BUG_MODE 4 : LED pin never set as OUTPUT -> multimeter on D0 stays at 0 V
//
// Wiring: Green LED + resistor -> D0.

#include <Arduino.h>

#define BUG_MODE 0
#define APPLY_FIXES 1
#define LOG_LEVEL 4  // 1 error, 2 warn, 3 info, 4 debug

constexpr uint8_t PIN_LED = D0;

// Leveled logging with a timestamp and the source location of each message.
#define LOG(level, tag, fmt, ...)                                                      \
  do {                                                                                 \
    if ((level) <= LOG_LEVEL) {                                                        \
      Serial.printf("[%lu] %s %s:%d " fmt "\n", (unsigned long)millis(), tag, __FILE__, \
                    __LINE__, ##__VA_ARGS__);                                          \
    }                                                                                  \
  } while (0)
#define LOGE(fmt, ...) LOG(1, "E", fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) LOG(2, "W", fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) LOG(3, "I", fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) LOG(4, "D", fmt, ##__VA_ARGS__)

static void bugNullPointer() {
  volatile int *p = nullptr;
#if APPLY_FIXES
  if (p == nullptr) {  // FIX: never dereference before checking
    LOGE("null pointer, write skipped");
    return;
  }
#endif
  *p = 42;  // crashes: LoadStoreError, EXCVADDR=0x00000000
}

static void bugDivideByZero() {
  volatile int divisor = 0;
#if APPLY_FIXES
  if (divisor == 0) {  // FIX: validate the divisor
    LOGE("divisor is zero, division skipped");
    return;
  }
#endif
  volatile int result = 100 / divisor;  // crashes: IntegerDivideByZero
  (void)result;
}

struct Guarded {
  int buf[4];
  uint32_t canary;
};

static void bugOffByOne() {
  Guarded g = {{0, 0, 0, 0}, 0xCAFEBABE};
  volatile int *raw = g.buf;
#if APPLY_FIXES
  for (int i = 0; i < 4; i++) {  // FIX: < instead of <=
#else
  for (int i = 0; i <= 4; i++) {  // BUG: writes buf[4], which is the canary
#endif
    raw[i] = i;
  }
  if (g.canary != 0xCAFEBABE) {
    LOGE("canary corrupted: 0x%08lX (expected 0xCAFEBABE)", (unsigned long)g.canary);
  } else {
    LOGI("canary intact");
  }
}

static void bugMissingPinMode() {
#if APPLY_FIXES
  pinMode(PIN_LED, OUTPUT);  // FIX: configure the pin before driving it
#endif
  digitalWrite(PIN_LED, HIGH);
  LOGI("LED pin driven HIGH: measure D0 with the multimeter (expect about 3.3 V)");
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  LOGI("Debugging demo, BUG_MODE=%d APPLY_FIXES=%d", BUG_MODE, APPLY_FIXES);

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
