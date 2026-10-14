# Hardware

Everything used across the three phases, what it is for, and what is still needed. Pin maps below are proposals: verify them against your exact board's pinout (Seeed's Xiao ESP32S3 pinout and the DevKitC-1 pinout) before wiring.

## Boards

| Board | Used in | Notes |
| ----- | ------- | ----- |
| Seeed Xiao ESP32S3 (x3, owned) | Phase 1, Phase 2 | Great for learning, but only 11 usable GPIOs (D0-D10). Fits the TFT + DHT11 + 2 buttons, but not TFT + 6 buttons + SD |
| **ESP32-S3 DevKitC-1, N16R8 (to buy)** | Phase 3 | 16 MB flash + 8 MB PSRAM, plenty of free pins. Order by Mon 16 Nov, needed by Mon 14 Dec |

Other boards you own (ESP32 DevKit 32E, WROOM, ESP8266, Teensy 3.5/4.1, Nano 33 BLE Sense, Raspberry Pis) are not part of the core path.

## Owned and used

| Item | Used in | Notes |
| ---- | ------- | ----- |
| Jumper wires, breadboards (large + small) | All phases | |
| Resistor set | Phase 1+ | LED resistors, pull-ups, battery divider |
| LEDs (R, G, B, White), buzzer, pushbuttons | Phase 1-3 | buttons become the 6 handheld inputs |
| **DHT11 temperature/humidity sensor (generic)** | Phase 1-3 | single-wire, not I2C. About +/-2 C and +/-5 %RH, at most one read per second, reads can fail |
| 2.8" TFT, 240x320 (SPI) | Phase 2-3 | handheld display |
| Digital multimeter | Phase 1+ | essential for power and charging checks |
| SD card module + 32 GB cards (x2) | Phase 2-3 (optional) | logging, save files |
| BNO085 IMU | Phase 1 (I2C topic), Bonus | an I2C device you already own; its library is heavier than a simple sensor |
| Addressable LED strip, 1 m | optional | status light |

## To get

**Phase 1 (before Mon 26 Oct, optional but recommended):**
- A cheap I2C sensor such as BME280 or AHT20 for the I2C topic (simpler than the BNO085)
- 1-2x 10k potentiometers (ADC practice)
- A data-capable USB cable

**Phase 2:**
- ESP32-S3 DevKitC-1 N16R8 (order by 16 Nov)

**Phase 3 (order by 30 Nov):**
- 3.7 V LiPo, 1000-2000 mAh, **with protection circuit**
- USB-C charger module with load sharing (power path) so the device can run while charging; avoid a bare TP4056 powering the board directly
- Slide power switch
- 2x 100k resistors (battery divider), 100 nF caps (optional button debounce)
- 6 tactile buttons for the D-pad + A + B
- For the perfboard v2: perfboard, female headers for the DevKitC-1 and TFT, hookup wire, soldering iron + solder (if you do not already have them)

**Nice to have:** DS3231 RTC, rotary encoder, I2S amp + speaker.

**Not needed:** E-ink display (dropped from the plan).

## Phase 1 wiring (Xiao ESP32S3)

| Part | Pin |
| ---- | --- |
| Potentiometer (ADC practice) | D8 |
| Green LED (+ resistor) | D0 |
| Red LED (+ resistor) | D1 |
| Buzzer | D2 |
| DHT11 data | D3 |
| I2C SDA / SCL | D4 / D5 |
| Button A / B (to GND, internal pull-ups) | D6 / D7 |

D6 and D7 are the UART pins, which is fine because the serial monitor uses USB. Power the DHT11 from 3.3 V.

## Phase 2 wiring (Xiao ESP32S3)

| Part | Pin |
| ---- | --- |
| TFT SCK / MOSI | D8 / D10 |
| TFT CS / DC / RST | D0 / D1 / D2 |
| TFT backlight | D3 |
| DHT11 data | D4 |
| Button A / B | D6 / D7 |
| Buzzer | D5 |

Move the potentiometer off D8 when the TFT goes on. The full 6-button layout needs the DevKitC-1.

## Phase 3 proposed pin map (ESP32-S3 DevKitC-1 N16R8)

| Function | GPIO |
| -------- | ---- |
| TFT SCK / MOSI | 12 / 11 |
| TFT CS / DC / RST | 10 / 9 / 8 |
| TFT backlight (PWM) | 7 |
| SD MISO / CS (shares the SPI bus) | 13 / 21 |
| Buttons Up / Down / Left / Right | 4 / 5 / 6 / 15 |
| Buttons A / B | 16 / 17 |
| DHT11 data | 14 |
| I2C SDA / SCL (future IMU / sensors) | 41 / 42 |
| Battery ADC (via 100k/100k divider) | 1 |
| Buzzer | 40 |

Pins to avoid: 0, 3, 45, 46 (strapping), 19 / 20 (USB), 26-32 (flash), 33-37 (octal PSRAM), 48 (onboard RGB LED).

## Power notes

- Buttons wire between GPIO and GND using internal pull-ups.
- A 100k/100k divider turns 4.2 V (full cell) into 2.1 V, safe for the ADC.
- Never charge a LiPo without a proper charger IC; use a protected cell and check polarity twice.
- Measure with the multimeter before connecting the battery to the board for the first time.
- DHT11 bit-timing can be disturbed by other work on the same core, so read it at 2-second intervals from its own task and treat a failed read as normal.

## Deliberately skipped

Motors, servos, steppers, ultrasonic, PIR and gas sensors, and E-ink. Good candidates for a future robotics repo.
