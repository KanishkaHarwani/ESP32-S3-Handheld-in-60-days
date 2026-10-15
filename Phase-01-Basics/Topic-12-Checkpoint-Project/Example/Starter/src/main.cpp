// Topic 12 Starter: Phase 1 checkpoint
// DHT11 + buttons -> LED / buzzer / serial feedback loop
//
// Wiring (Phase 1 table in hardware/README.md):
//   Green LED -> D0   Red LED -> D1   Buzzer -> D2 (active buzzer)   DHT11 data -> D3
//   Button A -> D6 to GND   Button B -> D7 to GND
//
// Behaviour:
//   - Read the DHT11 every 2 s.
//   - Temperature below the threshold : green LED on, quiet.
//   - Temperature at/above threshold  : red LED on, buzzer beeps (ALARM).
//   - Button A : mute / unmute the alarm buzzer.
//   - Button B : cycle the threshold 26 -> 28 -> 30 -> 32 C and back.
//   - 3 failed reads in a row          : SENSOR_ERROR, LEDs alternate, buzzer off.
//   - Print a status line to serial after every read.
//
// This file is the skeleton. Everything marked TODO is yours to write, using what
// you built in Topics 06, 07 and 10.

#include <Arduino.h>
#include <DHT.h>

constexpr uint8_t PIN_LED_GREEN = D0;
constexpr uint8_t PIN_LED_RED = D1;
constexpr uint8_t PIN_BUZZER = D2;
constexpr uint8_t PIN_DHT = D3;
constexpr uint8_t PIN_BTN_A = D6;
constexpr uint8_t PIN_BTN_B = D7;

constexpr uint32_t DHT_INTERVAL_MS = 2000;
constexpr uint8_t MAX_FAILS = 3;
constexpr float HYSTERESIS_C = 1.0f;  // alarm clears 1 C below the threshold
constexpr float THRESHOLDS_C[] = {26.0f, 28.0f, 30.0f, 32.0f};
constexpr size_t THRESHOLD_COUNT = sizeof(THRESHOLDS_C) / sizeof(THRESHOLDS_C[0]);

enum class State { OK, ALARM, SENSOR_ERROR };

// Debounced button from Topic 06 (complete, reuse it as is).
class Button {
 public:
  explicit Button(uint8_t pin, uint32_t debounceMs = 30) : pin_(pin), debounceMs_(debounceMs) {}
  void begin() {
    pinMode(pin_, INPUT_PULLUP);
    raw_ = stable_ = digitalRead(pin_);
    lastChange_ = millis();
  }
  bool pressed() {
    int reading = digitalRead(pin_);
    uint32_t now = millis();
    if (reading != raw_) {
      raw_ = reading;
      lastChange_ = now;
    }
    if (now - lastChange_ >= debounceMs_ && raw_ != stable_) {
      stable_ = raw_;
      if (stable_ == LOW) return true;
    }
    return false;
  }

 private:
  uint8_t pin_;
  uint32_t debounceMs_;
  int raw_ = HIGH;
  int stable_ = HIGH;
  uint32_t lastChange_ = 0;
};

DHT dht(PIN_DHT, DHT11);
Button btnA(PIN_BTN_A);
Button btnB(PIN_BTN_B);

static State state = State::OK;
static size_t thresholdIndex = 1;  // start at 28 C
static bool muted = false;
static uint8_t consecutiveFails = 0;
static float lastTempC = NAN;
static float lastHumidity = NAN;
static uint32_t lastReadMs = 0;

// TODO 1: read the sensor. On success store lastTempC/lastHumidity and reset
//         consecutiveFails. On failure increment consecutiveFails.
static void readSensor() {}

// TODO 2: decide the next state.
//   - consecutiveFails >= MAX_FAILS         -> SENSOR_ERROR
//   - temp >= threshold                     -> ALARM
//   - in ALARM, stay ALARM until temp < threshold - HYSTERESIS_C
//   - otherwise                             -> OK
//   When leaving ALARM, clear `muted` so the next alarm is audible again.
static void updateState() {}

// TODO 3: drive the outputs for the current state (must not block: no delay()).
//   OK           : green on, red off, buzzer off
//   ALARM        : green off, red on, buzzer beeps 100 ms on / 900 ms off unless muted
//   SENSOR_ERROR : green and red alternate every 250 ms, buzzer off
static void updateOutputs() {}

// TODO 4: print one status line:
//   "T=27.0 C RH=45 % thr=28 C state=OK muted=no fails=0"
static void printStatus() {}

void setup() {
  Serial.begin(115200);
  delay(1500);

  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
  btnA.begin();
  btnB.begin();
  dht.begin();

  Serial.println("Phase 1 checkpoint: temperature alarm");
}

void loop() {
  uint32_t now = millis();

  // TODO 5: if btnA.pressed(), toggle `muted` and print the new state.
  // TODO 6: if btnB.pressed(), advance thresholdIndex (wrap around) and print the new threshold.
  //         Re-run updateState() right away so the change takes effect immediately.

  if (now - lastReadMs >= DHT_INTERVAL_MS) {
    lastReadMs = now;
    readSensor();
    updateState();
    printStatus();
  }

  updateOutputs();
}
