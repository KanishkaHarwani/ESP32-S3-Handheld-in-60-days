// Topic 07 Solution: UART and the serial monitor as a debug tool
//
// A tiny command console over the USB serial monitor, plus a hardware UART
// loopback test.
//
// Wiring: Green LED + resistor -> D0.
// For the "loop" command only: jumper D6 (UART TX) to D7 (UART RX).
//
// Commands:  help | led on | led off | status | echo <text> | loop
// Tip: set the monitor's line ending to "Newline" so each command ends with '\n'.

#include <Arduino.h>

constexpr uint8_t PIN_LED = D0;
constexpr uint8_t PIN_UART_TX = D6;
constexpr uint8_t PIN_UART_RX = D7;

static String lineBuf;
static bool ledOn = false;

static void printHelp() {
  Serial.println("Commands: help | led on | led off | status | echo <text> | loop");
}

static void uartLoopbackTest() {
  Serial1.begin(9600, SERIAL_8N1, PIN_UART_RX, PIN_UART_TX);
  while (Serial1.available()) Serial1.read();  // flush old bytes

  const char *msg = "PING";
  Serial1.print(msg);
  Serial1.flush();  // wait until the bytes have left the transmitter

  String got;
  uint32_t start = millis();
  while (millis() - start < 100 && got.length() < strlen(msg)) {
    while (Serial1.available()) got += (char)Serial1.read();
  }

  Serial.printf("loop: sent '%s', received '%s' -> %s\n", msg, got.c_str(),
                got == msg ? "PASS" : "FAIL (is D6 jumpered to D7?)");
  Serial1.end();
}

static void handleCommand(const String &cmd) {
  if (cmd.length() == 0) return;

  if (cmd == "help") {
    printHelp();
  } else if (cmd == "led on") {
    ledOn = true;
    digitalWrite(PIN_LED, HIGH);
    Serial.println("LED is on");
  } else if (cmd == "led off") {
    ledOn = false;
    digitalWrite(PIN_LED, LOW);
    Serial.println("LED is off");
  } else if (cmd == "status") {
    Serial.printf("uptime: %lu s, free heap: %lu bytes, LED: %s\n",
                  (unsigned long)(millis() / 1000), (unsigned long)ESP.getFreeHeap(),
                  ledOn ? "on" : "off");
  } else if (cmd.startsWith("echo ")) {
    Serial.println(cmd.substring(5));
  } else if (cmd == "loop") {
    uartLoopbackTest();
  } else {
    Serial.printf("Unknown command: '%s' (type help)\n", cmd.c_str());
  }
}

// Non-blocking line reader: collects characters until '\n'.
static void pollSerial() {
  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      handleCommand(lineBuf);
      lineBuf = "";
    } else if (lineBuf.length() < 64) {
      lineBuf += c;
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  Serial.println("\nTopic 07: serial command console");
  printHelp();
}

void loop() {
  pollSerial();
}
