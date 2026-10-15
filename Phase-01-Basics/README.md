# Phase 1: Foundations

**Weeks 1-3 (19 Oct - 8 Nov 2026)**
**Board:** Seeed Xiao ESP32S3
**Parts:** breadboard, LEDs, buttons, buzzer, DHT11, potentiometer, multimeter

## Goal

Get from "never touched a microcontroller" to reading sensors, driving outputs and debugging a small program on real hardware. You finish with a working feedback loop: DHT11 + buttons controlling LED, buzzer and serial output.

## Topics

| # | Topic | Week | Example |
| - | ----- | ---- | ------- |
| 01 | [Embedded Systems Intro](Topic-01-Embedded-Systems-Intro/) | 1 | - |
| 02 | [Embedded C++ Essentials](Topic-02-Embedded-CPP-Essentials/) | 1 | Starter + Solution |
| 03 | [ESP32-S3 Architecture](Topic-03-ESP32S3-Architecture/) | 2 | - |
| 04 | [PlatformIO Toolchain](Topic-04-PlatformIO-Toolchain/) | 1 | Starter + Solution |
| 05 | [Git and GitHub Basics](Topic-05-Git-GitHub-Basics/) | 1 | - |
| 06 | [GPIO](Topic-06-GPIO/) | 2 | Starter + Solution |
| 07 | [UART](Topic-07-UART/) | 2 | Starter + Solution |
| 08 | [SPI Concepts](Topic-08-SPI-Concepts/) | 3 | Loopback test |
| 09 | [I2C](Topic-09-I2C/) | 3 | Starter + Solution |
| 10 | [DHT11 Sensor](Topic-10-DHT11-Sensor/) | 3 | Starter + Solution |
| 11 | [Debugging Basics](Topic-11-Debugging-Basics/) | 3 | - |
| 12 | [Checkpoint Project](Topic-12-Checkpoint-Project/) | 3 | Starter + Solution |

## Study order

Folder numbers are not the order you work in. Follow `ROADMAP.md`:

- **Week 1:** 01 -> 04 -> 02 -> 05 (you need the toolchain before the C++ exercises)
- **Week 2:** 03 -> 06 -> 07
- **Week 3:** 08 -> 09 -> 10 -> 11 -> 12

## Demos

- Week 1: blink + serial "hello" committed
- Week 2: buttons + LED + PWM fade
- Week 3: short video of the checkpoint

Save demo photos/videos to `../resources/demos/`.

## Checkpoint (finishes the phase)

**Topic 12:** read the DHT11, use two buttons to change behaviour, and give feedback through the LED, buzzer and serial monitor. A failed DHT11 read must be handled, not ignored. Do not start Phase 2 until this works.

## Wiring

See `../hardware/README.md` ("Phase 1 wiring"). Verify against the Xiao ESP32S3 pinout before powering anything. Power the DHT11 from 3.3 V.

## How to work

1. Read the topic README.
2. Try `Example/Starter/` before opening `Example/Solution/`.
3. Commit after each topic.
4. Tick the item off in `ROADMAP.md`.
