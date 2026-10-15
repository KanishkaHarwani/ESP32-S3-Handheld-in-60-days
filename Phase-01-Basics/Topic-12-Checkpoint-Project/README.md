# Topic 12: Checkpoint Project: Temperature Alert System

**Week 3** · This is where Phase 1 comes together. No new concepts, just everything from Topics 02-11 in one working device. **Do not start Phase 2 until this works.**

## What you are building

A small alert system. It reads the DHT11 every 2 seconds and reacts when the temperature crosses a threshold: the red LED and buzzer turn on, a debounced button mutes the alert, and everything is observable and controllable over serial. A failed sensor read is handled, not ignored.

## What it uses

| Concept | Where it shows up |
| ------- | ----------------- |
| Embedded C++ (Topic 02) | A struct for sensor state, a class or functions for the alert logic |
| GPIO (Topic 06) | LED and buzzer outputs, debounced button inputs |
| UART (Topic 07) | Status printing and live commands |
| DHT11 (Topic 10) | Temperature and humidity, with failed-read handling |
| Debugging (Topic 11) | Serial prints and the multimeter when wiring misbehaves |

## Wiring

Matches `hardware/README.md` ("Phase 1 wiring").

| Part | Pin |
| ---- | --- |
| Green LED (+ resistor) | D0 |
| Red LED (+ resistor) | D1 |
| Buzzer | D2 |
| DHT11 data | D3 |
| Button A (to GND, `INPUT_PULLUP`) | D6 |
| Button B (to GND, `INPUT_PULLUP`) | D7 |

DHT11 powered from 3.3 V.

## Behaviour

- **Every 2 seconds:** read the DHT11 and print a status line.
- **Normal:** green LED on, red LED and buzzer off.
- **Alert:** temperature above the threshold (default 28 °C) and not muted: red LED on, buzzer sounds, green LED off.
- **Button A:** mutes the alert for 10 seconds (debounced: one press, one mute).
- **Button B:** cycles the threshold through 26 / 28 / 30 / 32 °C.
- **Failed read:** keep the last good value, never trigger an alert from bad data, and blink the green LED quickly. After 5 failures in a row, print `SENSOR ERROR`.
- **Serial commands:**
  - `status`: print temperature, humidity, threshold, mute state, failure count
  - `threshold 30`: set the threshold live, no re-flash (validate the number)

## Rules

- No `delay()` in the main loop. Use `millis()` timing.
- No hard-coded magic numbers scattered about: pins and thresholds are named constants.
- The alert logic must be separate from the pin-reading code, so you can reason about it on its own.

## Where the code lives

Full instructions, starter and solution are in `Example/`.

## Done when

- You understand every line of the solution, not just that it runs.
- You can explain why the buttons use debounce and why timing uses `millis()` instead of `delay()`.
- Unplugging the DHT11 does not crash or false-alarm the device, and replugging it recovers.
- It runs for 10+ minutes without hanging or needing a reset.
- A short demo video is saved to `../../resources/demos/`, and `ROADMAP.md` is ticked.

## What's next

Phase 2 (`../../Phase-02-Libraries-IO/`): displays, Wi-Fi and real software architecture.
