# Topic 11: Debugging Basics

**Week 3** · No new hardware or pattern, just habits. These are the first things to check when something does not work, before you blame the code.

## The order to check things in

Embedded bugs are rarely "the logic is wrong." Suspect them in roughly this order:

1. **Power**: is the device getting the voltage it needs?
2. **Wiring**: right pin, right way round?
3. **Ground**: do all devices share a common ground?
4. **Code**: only after the above are ruled out.

People jump straight to "my code must be wrong" and rewrite logic when the real problem is a loose jumper. Check hardware first. It is faster.

## Multimeter checks

Three checks cover almost everything:

- **Voltage**: probes across power and ground. Expect about 3.3 V (or 5 V on a 5 V rail). If it reads 0 or something odd, that is your problem before any code runs.
- **Continuity** (beep mode): checks whether two points are really connected. Good for broken jumpers and for confirming how a breadboard row connects.
- **Resistance**: confirms an unmarked resistor's value. Measure with the part out of the circuit.

Never measure resistance on a powered circuit.

## Serial print debugging

```cpp
Serial.println("reached setup()");
Serial.printf("sensor value: %d\n", value);
Serial.println("about to call risky_function()");
```

Print *before and after* anything you suspect. If a print never appears, execution is not reaching that line, which rules out half the possible causes. Print the **value and its unit**, not just "here."

## Common beginner mistakes

- **`INPUT_PULLUP` logic is inverted.** Pressed reads `LOW` (Topic 06).
- **Wrong pin numbering.** Silkscreen labels like `D0` are not GPIO numbers. Use the board's official pinout (Topic 03).
- **Floating input pins.** A button that "randomly" triggers usually lacks a pull-up or has a poor connection.
- **Baud rate mismatch.** Garbled serial output means `Serial.begin()` and `monitor_speed` differ (Topic 07).
- **No common ground** between two power sources or boards.
- **Reading the DHT11 too often.** Faster than once per second gives `NaN` (Topic 10).
- **Pin conflicts.** The pot on D8 clashes with SPI SCK (Topic 08).
- **A charge-only USB cable.** The board powers up but never appears for upload.

## Break it on purpose

The fastest way to learn failure signatures is to cause them once, deliberately, while you know the code is good. Do each one, note what you see, then fix it:

| Break this | What you should observe |
| ---------- | ----------------------- |
| Unplug the DHT11 data wire | `NaN` reads and "read failed" |
| Swap SDA and SCL | Bus scan finds nothing |
| Change `Serial.begin(9600)` | Garbled monitor output |
| Remove the button's GND wire | Button never registers, or triggers randomly |
| Remove the LED's resistor leg | LED off, and no other symptoms |
| Disconnect GND on a sensor | Weird readings or total silence |

Write the symptom next to each in your notes. You will recognise them instantly later.

## One change at a time

When something breaks, resist changing five things at once. Change one thing, test, observe, then decide the next step from what you saw. It is slower per step and much faster overall.

## Check yourself

- What are the four things to check, in order?
- What does a missing serial print tell you?
- Which deliberate break was hardest to diagnose?

## What's next

Topic 12 is the Phase 1 checkpoint. This is where these habits get their first real workout.
