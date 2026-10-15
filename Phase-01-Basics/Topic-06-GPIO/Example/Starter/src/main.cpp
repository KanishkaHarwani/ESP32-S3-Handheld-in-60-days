// Topic 06 Starter: GPIO (outputs, inputs, pull-ups, non-blocking debounce, PWM fade, ADC)
//
// Wiring (Phase 1 table in hardware/README.md):
//   Green LED + resistor -> D0     Red LED + resistor -> D1
//   Button A -> D6 to GND          Button B -> D7 to GND   (internal pull-ups)
//   Potentiometer wiper  -> D8     (outer legs to 3.3 V and GND)
//
// Behaviour to build:
//   Button A press : toggle the green LED
//   Button B press : start/stop the red LED breathing (PWM fade)
//   Potentiometer  : controls the fade speed
//   Serial         : print the pot value twice a second

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
    // TODO 1: set the pin to INPUT_PULLUP, then initialise raw_ and stable_
    //         with digitalRead(pin_) and lastChange_ with millis().
  }

  // Returns true exactly once per press (after the signal has been stable).
  bool pressed() {
    // TODO 2: read the pin. If it differs from raw_, store it and restart the timer.
    //         When the reading has been unchanged for debounceMs_ and differs from stable_,
    //         accept it as the new stable_ state. Return true if the new state is LOW
    //         (buttons connect to GND, so LOW means pressed).
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

  // TODO 3: configure the green LED pin as OUTPUT and start it LOW.
  pwmBegin(PIN_LED_RED);
  btnA.begin();
  btnB.begin();
  analogReadResolution(12);  // ADC range 0..4095
}

void loop() {
  uint32_t now = millis();

  // TODO 4: if btnA.pressed(), toggle greenOn and write it to the green LED.
  // TODO 5: if btnB.pressed(), toggle `fading`. When it stops, set the red LED duty to 0.

  // TODO 6: read the pot (analogRead(PIN_POT)) and map 0..4095 to a fade interval
  //         of 30 ms (slow) .. 2 ms (fast). Use map().
  uint32_t fadeIntervalMs = 10;

  if (fading && now - lastFadeMs >= fadeIntervalMs) {
    lastFadeMs = now;
    // TODO 7: change duty by `step`. When it reaches 255 or 0, reverse the direction
    //         (step = -step) and clamp duty. Then call pwmWrite(PIN_LED_RED, duty).
  }

  if (now - lastPrintMs >= 500) {
    lastPrintMs = now;
    // TODO 8: print the raw pot value, green LED state and fade state.
  }
}
