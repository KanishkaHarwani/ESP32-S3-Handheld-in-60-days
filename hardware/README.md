# Hardware

Everything used across the three phases, what it's for, and what's still needed.

## Boards

| Board | Used in | Notes |
| ----- | ------- | ----- |
| Seeed Xiao ESP32S3 (x3, owned) | Phase 1, early Phase 2 | Great for learning, but only ~11 usable GPIOs: not enough for TFT + 6 buttons + SD |
| **ESP32-S3 DevKitC-1, N16R8 (to buy)** | Late Phase 2, Phase 3 | 16 MB flash + 8 MB PSRAM, plenty of free pins; order before Week 3 |

Other boards you own (ESP32 DevKit 32E, WROOM, ESP8266, Teensy 3.5/4.1, Nano 33 BLE Sense, Raspberry Pis) are not part of the core path.

## Owned and used

| Item | Used in | Notes |
| ---- | ------- | ----- |
| Jumper wires, breadboards (large + small) | All phases | |
| Resistor set | Phase 1+ | pull-ups, LED, battery divider |
| LEDs (R, G, B, White), buzzer, pushbuttons | Phase 1, 3 | buttons become the 6 handheld inputs |
| Digital multimeter | Phase 1+ | essential for power/charging checks |
| Temp & humidity sensor (I2C) | Phase 1-3 | dashboard app input |
| 2.8" TFT, 240x320 (SPI) | Phase 2-3 | handheld display |
| SD card module + 32 GB cards (x2) | Phase 2-3 | logging, save files |
| BNO085 IMU | Phase 2-3 (optional) | tilt controls / motion data |
| Addressable LED strip, 1 m | optional | status light |

## To get

**Phase 1:** nothing required. Optional: 2x 10k potentiometers, a data-capable USB cable.

**Phase 2 (order by 2 Nov):**
- ESP32-S3 DevKitC-1 N16R8
- 3.3 V buck converter module, 12 V -> 5 V converter (power lessons)
- Small prototyping perfboards

**Phase 3 (handheld):**
- 3.7 V LiPo, 1000-2000 mAh, **with protection circuit**
- Charger module with USB-C and load sharing (power path) so the device can run while charging; avoid a bare TP4056 powering the board directly
- Slide power switch
- 2x 100k resistors (battery divider), 10k pull-ups (optional), 100 nF caps (optional button debounce)
- 6 tactile buttons (D-pad Up/Down/Left/Right + A + B)

**Nice to have:** DS3231 RTC, BME280, rotary encoder, single WS2812 LED, small I2S amp + speaker.

## Proposed pin map (ESP32-S3 DevKitC-1 N16R8)

Verify against your exact board's pinout before wiring.

| Function | GPIO |
| -------- | ---- |
| TFT SCK / MOSI | 12 / 11 |
| TFT CS / DC / RST | 10 / 9 / 8 |
| TFT backlight (PWM) | 7 |
| SD MISO / CS (shares SPI bus) | 13 / 21 |
| Buttons Up / Down / Left / Right | 4 / 5 / 6 / 15 |
| Buttons A / B | 16 / 17 |
| I2C SDA / SCL | 41 / 42 |
| Battery ADC (via 100k/100k divider) | 1 |
| Buzzer | 40 |

Pins to avoid on this board: 0, 3, 45, 46 (strapping), 19 / 20 (USB), 26-32 (flash), 33-37 (octal PSRAM), 48 (onboard RGB LED).

## Power notes

- Buttons wire between GPIO and GND using internal pull-ups.
- A 100k/100k divider turns 4.2 V (full cell) into 2.1 V, safe for the ADC.
- Never charge a LiPo without a proper charger IC; use a protected cell and check polarity twice.
- Measure with the multimeter before connecting the battery to the board for the first time.

## Deliberately skipped

Motors, servos, steppers, ultrasonic, PIR and gas sensors. Good candidates for a future robotics repo.
