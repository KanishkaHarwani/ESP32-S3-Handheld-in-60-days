// Topic 06 Solution: GPIO (outputs, inputs, pull-ups, non-blocking debounce, PWM fade, ADC)
//
// Wiring (Phase 1 table in hardware/README.md):
//   Green LED + resistor -> D0     Red LED + resistor -> D1
//   Button A -> D6 to GND          Button B -> D7 to GND   (internal pull-ups)
//   Potentiometer wiper  -> D8     (outer legs to 3.3 V and GND)
//
// Behaviour:
//   Button A press : toggle the green LED
//   Button B press : start/stop the red LED breathing (PWM fade)
//   Potentiometer  : controls the fade speed
//   Serial         : prints the pot value twice a second

#include <Arduino.h>

constexpr uint8_t PIN_LED_GREEN = D0;
constexpr uint8_t PIN_LED_RED = D1;
constexpr uint8_t PIN_BTN_A = D6;
constexpr uint8_t PIN_BTN_B = D7;
constexpr uint8_t PIN_POT = D8;

// ---------- PWM helper (works on Arduino-ESP32 core 2.x and 3.x) ----------
constexpr uint32_t PWM_FREQ = 5000;
constexpr uint8_t PWM_BITS = 8;  // duty 0..255
constexpr uint8_t PWM_CH = 0;    // only used by core 2.x

static void pwmBegin(uint8_t pin) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(pin, PWM_FREQ, PWM_BITS);
#else
  ledcSetup(PWM_CH, PWM_FREQ, PWM_BITS);
  ledcAttachPin(pin, PWM_CH);
#endif
}

static void pwmWrite(uint8_t pin, uint32_t duty) {
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(pin, duty);
#else
  (void)pin;
  ledcWrite(PWM_CH, duty);
#endif
}

// ---------- Non-blocking debounced button ----------
class Button {
 public:
  explicit Button(uint8_t pin, uint32_t debounceMs = 30) : pin_(pin), debounceMs_(debounceMs) {}

  void begin() {
    pinMode(pin_, INPUT_PULLUP);
    raw_ = stable_ = digitalRead(pin_);
    lastChange_ = millis();
  }

  // Returns true exactly once per press (after the signal has been stable).
  bool pressed() {
    int reading = digitalRead(pin_);
    uint32_t now = millis();

    if (reading != raw_) {  // signal moved: restart the stability timer
      raw_ = reading;
      lastChange_ = now;
    }

    if (now - lastChange_ >= debounceMs_ && raw_ != stable_) {
      stable_ = raw_;
      if (stable_ == LOW) return true;  // buttons connect to GND: LOW = pressed
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

Button btnA(PIN_BTN_A);
Button btnB(PIN_BTN_B);

static bool greenOn = false;
static bool fading = true;
static int duty = 0;
static int step = 5;
static uint32_t lastFadeMs = 0;
static uint32_t lastPrintMs = 0;

void setup() {
  Serial.begin(115200);
  delay(1500);

  pinMode(PIN_LED_GREEN, OUTPUT);
  digitalWrite(PIN_LED_GREEN, LOW);
  pwmBegin(PIN_LED_RED);
  btnA.begin();
  btnB.begin();
  analogReadResolution(12);  // ADC range 0..4095
}

void loop() {
  uint32_t now = millis();

  if (btnA.pressed()) {
    greenOn = !greenOn;
    digitalWrite(PIN_LED_GREEN, greenOn ? HIGH : LOW);
  }

  if (btnB.pressed()) {
    fading = !fading;
    if (!fading) {
      duty = 0;
      pwmWrite(PIN_LED_RED, 0);
    }
  }

  int potRaw = analogRead(PIN_POT);
  // Pot fully left = slow (30 ms per step), fully right = fast (2 ms per step).
  uint32_t fadeIntervalMs = (uint32_t)map(potRaw, 0, 4095, 30, 2);

  if (fading && now - lastFadeMs >= fadeIntervalMs) {
    lastFadeMs = now;
    duty += step;
    if (duty >= 255) {
      duty = 255;
      step = -step;
    } else if (duty <= 0) {
      duty = 0;
      step = -step;
    }
    pwmWrite(PIN_LED_RED, duty);
  }

  if (now - lastPrintMs >= 500) {
    lastPrintMs = now;
    Serial.printf("pot=%d  green=%s  fade=%s\n", potRaw, greenOn ? "on" : "off",
                  fading ? "running" : "stopped");
  }
}
