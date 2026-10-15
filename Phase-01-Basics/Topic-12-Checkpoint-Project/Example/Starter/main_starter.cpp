// Topic 11 — Checkpoint Project: Temperature Alert System
// Starter. Copy this file into your PlatformIO project's src/ folder as main.cpp.
//
// Ties together: I2C sensor reading, GPIO output, debounced button input,
// non-blocking timing, and serial commands - everything from Phase 1.

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

// ---- Pins ----
const uint8_t LED_PIN = D1;
const uint8_t BUZZER_PIN = D3;
const uint8_t BUTTON_PIN = D2;

// ---- Timing ----
const uint32_t READ_INTERVAL_MS = 2000;
const uint32_t DEBOUNCE_MS = 50;
const uint32_t MUTE_DURATION_MS = 10000;

// ---- State ----
Adafruit_AHTX0 aht;
float threshold = 28.0;
float lastTemp = 0.0;
float lastHumidity = 0.0;

uint32_t lastRead = 0;
uint32_t muteUntil = 0;   // millis() timestamp when mute expires (0 = not muted)

// Button debounce state (same pattern as Topic 06)
bool lastReading = HIGH;
bool stableState = HIGH;
uint32_t lastChangeTime = 0;

bool isMuted() {
  return millis() < muteUntil;
}

void handleButton() {
  // TODO: same debounce pattern as Topic 06.
  // On a real, settled press (stableState goes to LOW):
  //   set muteUntil = millis() + MUTE_DURATION_MS
  //   print a message confirming the mute started
}

void readSensorAndUpdateAlert() {
  // TODO, every READ_INTERVAL_MS (non-blocking):
  //   1. read temp/humidity into lastTemp / lastHumidity via aht.getEvent()
  //   2. print a status line, e.g.:
  //        "[status] temp=23.4C humidity=48.1% muted=false"
  //   3. if lastTemp > threshold AND not isMuted():
  //        turn on LED_PIN and BUZZER_PIN, print an "[ALERT] ..." line
  //      else:
  //        turn off LED_PIN and BUZZER_PIN
}

void handleSerialCommands() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "status") {
      Serial.printf("[status] temp=%.1fC humidity=%.1f%% threshold=%.1fC muted=%s\n",
                    lastTemp, lastHumidity, threshold, isMuted() ? "true" : "false");
    } else if (command.startsWith("threshold ")) {
      // TODO: parse the number after "threshold " (hint: command.substring(10).toFloat())
      // update `threshold`, and print a confirmation.
    } else if (command.length() > 0) {
      Serial.printf("Unknown command: %s\n", command.c_str());
    }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  Wire.begin();

  if (aht.begin()) {
    Serial.printf("Sensor ready. Threshold: %.1fC\n", threshold);
  } else {
    Serial.println("Could not find AHT sensor - check wiring.");
  }
}

void loop() {
  handleButton();
  readSensorAndUpdateAlert();
  handleSerialCommands();
}
