# Roadmap

Week-by-week plan for the 13-week (about 90-day) build. Check items off as you complete them; this file is the progress tracker. Planned start **2026-10-19**, planned finish **2027-01-17**. Each week has a buffer day (Saturday) and a demo day (Sunday). If you slip, edit the dates and add a dated line under Schedule notes.

Rule: a phase is finished when its checkpoint works. Slip the dates, never skip the checkpoint.

---

## Phase 1: Foundations (Weeks 1-3, 19 Oct - 8 Nov)

Board: Xiao ESP32S3 · breadboard, LEDs, buttons, buzzer, DHT11, potentiometer, multimeter

**Week 1 (19-25 Oct)**
- [ ] Topic 01: Embedded systems intro (constraints, real-time, memory)
- [ ] Topic 04: PlatformIO toolchain (build, upload, monitor, blink)
- [ ] Topic 02: Embedded C++ essentials (types, functions, structs/classes, pointers and references)
- [ ] Topic 05: Git and GitHub (commits, branches, `.gitignore`, keeping secrets out)
- Demo: blink + serial "hello" committed

**Week 2 (26 Oct - 1 Nov)**
- [ ] Topic 03: ESP32-S3 architecture (dual-core, memory map, Xiao pinout)
- [ ] Topic 06: GPIO (outputs, inputs, pull-ups, non-blocking debounce, PWM fade, ADC)
- [ ] Topic 07: UART and the serial monitor as a debug tool
- Demo: buttons + LED + PWM fade

**Week 3 (2-8 Nov)**
- [ ] Topic 08: SPI concepts + loopback test
- [ ] Topic 09: I2C (bus scan, read an I2C sensor)
- [ ] Topic 10: DHT11 single-wire sensor (read, handle failed reads)
- [ ] Topic 11: Debugging basics (serial prints, multimeter, break-it-on-purpose)
- [ ] **Checkpoint project (Topic 12):** DHT11 + buttons -> LED/buzzer/serial feedback loop
- Demo: short video of the checkpoint

---

## Phase 2: Connectivity & Architecture (Weeks 4-8, 9 Nov - 13 Dec)

Board: Xiao ESP32S3 · 2.8" TFT, DHT11, 2 buttons, buzzer

> Order the ESP32-S3 DevKitC-1 (N16R8) by **Mon 16 Nov**. It is needed by Mon 14 Dec.

**Week 4 (9-15 Nov)**
- [ ] Topic 01: TFT displays and graphics (primitives, fonts, sprites, avoiding flicker)
- [ ] Button-test screen (the first handheld UI slice, 2 buttons on the Xiao)
- Demo: button-test screen on the TFT

**Week 5 (16-22 Nov)**
- [ ] Topic 02: Wi-Fi (station mode, reconnect handling)
- [ ] Topic 03: HTTP/HTTPS (requests, TLS basics, certificates)
- [ ] Topic 04: REST APIs (call Open-Meteo, status codes, timeouts)
- Demo: raw weather data on the TFT

**Week 6 (23-29 Nov)**
- [ ] Topic 05: JSON (ArduinoJson, filtering big responses, mapping to structs)
- [ ] Topic 06: Flight and live-data APIs (OpenSky bounding box, auth, rate-limit budget, caching)
- [ ] Topic 07: FreeRTOS, part 1 (tasks, `vTaskDelay`)
- Demo: parsed weather + nearby flight count on the TFT

**Week 7 (30 Nov - 6 Dec)**
- [ ] Topic 07: FreeRTOS, part 2 (queues, task design)
- [ ] Topic 08: Software architecture (drivers vs logic vs UI)
- [ ] Topic 09: State machines (CONNECTING -> FETCHING -> DISPLAYING -> ERROR)
- Demo: tasks + state machine skeleton running

**Week 8 (7-13 Dec)**
- [ ] Topic 10: Driver development (reusable `Buttons` and `DHT11` drivers)
- [ ] Topic 11: Debugging, intermediate (log levels, backtraces, watchdog timers)
- [ ] **Checkpoint project (Topic 12):** weather + nearby flights on the TFT, state machine + FreeRTOS tasks, survives Wi-Fi drops and API failures
- Demo: video of live data, then pull the Wi-Fi

---

## Phase 3: The Handheld (Weeks 9-13, 14 Dec - 17 Jan)

Board: ESP32-S3 DevKitC-1 (N16R8) · TFT, 6 buttons, DHT11, LiPo, charger, optional SD card

**Week 9 (14-20 Dec): Hardware bring-up**
- [ ] Lesson 01: Wire the DevKitC-1 pin map (see `hardware/README.md`), TFT + all 6 buttons working
- [ ] Lesson 02: Power and battery (LiPo safety, battery divider -> ADC, percentage curve, protected cell, charger with power path)
- [ ] Lesson 03: Backlight PWM and double-buffered drawing in PSRAM
- Demo: 6-button test + battery percentage on the TFT

**Week 10 (21-27 Dec): Launcher and offline apps**
- [ ] Lesson 04: App framework and launcher (launcher -> app -> back, press/hold/release events)
- [ ] Lesson 05: Snake
- [ ] Lesson 05: Stopwatch + system/battery info
- Demo: launcher with three apps

**Week 11 (28 Dec - 3 Jan): Network apps**
- [ ] Lesson 06: Shared network service with caching and a polling budget
- [ ] Weather app (Open-Meteo)
- [ ] Flight tracker app (OpenSky)
- [ ] Wi-Fi scanner
- [ ] Smart Dashboard (DHT11 + weather + flight count)
- Demo: all network apps running from the launcher

**Week 12 (4-10 Jan): Production practices**
- [ ] Lesson 07: Settings and config (NVS, Wi-Fi setup, location, units; no hardcoded secrets)
- [ ] Lesson 08: OTA updates (versioning, rollback safety)
- [ ] Lesson 09: Power management (idle dimming, deep sleep, wake on button)
- [ ] Lesson 10: Error handling, logging, watchdogs, power-loss recovery
- [ ] Optional, Lesson 11: SD card logging
- [ ] **Go/no-go (Sun 10 Jan):** if the breadboard v1 is stable, start the perfboard build next week
- Demo: wireless firmware update

**Week 13 (11-17 Jan): Perfboard v2, polish and ship**
- [ ] Lesson 12: Build version 2 on perfboard (layout on paper, solder, continuity test, bring-up)
- [ ] Lesson 13: Stress tests (Wi-Fi drop, API failure, DHT11 disconnect, low battery)
- [ ] Lesson 14: Final README/build log with photos and wiring diagram
- Demo: final video of the handheld running

---

## Bonus (after 17 Jan, only if everything works)

- [ ] Custom KiCad PCB
- [ ] 3D-printed case
- [ ] IMU tilt controls (BNO085), I2S audio, haptics
- [ ] More apps: Pong, Tetris, ISS tracker, crypto/stocks ticker

---

## Progress

| Phase | Planned dates | Status |
| ----- | ------------- | ------ |
| Phase 1: Foundations | 19 Oct - 8 Nov | Not started |
| Phase 2: Connectivity & Architecture | 9 Nov - 13 Dec | Not started |
| Phase 3: The Handheld | 14 Dec - 17 Jan | Not started |
| Bonus: PCB and case | after 17 Jan | Not planned |

Schedule notes:
- Diwali (early Nov), Christmas and New Year fall inside the plan. Buffer days exist for this; if they are not enough, slip the dates.
- Tightest weeks: Week 11 (four network apps) and Week 13 (perfboard + tests + docs). If needed, move the Wi-Fi scanner and the perfboard build to the Bonus list.
- (add a dated line here whenever the plan shifts)
