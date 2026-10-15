# Example — Temperature Alert System

The Phase 1 checkpoint build. Everything from this phase, in one program.

## Wiring

| Component | Pin |
|---|---|
| Temp/humidity sensor (I²C) | SDA/SCL (as in Topic 09) |
| LED | `D1` (through resistor, to GND) |
| Buzzer | `D3` (to GND) |
| Button | `D2` (other leg to GND, `INPUT_PULLUP`) |

## Library

Same as Topic 09 — add to `platformio.ini`:

```ini
lib_deps =
    adafruit/Adafruit AHTX0
```

(already included in the `platformio.ini` provided in this folder)

## The exercise

`main_starter.cpp` has the full structure — pin setup, sensor init, serial command parsing skeleton — with `// TODO` markers for the parts that tie Phase 1's concepts together:

1. Non-blocking sensor read + status print every 2 seconds (Topic 07 pattern)
2. Debounced button press that starts a 10-second mute window (Topic 06 pattern, reused)
3. Alert logic: LED + buzzer on when `temp > threshold` and not muted
4. Parsing the `threshold <n>` serial command to update the threshold live

`main_solution.cpp` is the completed reference — build the starter yourself first. This one's worth genuinely attempting; it's the whole point of the phase.

## Build, upload, monitor

```bash
pio run
pio run --target upload
pio device monitor
```

## Expected behavior

```
Sensor ready. Threshold: 28.0C
[status] temp=23.4C humidity=48.1% muted=false
[status] temp=23.6C humidity=48.0% muted=false
```

Warm the sensor above the threshold (cup your hand around it) and you should see:

```
[ALERT] temp=28.7C exceeds threshold 28.0C
```

...with the LED and buzzer active. Press the button — alert silences for 10 seconds (LED still indicates the condition, buzzer stays quiet), then resumes if still over threshold.

Try typing `threshold 35` — the alert should stop immediately since the new threshold is higher than the current reading. Typing `status` prints the current state on demand.

## If something's not working

Work through Topic 10's checklist: power → wiring → ground → code. Confirm the I²C scan (Topic 09) still finds your sensor before assuming the alert logic is broken.
