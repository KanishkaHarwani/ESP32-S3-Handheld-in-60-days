// Topic 08 Starter: SPI concepts + loopback test
//
// Wiring: jumper D10 (MOSI) to D9 (MISO). Whatever the board sends, it hears back.
// Disconnect the potentiometer from D8 (SCK) for this test.
//   SCK = D8, MISO = D9, MOSI = D10, chip select (CS) = D0 (a GPIO we toggle ourselves)
//
// Goal: send bytes, check they come back identical, and see which clock speeds
// and SPI modes work.

#include <Arduino.h>
#include <SPI.h>

constexpr uint8_t PIN_SCK = D8;
constexpr uint8_t PIN_MISO = D9;
constexpr uint8_t PIN_MOSI = D10;
constexpr uint8_t PIN_CS = D0;

// Sends `len` bytes and returns true if every byte comes back unchanged.
static bool runLoopback(uint32_t hz, uint8_t mode, size_t len) {
  // TODO 3: start a transaction with SPISettings(hz, MSBFIRST, mode)
  // TODO 4: pull CS LOW
  bool ok = true;
  for (size_t i = 0; i < len; i++) {
    uint8_t tx = (uint8_t)(0xA0 + i);
    uint8_t rx = 0;
    // TODO 5: rx = SPI.transfer(tx);  then if rx != tx set ok = false
    (void)tx;
    (void)rx;
  }
  // TODO 6: pull CS HIGH and end the transaction
  return ok;
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  // TODO 1: set PIN_CS as OUTPUT and HIGH (idle = not selected)
  // TODO 2: start the bus: SPI.begin(PIN_SCK, PIN_MISO, PIN_MOSI, -1)
  //         (-1 because we control CS by hand)

  Serial.println("SPI loopback test (D10 -> D9)");
}

void loop() {
  const uint32_t speeds[] = {1000000, 4000000, 10000000, 20000000};
  const uint8_t modes[] = {SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3};

  // TODO 7: for every speed and every mode, call runLoopback(speed, mode, 8) and print
  //         "<speed> Hz, mode <n>: PASS/FAIL". In loopback every combination should pass.
  (void)speeds;
  (void)modes;

  // TODO 8 (experiment): unplug the jumper and run again. What does a floating MISO read?

  delay(5000);
}
