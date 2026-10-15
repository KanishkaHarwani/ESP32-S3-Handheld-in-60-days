# Topic 11 — Checkpoint Project: Temperature Alert System

This is where Phase 1 comes together. No new concepts here — just combining everything from Topics 02–10 into one real, working device.

## What you're building

A small alert system: it continuously reads temperature from the I²C sensor, and reacts when it crosses a threshold — LED and buzzer turn on, a debounced button lets you mute the alert, and everything is observable and controllable over serial. If you can build and understand this end to end, Phase 1 has done its job.

## What it touches from this phase

| Concept | Where it shows up |
|---|---|
| Embedded C++ (Topic 02) | Clean state tracking instead of scattered global flags |
| GPIO (Topic 06) | LED + buzzer output, debounced button input |
| UART (Topic 07) | Status printing + live commands (`status`, `threshold <n>`) |
| I²C (Topic 09) | Real temperature/humidity readings |
| Debugging habits (Topic 10) | You'll lean on Serial prints and the multimeter if wiring misbehaves |

## Behavior

- Every 2 seconds: read temperature, print a status line
- If temperature exceeds the threshold (default 28°C) **and** the alert isn't muted: LED on, buzzer sounds
- Pressing the button mutes the alert for 10 seconds (debounced — one press, one mute, no double-triggers)
- Typing `status` into serial prints current temp, threshold, and mute state
- Typing `threshold 30` (or any number) changes the alert threshold live, no re-flashing needed

## Wiring

- Temp/humidity sensor: I²C (same as Topic 09)
- LED: pin `D1` (through resistor, to GND) — same as Topic 06
- Buzzer: pin `D3` (or any free digital pin) — direct to GND
- Button: pin `D2`, other leg to GND, using `INPUT_PULLUP` — same as Topic 06

## Where the code lives

Full instructions, starter, and solution are in `Example/`.

## Done when

- You understand every line of the solution, not just that it runs
- You can explain, out loud, why the button uses debounce and why the sensor read uses non-blocking timing instead of `delay()`
- It runs continuously without hanging or needing a reset

Once this is solid, move on to `phase2-connectivity-architecture/` — displays, Wi-Fi, and real software architecture.
