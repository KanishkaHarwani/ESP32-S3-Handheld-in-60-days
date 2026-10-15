# Topic 10 — Debugging Basics

No new hardware or code pattern here — just habits. These are the first things to check whenever something doesn't work, before you assume the code is wrong.

## The order to check things in

Embedded bugs are rarely "the logic is wrong." Far more often, it's one of these, roughly in the order to suspect them:

1. **Power** — is the device actually getting the voltage it needs?
2. **Wiring** — is everything connected to the right pin, the right way round?
3. **Ground** — do all your devices share a common ground?
4. **Code** — only after the above are ruled out.

Beginners (and experienced people too) tend to jump straight to "my code must be wrong" and start rewriting logic, when the actual problem is a loose jumper wire. Check hardware first — it's faster.

## Multimeter checks worth knowing

You don't need to be a multimeter expert — three checks cover almost everything:

**Voltage** — put the probes across power and ground on your breadboard rail. You should see close to 3.3V (or 5V, depending what you're powering). If it reads 0 or something odd, that's your problem, before any code runs.

**Continuity** (the beep mode) — checks if two points are actually electrically connected. Great for verifying a jumper wire isn't broken, or that a breadboard row is actually connected the way you think it is.

**Resistance** — mostly useful for confirming an unmarked resistor's value before you use it (color bands can be hard to read, especially on tiny ones).

## Serial print debugging

This is your main tool from here on (Topic 07). When something isn't behaving:

```cpp
Serial.println("reached setup()");
Serial.printf("sensor value: %d\n", value);
Serial.println("about to call risky_function()");
```

Print *before and after* anything you suspect. If a print statement never shows up, you now know execution isn't reaching that line — that alone rules out half the possible causes.

## Common beginner mistakes worth remembering

- **`INPUT_PULLUP` logic is inverted** — pressed usually reads `LOW`, not `HIGH` (Topic 06). Easy to forget, easy to "fix" by rewriting logic that was actually already correct.
- **Wrong pin numbering** — silkscreen labels on a board (like `D0`) don't always match the underlying GPIO number used in some libraries. When in doubt, check the board's official pinout diagram.
- **Floating input pins** — an unconnected digital input can read random noise. If a button "randomly" triggers, check you're using a pull-up/pull-down and that wiring is actually solid.
- **Baud rate mismatch** — garbled serial monitor output almost always means `Serial.begin()` and `monitor_speed` in `platformio.ini` don't match (Topic 07).
- **Forgetting common ground** — if you're connecting the ESP32-S3 to an external power source or a second board, and things behave strangely, check they share a ground connection.

## A habit worth building

When something breaks, resist the urge to change five things at once. Change one thing, test, observe — then decide the next change based on what you actually saw. It's slower per-step but dramatically faster overall, since you're not guessing which of five changes fixed (or broke) something.

## What's next

Topic 11 is the Phase 1 checkpoint project — it pulls together GPIO, I²C, and everything above into one working build. This is exactly where these debugging habits get their first real workout.
