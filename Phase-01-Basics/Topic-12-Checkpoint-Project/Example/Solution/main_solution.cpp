// Topic 11 — Checkpoint Project: Temperature Alert System
// Solution. Copy this file into your PlatformIO project's src/ folder as main.cpp.
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
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastReading) {
    lastChangeTime = millis();
  }

  if ((millis() - lastChangeTime) > DEBOUNCE_MS) {
    if (reading != stableState) {
      stableState = reading;

      if (stableState == LOW) {  // a real, settled press
        muteUntil = millis() + MUTE_DURATION_MS;
        Serial.println("Alert muted for 10 seconds.");
      }
    }
  }

  lastReading = reading;
}

void readSensorAndUpdateAlert() {
  if (millis() - lastRead < READ_INTERVAL_MS) {
    return;
  }
  lastRead = millis();

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  lastTemp = temp.temperature;
  lastHumidity = humidity.relative_humidity;

  Serial.printf("[status] temp=%.1fC humidity=%.1f%% muted=%s\n",
                lastTemp, lastHumidity, isMuted() ? "true" : "false");

  bool shouldAlert = (lastTemp > threshold) && !isMuted();

  if (shouldAlert) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.printf("[ALERT] temp=%.1fC exceeds threshold %.1fC\n", lastTemp, threshold);
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void handleSerialCommands() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "status") {
      Serial.printf("[status] temp=%.1fC humidity=%.1f%% threshold=%.1fC muted=%s\n",
                    lastTemp, lastHumidity, threshold, isMuted() ? "true" : "false");
    } else if (command.startsWith("threshold ")) {
      float newThreshold = command.substring(10).toFloat();
      threshold = newThreshold;
      Serial.printf("Threshold set to %.1fC\n", threshold);
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
