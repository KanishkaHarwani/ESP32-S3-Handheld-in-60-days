# Topic 06: GPIO

**Week 2** · GPIO (General Purpose Input/Output) is the most basic thing a chip does: read a voltage, or set one. Everything else in this repo is built on top of it.

## Digital output

```cpp
pinMode(LED_PIN, OUTPUT);
digitalWrite(LED_PIN, HIGH);  // ~3.3 V out
digitalWrite(LED_PIN, LOW);   // 0 V out
```

Always put a resistor (about 220 Ω-1 kΩ) in series with an LED. The pin cannot safely drive it directly.

## Digital input

```cpp
pinMode(BUTTON_PIN, INPUT_PULLUP);
bool pressed = (digitalRead(BUTTON_PIN) == LOW);
```

**Why `INPUT_PULLUP`?** An unconnected pin "floats" and reads random noise. `INPUT_PULLUP` uses an internal resistor to hold the pin HIGH, so a button wired between the pin and GND gives a clean LOW when pressed. The logic is inverted (`LOW` means pressed). This trips everyone up once.

## Debounce, without blocking

A mechanical button's contacts bounce for a few milliseconds, which the chip sees as several presses. Accept a new state only after it has been stable for a short time, and never use `delay()` for it:

```cpp
bool lastReading = HIGH;
bool stableState = HIGH;
uint32_t lastChangeMs = 0;

bool buttonPressedEvent() {            // true once per press
  bool reading = digitalRead(BUTTON_PIN);
  if (reading != lastReading) {
    lastChangeMs = millis();
    lastReading = reading;
  }
  if (millis() - lastChangeMs > 30 && reading != stableState) {
    stableState = reading;
    if (stableState == LOW) return true;
  }
  return false;
}
```

`millis()` returns milliseconds since boot. `delay()` freezes the whole program; `millis()` does not.

## PWM: fake analogue output

Pins are only HIGH or LOW. PWM (Pulse Width Modulation) switches fast between them at a chosen ratio (the duty cycle). A dimmed LED is flickering faster than your eye can see:

```cpp
analogWrite(LED_PIN, 128);   // about 50% duty cycle (0-255)
```

A fade is just a value that changes over time:

```cpp
static uint8_t level = 0;
static int8_t  step  = 5;
static uint32_t lastMs = 0;

if (millis() - lastMs >= 20) {
  lastMs = millis();
  level += step;
  if (level == 0 || level == 255) step = -step;
  analogWrite(LED_PIN, level);
}
```

## ADC: reading analogue voltages

The ADC turns a voltage into a number. The ESP32-S3's ADC is 12-bit, so 0 V to about 3.3 V maps to 0-4095:

```cpp
int raw = analogRead(POT_PIN);                   // 0-4095
uint32_t mv = analogReadMilliVolts(POT_PIN);     // calibrated millivolts
uint8_t brightness = map(raw, 0, 4095, 0, 255);
```

Wire the potentiometer's outer legs to 3.3 V and GND, and the middle leg (wiper) to the ADC pin. Readings are slightly noisy and not perfectly linear, especially near 0 V and 3.3 V. Never feed a pin more than 3.3 V.

## Phase 1 pins (Xiao)

| Part | Pin |
| ---- | --- |
| Green LED | D0 |
| Red LED | D1 |
| Potentiometer | D8 |
| Button A / B | D6 / D7 |

## Check yourself

- Why does a pressed button read `LOW`?
- Why use `millis()` instead of `delay()` for debounce?
- What number does `analogRead` return at 1.65 V?

## What's next

The example combines all of it: a debounced button toggles an LED, the potentiometer sets brightness, and a PWM fade is the stretch goal. Topic 07 adds UART so you can see what the program is doing.
