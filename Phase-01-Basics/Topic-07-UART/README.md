# Topic 07: UART and the Serial Monitor

**Week 2** · UART is the simplest way two devices exchange data over wires. On your board it is also your window into what the chip is doing. From here on, `Serial` is how you debug everything.

## Baud rate: both sides must agree

UART has no clock wire. Both ends agree in advance on the speed in bits per second (the **baud rate**). If they do not match, you get garbage characters.

```cpp
Serial.begin(115200);   // must match monitor_speed in platformio.ini
```

## Printing: your primary debug tool

```cpp
Serial.println("Hello from the ESP32-S3");
Serial.print("Reading: ");
Serial.println(42);
Serial.printf("Temp: %.1f C\n", 23.5);     // formatted, like C's printf
```

Before you have a display or Wi-Fi, `Serial.println` is how you learn whether your code even reaches a line. Printing through suspect code is normal, professional debugging.

## Reading input: the board can listen too

```cpp
if (Serial.available() > 0) {
  String command = Serial.readStringUntil('\n');
  command.trim();                 // strip trailing whitespace/newline

  if (command == "on") {
    // ...
  }
}
```

Check `Serial.available()` first, or you may block waiting for input that is not there. (`String` is fine for this small use. See Topic 02 for why to be careful with it in tight loops.)

## Non-blocking status printing

```cpp
static uint32_t lastPrint = 0;
if (millis() - lastPrint >= 2000) {
  lastPrint = millis();
  Serial.println("still alive");
}
```

## A tiny command parser

Commands with a number (`threshold 30`) are common in this repo:

```cpp
if (command.startsWith("threshold ")) {
  float value = command.substring(10).toFloat();
  // validate, then apply
}
```

Always validate input. `toFloat()` returns 0 for text it cannot parse.

## About D6 and D7

On the Xiao, D6/D7 are the hardware UART pins (`Serial1`). You use them for buttons in Phase 1, which is fine because the serial monitor goes over USB, not those pins.

## Check yourself

- What happens if `Serial.begin()` and `monitor_speed` disagree?
- Why check `Serial.available()` before reading?
- How would you add a `reset` command?

## What's next

The example prints a periodic status message and accepts text commands to control an LED. Topic 08 covers SPI, then Topic 09 reads a real I²C sensor and prints it over this same connection.
