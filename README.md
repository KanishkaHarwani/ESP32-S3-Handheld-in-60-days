# ESP32-S3-Handheld-in-60-days

Learn embedded C++ from scratch by building a real product: a **battery-powered ESP32-S3 handheld** with a colour display, 6 buttons, Wi-Fi and a launcher of small apps, one of which is the original **smart dashboard**. 60 days, three phases, one working checkpoint per phase.

> Formerly `ESP32-S3-Smart-Dashboard-in-60-days`.

## Why this repo

Most "learn embedded C++" resources either stay stuck at blinking an LED or jump straight into production firmware with no ramp. This repo is built around one real target you can hold in your hand. You pick up the C++, the RTOS, the networking, the power design and the practices that make firmware maintainable, all in service of that one device.

## What you end up with

- A pocket-sized device: ESP32-S3, 2.0"-2.8" SPI TFT, D-pad + A + B buttons, LiPo battery with USB-C charging
- A launcher menu with apps: Snake, a Wi-Fi scanner, a stopwatch, system/battery info, and the **Smart Dashboard** (sensor data + live API data)
- OTA updates, watchdogs, logging, sleep mode and power-loss recovery
- Optional: custom KiCad PCB and 3D-printed case

## Prerequisites

- Basic programming experience in *any* language (loops, functions, variables). No embedded or C++ experience required.
- A computer with USB, and the patience to debug wiring before code.

## Timeline (60 days)

Planned start: **Mon 2026-10-19**, finish: **Thu 2026-12-17**. Dates are targets; shift them if you slip and note it in `ROADMAP.md`.

| Phase | Folder | Weeks | Ends with |
| ----- | ------ | ----- | --------- |
| 1. Foundations | `Phase-01-Basics/` | 1-2 | Sensor + buttons -> LED/buzzer/serial feedback loop |
| 2. Connectivity & Architecture | `Phase-02-Libraries-IO/` | 3-5 | Live API data parsed and drawn on the TFT via a state machine |
| 3. The Handheld (final project) | `Phase-03-Final_Project/` | 6-9 | Battery-powered handheld with launcher, apps and OTA |

Every phase ends with a **demo**: a photo or short video committed to `resources/demos/`.

### Phase 1: Foundations
Embedded C++, ESP32-S3 architecture, PlatformIO, Git basics, and the core peripherals (GPIO, UART, SPI, I2C). Runs on the Xiao ESP32S3. Checkpoint: read a sensor and buttons, give feedback with LED, buzzer and serial.

### Phase 2: Connectivity & Architecture
Display and graphics, Wi-Fi, HTTP/HTTPS, REST and JSON, FreeRTOS, layered architecture, state machines and driver development. Checkpoint: fetch API data over Wi-Fi, parse it, render it on the TFT, driven by a state machine. Move to the ESP32-S3 DevKitC-1 here once it arrives (see `hardware/README.md`).

### Phase 3: The Handheld
Hardware bring-up (buttons, display, battery divider, charging), the launcher and app framework, apps, power management, OTA and production practices. Checkpoint: the finished handheld, documented.

See [`ROADMAP.md`](ROADMAP.md) for the lesson-by-lesson breakdown and progress tracker.

## Repo structure

```
├── README.md
├── ROADMAP.md
├── LICENSE
├── Phase-01-Basics/
├── Phase-02-Libraries-IO/
├── Phase-03-Final_Project/
├── hardware/
│   └── README.md        <- parts, pin map, power notes
└── resources/
    └── demos/           <- one demo photo/video per phase
```

## How to use this repo

1. Work through phases in order; each assumes the last is done.
2. Each lesson folder gets a short README (concept + what to build) and example code.
3. Build and demo the checkpoint project before moving on.
4. Commit as you go. The repo doubles as your Git practice.

## License

MIT. See [LICENSE](LICENSE).
