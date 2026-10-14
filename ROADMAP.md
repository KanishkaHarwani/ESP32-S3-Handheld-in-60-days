# Roadmap

Lesson-by-lesson plan for the 60-day build. Check items off as you complete them; this file is the progress tracker. Planned start **2026-10-19**, planned finish **2026-12-17**. If you slip, edit the dates and add a one-line note under Progress.

---

## Phase 1: Foundations (Weeks 1-2, 19 Oct - 1 Nov)

Board: Xiao ESP32S3 · breadboard, LEDs, buttons, buzzer, temp/humidity sensor, multimeter

**Week 1 (19-25 Oct)**
- [ ] What is embedded systems programming: constraints, real-time, memory
- [ ] Embedded C++: variables, types, structs/classes, pointers and references
- [ ] ESP32-S3 architecture: dual-core, memory map, peripherals overview
- [ ] Toolchain: PlatformIO setup, project structure, build/upload/monitor
- [ ] Git and GitHub: repo structure, commits, branches, `.gitignore` for firmware
- Demo: blink + serial "hello" committed

**Week 2 (26 Oct - 1 Nov)**
- [ ] GPIO: digital in/out, pushbutton + debounce, PWM/LED fade
- [ ] UART: serial communication, serial monitor as a debug tool
- [ ] SPI: concept + wiring (prep for the TFT)
- [ ] I2C: concept + wiring, device scanning, reading the temp/humidity sensor
- [ ] Debugging basics: serial prints, wiring/power mistakes, multimeter
- [ ] **Checkpoint project:** sensor + buttons -> LED/buzzer/serial feedback loop
- Demo: short video of the checkpoint

---

## Phase 2: Connectivity & Architecture (Weeks 3-5, 2 - 22 Nov)

Board: Xiao ESP32S3, then ESP32-S3 DevKitC-1 · TFT, SD card, buck converter

> Order the DevKitC-1 by the start of Week 3 so it arrives before Phase 3.

**Week 3 (2-8 Nov)**
- [ ] Displays and graphics: driving the TFT over SPI, primitives, fonts, sprites
- [ ] Draw a button-test screen (the first handheld UI slice)
- [ ] Wi-Fi networking: station mode, connecting, reconnect handling

**Week 4 (9-15 Nov)**
- [ ] HTTP/HTTPS: requests, TLS basics on embedded, certificates
- [ ] REST APIs: calling a public API
- [ ] JSON: parsing/serializing (ArduinoJson), mapping API data to structs
- [ ] FreeRTOS: tasks, `vTaskDelay`, queues, why an RTOS over one big loop

**Week 5 (16-22 Nov)**
- [ ] Software architecture: layering drivers vs logic vs UI
- [ ] State machines: connecting -> fetching -> displaying -> error
- [ ] Driver development: write a thin driver for a sensor or the button module
- [ ] Debugging (intermediate): log levels, backtraces, watchdog timers
- [ ] **Checkpoint project:** API data over Wi-Fi -> JSON -> TFT, driven by a state machine
- Demo: photo/video of live data on screen

---

## Phase 3: The Handheld (Weeks 6-9, 23 Nov - 17 Dec)

Board: ESP32-S3 DevKitC-1 (N16R8) · TFT, 6 buttons, LiPo, charger, SD card

**Week 6 (23-29 Nov): Hardware bring-up**
- [ ] Wire the final pin map (see `hardware/README.md`), button test on all 6 inputs
- [ ] Battery voltage divider -> ADC, percentage curve for a LiPo
- [ ] Safe charging + power path on the breadboard (protected cell, proper charger module)
- [ ] Backlight PWM and double-buffered drawing (use PSRAM)

**Week 7 (30 Nov - 6 Dec): Launcher and apps**
- [ ] App framework: launcher -> app -> back, input events (press/hold/release)
- [ ] App 1: Snake
- [ ] App 2: Wi-Fi scanner
- [ ] App 3: **Smart Dashboard** (sensor + API data, reuse Phase 2 code)
- [ ] App 4: stopwatch + system/battery info

**Week 8 (7-13 Dec): Production practices**
- [ ] OTA updates: versioning, rollback safety
- [ ] Power management: idle dimming, deep sleep, wake on button
- [ ] Error handling, config storage (NVS), logging, watchdogs, power-loss recovery
- [ ] Optional: SD card logging/save files

**Week 9 (14-17 Dec): Polish and ship**
- [ ] Stress tests: Wi-Fi drop, API failure, sensor disconnect, low battery
- [ ] Final README/build log with photos and wiring diagram
- [ ] Optional stretch: KiCad PCB, 3D-printed case, IMU tilt controls, buzzer/audio
- Demo: final video of the handheld running

---

## Progress

| Phase | Planned dates | Status |
| ----- | ------------- | ------ |
| Phase 1: Foundations | 19 Oct - 1 Nov | Not started |
| Phase 2: Connectivity & Architecture | 2 - 22 Nov | Not started |
| Phase 3: The Handheld | 23 Nov - 17 Dec | Not started |

Schedule notes:
- (add a dated line here whenever the plan shifts)
