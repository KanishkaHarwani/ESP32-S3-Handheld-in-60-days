// Topic 08 Solution: SPI concepts + loopback test
//
// Wiring: jumper D10 (MOSI) to D9 (MISO). Whatever the board sends, it hears back.
// Disconnect the potentiometer from D8 (SCK) for this test.
//   SCK = D8, MISO = D9, MOSI = D10, chip select (CS) = D0 (a GPIO we toggle ourselves)
//
// With the jumper in place every speed/mode passes. Remove the jumper and the
// test fails: that is how you prove a wiring problem before blaming your code.

#include <Arduino.h>
#include <SPI.h>

constexpr uint8_t PIN_SCK = D8;
constexpr uint8_t PIN_MISO = D9;
constexpr uint8_t PIN_MOSI = D10;
constexpr uint8_t PIN_CS = D0;

// Sends `len` bytes and returns true if every byte comes back unchanged.
static bool runLoopback(uint32_t hz, uint8_t mode, size_t len) {
  SPI.beginTransaction(SPISettings(hz, MSBFIRST, mode));
  digitalWrite(PIN_CS, LOW);

  bool ok = true;
  for (size_t i = 0; i < len; i++) {
    uint8_t tx = (uint8_t)(0xA0 + i);
    uint8_t rx = SPI.transfer(tx);  // SPI is full duplex: one byte out, one byte in
    if (rx != tx) ok = false;
  }

  digitalWrite(PIN_CS, HIGH);
  SPI.endTransaction();
  return ok;
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);  // idle = not selected
  SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, -1);

  Serial.println("SPI loopback test (D10 -> D9)");
}

void loop() {
  const uint32_t speeds[] = {1000000, 4000000, 10000000, 20000000};
  const uint8_t modes[] = {SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3};

  uint8_t failures = 0;
  for (uint32_t hz : speeds) {
    for (uint8_t m = 0; m < 4; m++) {
      bool ok = runLoopback(hz, modes[m], 8);
      if (!ok) failures++;
      Serial.printf("%8lu Hz, mode %u: %s\n", (unsigned long)hz, (unsigned)m, ok ? "PASS" : "FAIL");
    }
  }
  Serial.printf("Done: %u failure(s)%s\n\n", (unsigned)failures,
                failures ? " -> check the D10-D9 jumper" : "");

  delay(5000);
}
