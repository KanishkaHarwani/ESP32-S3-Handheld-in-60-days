# Phase 2: Connectivity and Architecture

**Weeks 4-8 (9 Nov - 13 Dec 2026)**
**Board:** Seeed Xiao ESP32S3
**Parts:** 2.8" SPI TFT, DHT11, 2 buttons, buzzer

> **Reminder:** order the ESP32-S3 DevKitC-1 (N16R8) by **Mon 16 Nov**. It is needed by Mon 14 Dec for Phase 3.

## Goal

Put live data on the screen and structure the code so it survives failure. You learn displays, Wi-Fi, HTTP/TLS, REST, JSON, FreeRTOS, state machines and reusable drivers. You finish with weather and nearby flights on the TFT that keep working through Wi-Fi drops and API errors.

## Topics

| # | Topic | Week |
| - | ----- | ---- |
| 01 | [TFT Displays and Graphics](Topic-01-TFT-Displays-Graphics/) | 4 |
| 02 | [Wi-Fi](Topic-02-WiFi/) | 5 |
| 03 | [HTTP and HTTPS](Topic-03-HTTP-HTTPS/) | 5 |
| 04 | [REST APIs](Topic-04-REST-APIs/) | 5 |
| 05 | [JSON](Topic-05-JSON/) | 6 |
| 06 | [Flight and Live-Data APIs](Topic-06-Flight-Live-Data-APIs/) | 6 |
| 07 | [FreeRTOS](Topic-07-FreeRTOS/) | 6-7 (tasks in 6, queues in 7) |
| 08 | [Software Architecture](Topic-08-Software-Architecture/) | 7 |
| 09 | [State Machines](Topic-09-State-Machines/) | 7 |
| 10 | [Driver Development](Topic-10-Driver-Development/) | 8 |
| 11 | [Debugging, Intermediate](Topic-11-Debugging-Intermediate/) | 8 |
| 12 | [Checkpoint Project](Topic-12-Checkpoint-Project/) | 8 |

## Demos

- Week 4: button-test screen on the TFT (first handheld UI slice)
- Week 5: raw weather data on the TFT
- Week 6: parsed weather + nearby flight count on the TFT
- Week 7: tasks + state machine skeleton running
- Week 8: video of live data, then pull the Wi-Fi

## Checkpoint (finishes the phase)

**Topic 12:** weather and nearby flights on the TFT, driven by a state machine (`CONNECTING -> FETCHING -> DISPLAYING -> ERROR`) and FreeRTOS tasks. It must recover from Wi-Fi loss and API failures without a reset.

## APIs and limits

| Data | Source | Limits |
| ---- | ------ | ------ |
| Weather | Open-Meteo | 600/min, 5,000/hour, 10,000/day; non-commercial, attribution required |
| Flights | OpenSky `/states/all` with a bounding box | Anonymous 400 credits/day, registered (OAuth2) 4,000/day |

Plan a polling budget and cache results; do not poll in a tight loop.

## Secrets

Wi-Fi credentials, API client IDs/secrets and your coordinates go in `include/secrets.h`, which is git-ignored. Commit only `secrets.example.h` with placeholders. This repo is public.

## Wiring

See `../hardware/README.md` ("Phase 2 wiring"). The potentiometer moves off D8 once the TFT is attached. The Xiao only has enough pins for 2 buttons; the full 6-button layout comes in Phase 3.

## How to work

1. Read the topic README.
2. Try `Example/Starter/` before `Example/Solution/`.
3. Commit after each topic and update `ROADMAP.md`.
4. Build and demo the checkpoint before moving on.
