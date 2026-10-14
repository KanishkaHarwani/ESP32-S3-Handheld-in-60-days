# ESP32-S3-Handheld-in-90-days

Learn embedded C++ from scratch by building a real product: a **battery-powered ESP32-S3 handheld** with a colour display, 6 buttons, Wi-Fi and a launcher of small apps, including live **weather**, a **flight tracker** and a **smart dashboard**. 13 weeks (about 90 days), three phases, one working checkpoint per phase.

> Formerly `ESP32-S3-Smart-Dashboard-in-60-days`.

## Why this repo

Most "learn embedded C++" resources either stay stuck at blinking an LED or jump straight into production firmware with no ramp. This repo is built around one real target you can hold in your hand. You pick up the C++, the RTOS, the networking, the power design and the practices that make firmware maintainable, all in service of that one device.

## What you end up with

- A pocket-sized device: ESP32-S3, 2.8" SPI TFT, D-pad + A + B buttons, DHT11 temperature/humidity sensor, LiPo battery with USB-C charging
- A launcher menu with apps:
  - **Snake** and **stopwatch / system info** (offline apps)
  - **Weather** (live API data) and **Flight tracker** (aircraft near you)
  - **Wi-Fi scanner**
  - **Smart Dashboard**: local sensor + weather + flight count on one screen
- OTA updates, watchdogs, logging, sleep mode and power-loss recovery
- Version 1 on a breadboard, version 2 on perfboard

**Bonus, after the deadline and only if everything works:** custom KiCad PCB and a 3D-printed case.

## Prerequisites

- Basic programming experience in *any* language (loops, functions, variables). No embedded or C++ experience required.
- A computer with USB, and the patience to debug wiring before code.

## Timeline

Planned start: **Mon 2026-10-19**, finish: **Sun 2027-01-17** (13 weeks). Dates are targets. If you slip, shift the dates and add a note in `ROADMAP.md`. **A phase is finished when its checkpoint works, so slip the dates rather than skip the checkpoint.**

| Phase | Folder | Weeks (dates) | Ends with |
| ----- | ------ | ------------- | --------- |
| 1. Foundations | `Phase-01-Basics/` | 1-3 (19 Oct - 8 Nov) | DHT11 + buttons -> LED/buzzer/serial feedback loop |
| 2. Connectivity & Architecture | `Phase-02-Libraries-IO/` | 4-8 (9 Nov - 13 Dec) | Live weather + nearby flights on the TFT via a state machine and FreeRTOS tasks |
| 3. The Handheld (final project) | `Phase-03-Final_Project/` | 9-13 (14 Dec - 17 Jan) | Battery-powered handheld with launcher, apps and OTA, rebuilt on perfboard |

Every phase ends with a **demo**: a photo or short video committed to `resources/demos/`.

See [`ROADMAP.md`](ROADMAP.md) for the week-by-week plan and progress tracker, and [`hardware/README.md`](hardware/README.md) for parts, pin maps and power notes.

## Live data (APIs)

| Data | Source | Notes |
| ---- | ------ | ----- |
| Weather | Open-Meteo | Free tier is non-commercial and requires attribution (CC BY 4.0). Limits: 600 calls/min, 5,000/hour, 10,000/day |
| Flights | OpenSky Network (`/states/all`, bounding box) | Anonymous: 400 credits/day. Registered (OAuth2): 4,000/day. A small bounding box costs 1 credit per request |
| Alternatives | adsb.lol and others | Check each service's current terms before relying on it |

Polling budget matters: with anonymous OpenSky access you can only afford one flight request every ~3.6 minutes if it ran all day, so the Flight app only polls while it is open and caches results.

## Secrets: never commit them

This repo is public. Wi-Fi passwords, API client IDs/secrets and your coordinates go in `include/secrets.h`, which is listed in `.gitignore`. Commit a `secrets.example.h` with placeholder values instead.

## Repo structure

```
├── README.md
├── ROADMAP.md
├── LICENSE
├── .gitignore               <- includes secrets.h
├── Phase-01-Basics/         <- Topic-01 ... Topic-12 (Example/Starter + Example/Solution)
├── Phase-02-Libraries-IO/   <- Topic-01 ... Topic-12 (Example/Starter + Example/Solution)
├── Phase-03-Final_Project/  <- Lesson-01 ... Lesson-14 + src/
├── hardware/
│   └── README.md            <- parts, pin maps, power notes
└── resources/
    └── demos/               <- one demo photo/video per phase
```

Phases 1 and 2 use `Topic-NN-Name/` folders, each with a README and an `Example/` split into `Starter/` (gaps to fill in) and `Solution/`. Phase 3 uses `Lesson-NN-Name/` folders for notes and a single `src/` for the firmware, organised as `drivers/`, `tasks/`, `net/`, `ui/`, `apps/`.

## How to use this repo

1. Work through phases in order; each assumes the last is done.
2. Try each `Starter/` before opening its `Solution/`.
3. Build and demo the checkpoint project before moving on.
4. Commit as you go. The repo doubles as your Git practice.

## License

MIT. See [LICENSE](LICENSE).
