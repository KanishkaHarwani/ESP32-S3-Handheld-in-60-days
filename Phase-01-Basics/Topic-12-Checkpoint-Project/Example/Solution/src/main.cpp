// Topic 12 Solution: Phase 1 checkpoint
// DHT11 + buttons -> LED / buzzer / serial feedback loop
//
// Wiring (Phase 1 table in hardware/README.md):
//   Green LED -> D0   Red LED -> D1   Buzzer -> D2 (active buzzer)   DHT11 data -> D3
//   Button A -> D6 to GND   Button B -> D7 to GND
//
// Behaviour:
//   - Reads the DHT11 every 2 s.
//   - Temperature below the threshold : green LED on, quiet.
//   - Temperature at/above threshold  : red LED on, buzzer beeps (ALARM).
//   - Button A : mute / unmute the alarm buzzer.
//   - Button B : cycle the threshold 26 -> 28 -> 30 -> 32 C and back.
//   - 3 failed reads in a row          : SENSOR_ERROR, LEDs alternate, buzzer off.
//   - Prints a status line to serial after every read.
//
// Tip for testing: warm the sensor with your fingers (or breathe on it) to cross
// the threshold, and unplug the data wire to trigger SENSOR_ERROR.
// If your buzzer is passive (needs a tone), replace the digitalWrite on PIN_BUZZER
// with a PWM tone like in Topic 06.

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

static const char *stateName(State s) {
  switch (s) {
    case State::OK: return "OK";
    case State::ALARM: return "ALARM";
    case State::SENSOR_ERROR: return "SENSOR_ERROR";
  }
  return "?";
}

// Debounced button from Topic 06.
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

static float threshold() { return THRESHOLDS_C[thresholdIndex]; }

static void readSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    if (consecutiveFails < 255) consecutiveFails++;
    return;  // keep the last good values
  }
  consecutiveFails = 0;
  lastTempC = t;
  lastHumidity = h;
}

static void updateState() {
  State previous = state;

  if (consecutiveFails >= MAX_FAILS || isnan(lastTempC)) {
    // No trustworthy data: after the first failures we cannot judge the temperature.
    state = (consecutiveFails >= MAX_FAILS) ? State::SENSOR_ERROR : state;
  } else if (lastTempC >= threshold()) {
    state = State::ALARM;
  } else if (state == State::ALARM && lastTempC >= threshold() - HYSTERESIS_C) {
    state = State::ALARM;  // hysteresis: stay in alarm until clearly below the threshold
  } else {
    state = State::OK;
  }

  if (previous == State::ALARM && state != State::ALARM) {
    muted = false;  // next alarm should be audible again
  }
  if (state != previous) {
    Serial.printf("state: %s -> %s\n", stateName(previous), stateName(state));
  }
}

static void updateOutputs() {
  uint32_t now = millis();

  switch (state) {
    case State::OK:
      digitalWrite(PIN_LED_GREEN, HIGH);
      digitalWrite(PIN_LED_RED, LOW);
      digitalWrite(PIN_BUZZER, LOW);
      break;

    case State::ALARM: {
      digitalWrite(PIN_LED_GREEN, LOW);
      digitalWrite(PIN_LED_RED, HIGH);
      bool beepPhase = (now % 1000) < 100;  // 100 ms on, 900 ms off
      digitalWrite(PIN_BUZZER, (!muted && beepPhase) ? HIGH : LOW);
      break;
    }

    case State::SENSOR_ERROR: {
      bool phase = (now / 250) % 2 == 0;  // swap every 250 ms
      digitalWrite(PIN_LED_GREEN, phase ? HIGH : LOW);
      digitalWrite(PIN_LED_RED, phase ? LOW : HIGH);
      digitalWrite(PIN_BUZZER, LOW);
      break;
    }
  }
}

static void printStatus() {
  if (isnan(lastTempC)) {
    Serial.printf("no valid reading yet thr=%.0f C state=%s muted=%s fails=%u\n", threshold(),
                  stateName(state), muted ? "yes" : "no", (unsigned)consecutiveFails);
    return;
  }
  Serial.printf("T=%.1f C RH=%.0f %% thr=%.0f C state=%s muted=%s fails=%u\n", lastTempC,
                lastHumidity, threshold(), stateName(state), muted ? "yes" : "no",
                (unsigned)consecutiveFails);
}

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

  if (btnA.pressed()) {
    muted = !muted;
    Serial.printf("buzzer %s\n", muted ? "muted" : "unmuted");
  }

  if (btnB.pressed()) {
    thresholdIndex = (thresholdIndex + 1) % THRESHOLD_COUNT;
    Serial.printf("threshold now %.0f C\n", threshold());
    updateState();  // apply the new threshold immediately
  }

  if (now - lastReadMs >= DHT_INTERVAL_MS) {
    lastReadMs = now;
    readSensor();
    updateState();
    printStatus();
  }

  updateOutputs();
}
