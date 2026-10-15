// Topic 07 Starter: UART and the serial monitor as a debug tool
//
// Goal: a tiny command console over the USB serial monitor, plus a hardware
// UART loopback test.
//
// Wiring: Green LED + resistor -> D0.
// For the "loop" command only: jumper D6 (UART TX) to D7 (UART RX).
//
// Commands:  help | led on | led off | status | echo <text> | loop

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
  // TODO 5: start Serial1 at 9600 baud, 8N1, with RX = PIN_UART_RX and TX = PIN_UART_TX
  //         (hint: Serial1.begin(9600, SERIAL_8N1, rx, tx))
  // TODO 6: send "PING" with Serial1.print, wait up to 100 ms, read what comes back
  //         and print PASS if it equals "PING", otherwise FAIL (check the jumper wire).
  // TODO 7: call Serial1.end() when done.
  Serial.println("loop: not implemented yet");
}

static void handleCommand(const String &cmd) {
  if (cmd.length() == 0) return;

  if (cmd == "help") {
    printHelp();
  }
  // TODO 3: "led on" / "led off": drive PIN_LED, update ledOn, reply with the new state.
  // TODO 4: "status": print uptime in seconds (millis() / 1000), free heap and LED state.
  // TODO 4b: "echo <text>": print everything after "echo " (hint: cmd.substring(5)).
  else if (cmd == "loop") {
    uartLoopbackTest();
  } else {
    Serial.printf("Unknown command: '%s' (type help)\n", cmd.c_str());
  }
}

static void pollSerial() {
  // TODO 2: read characters while Serial.available() > 0.
  //   - ignore '\r'
  //   - on '\n' call handleCommand(lineBuf) and clear the buffer
  //   - otherwise append the char, but stop growing past 64 characters
  // This must never block: no delay() and no waiting for input.
}

void setup() {
  Serial.begin(115200);
  delay(1500);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // TODO 1: print a banner and call printHelp().
}

void loop() {
  pollSerial();
}
