# Topic 03: ESP32-S3 Architecture

**Week 2** · No code. A mental map of the chip, so later topics ("this runs on core 1", "that lives in flash") make sense instead of feeling like magic.

## Two cores, not one

The ESP32-S3 has **two CPU cores** (Xtensa LX7, up to 240 MHz each). Simple Arduino sketches use one core without you noticing, but this matters later:

- **Phase 2 (FreeRTOS):** you will run separate tasks (sensor, networking, display) that can genuinely run in parallel.
- The Wi-Fi and Bluetooth stacks use the dual-core design internally.

## Memory: three things to know

| Type | What it is | Xiao ESP32S3 | DevKitC-1 N16R8 |
| ---- | ---------- | ------------ | --------------- |
| **Flash** | Compiled program; persists after power-off | 8 MB | 16 MB |
| **SRAM** | Fast working memory: variables, stacks | ~512 KB | ~512 KB |
| **PSRAM** | Extra, slower RAM for big buffers (framebuffers, JSON) | 8 MB | 8 MB |

Check your exact board's datasheet, since variants differ.

**RAM is small and fixed.** There is no swap. This is why fixed-width types and avoiding runtime allocation matter.

### A rough memory map

```
Flash  ->  your program (code), constants, filesystem/NVS
SRAM   ->  global variables, task stacks, heap
PSRAM  ->  large buffers you place there on purpose (Phase 3)
```

## Peripherals you will use

These are dedicated hardware blocks, not "features":

- **GPIO**: digital in/out and PWM (Topic 06)
- **ADC**: reads analogue voltages, e.g. a potentiometer or battery (Topic 06)
- **UART**: serial communication and your main debug tool (Topic 07)
- **SPI**: fast bus for the TFT and SD card (Topic 08, Phase 2)
- **I²C**: simple two-wire bus for sensors (Topic 09)
- **Wi-Fi / Bluetooth**: built in (Phase 2)

## The Xiao ESP32S3 pinout

The Xiao exposes **11 usable GPIOs, labelled D0-D10**. The `D` labels are not the same as GPIO numbers, so always use the `D` names in code.

| Label | Common use in this repo |
| ----- | ----------------------- |
| D0 / D1 | LEDs (Phase 1), TFT CS / DC (Phase 2) |
| D2 | Buzzer (Phase 1), TFT RST (Phase 2) |
| D3 | DHT11 (Phase 1), TFT backlight (Phase 2) |
| D4 / D5 | I²C SDA / SCL (Phase 1) |
| D6 / D7 | Buttons A / B (also UART pins; fine, since the monitor uses USB) |
| D8 / D9 / D10 | SPI SCK / MISO / MOSI; also the pot (D8) in Phase 1 |

See `../../hardware/README.md` for full wiring tables. Eleven pins is why Phase 3 moves to the DevKitC-1: TFT + 6 buttons + SD does not fit.

## Strapping and reserved pins (DevKitC-1)

On the bigger board some pins are special: 0, 3, 45, 46 (strapping, they set boot mode), 19/20 (USB), 26-32 (flash), 33-37 (octal PSRAM), 48 (onboard RGB LED). You will avoid these in Phase 3.

## Why the S3 specifically

- **Native USB**: flashing and serial over the board's USB port, no separate USB-serial chip needed.
- Vector instructions for ML workloads (not used here).
- It is a current, well-supported chip with good tooling.

## Check yourself

- Where does your program live when power is off?
- Why can the Xiao not run the final handheld?
- Why does "D6" not equal "GPIO6"?

## What's next

Topic 06 starts using these pins for real.
