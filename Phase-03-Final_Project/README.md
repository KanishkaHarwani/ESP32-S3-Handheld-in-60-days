# Phase 3: The Handheld

**Weeks 9-13 (14 Dec 2026 - 17 Jan 2027)**
**Board:** ESP32-S3 DevKitC-1 (N16R8, 16 MB flash + 8 MB PSRAM)
**Parts:** 2.8" TFT, 6 buttons, DHT11, LiPo (protected), USB-C charger with power path, optional SD card

## Goal

Build the finished product: a battery-powered handheld with a launcher and small apps, OTA updates, watchdogs, logging, sleep and power-loss recovery. Version 1 runs on a breadboard; version 2 is rebuilt on perfboard.

## Lessons

| # | Lesson | Week |
| - | ------ | ---- |
| 01 | [Hardware Bring-up](Lesson-01-Hardware-Bring-up/) | 9 |
| 02 | [Power and Battery](Lesson-02-Power-and-Battery/) | 9 |
| 03 | [Backlight PWM and Double Buffering](Lesson-03-Backlight-and-Double-Buffering/) | 9 |
| 04 | [App Framework and Launcher](Lesson-04-App-Framework-Launcher/) | 10 |
| 05 | [Offline Apps (Snake, Stopwatch, System Info)](Lesson-05-Offline-Apps/) | 10 |
| 06 | [Network Service and Caching](Lesson-06-Network-Service-and-Caching/) | 11 |
| 07 | [Settings and Config](Lesson-07-Settings-and-Config/) | 12 |
| 08 | [OTA Updates](Lesson-08-OTA-Updates/) | 12 |
| 09 | [Power Management](Lesson-09-Power-Management/) | 12 |
| 10 | [Error Handling and Logging](Lesson-10-Error-Handling-and-Logging/) | 12 |
| 11 | [SD Card Logging](Lesson-11-SD-Card-Logging/) (optional) | 12 |
| 12 | [Perfboard v2](Lesson-12-Perfboard-v2/) | 13 |
| 13 | [Stress Tests](Lesson-13-Stress-Tests/) | 13 |
| 14 | [Final README and Build Log](Lesson-14-Final-README-and-Build-Log/) | 13 |

## Apps

| App | Type | Week |
| --- | ---- | ---- |
| Snake | offline | 10 |
| Stopwatch + system/battery info | offline | 10 |
| Weather (Open-Meteo) | network | 11 |
| Flight tracker (OpenSky) | network | 11 |
| Wi-Fi scanner | network | 11 |
| Smart Dashboard (DHT11 + weather + flight count) | network | 11 |

## Firmware layout

```
Phase-03-Final_Project/
├── include/
│   ├── secrets.h            <- git-ignored
│   └── secrets.example.h
├── platformio.ini
└── src/
    ├── drivers/             <- buttons, display, DHT11, battery, SD
    ├── tasks/               <- FreeRTOS tasks
    ├── net/                 <- shared network service, cache, polling budget
    ├── ui/                  <- launcher, widgets, theme
    └── apps/                <- snake, stopwatch, weather, flights, wifi_scan, dashboard
```

Lesson folders hold notes; all firmware lives in `src/`.

## Demos

- Week 9: 6-button test + battery percentage on the TFT
- Week 10: launcher with three apps
- Week 11: all network apps running from the launcher
- Week 12: wireless firmware update
- Week 13: final video of the handheld running

## Go / no-go

**Sun 10 Jan:** if the breadboard v1 is stable, start the perfboard build the following week. If not, spend Week 13 on stability and move the perfboard to Bonus.

## Pin map and power

See `../hardware/README.md` ("Phase 3 proposed pin map" and "Power notes"). Avoid strapping pins (0, 3, 45, 46), USB (19/20), flash (26-32), octal PSRAM (33-37) and the onboard RGB LED (48).

Safety: use a protected LiPo, a proper charger IC with power path, check polarity twice, and measure with the multimeter before connecting the battery for the first time.

## Secrets

Never hardcode Wi-Fi passwords, API credentials or coordinates. Store them in NVS via the settings screen (Lesson 07); use `secrets.h` only for build-time defaults, and keep it out of Git.

## Checkpoint (finishes the phase)

A battery-powered handheld on perfboard that runs the launcher and all apps, updates over the air, and passes the stress tests: Wi-Fi drop, API failure, DHT11 disconnect and low battery.

## Bonus (only after everything above works)

Custom KiCad PCB, 3D-printed case, IMU tilt controls, I2S audio, haptics, and more apps (Pong, Tetris, ISS tracker, stocks ticker).
