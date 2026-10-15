// Topic 02 Starter: embedded C++ essentials
// (types, functions, structs/classes, pointers and references)
//
// Each section has a TODO. Fill them in, then compare the serial output with
// the expected values in the comments.

#include <Arduino.h>

// ---------- 1. Types ----------
static void demoTypes() {
  Serial.println("\n[1] Types");
  uint8_t small = 250;
  // TODO 1a: add 10 to `small` and print it. Expected: 4 (8-bit overflow wraps around).
  // TODO 1b: print sizeof(int), sizeof(uint8_t), sizeof(float), sizeof(double), sizeof(void*)
  (void)small;
}

// ---------- 2. Functions and overloading ----------
// TODO 2a: write `int add(int a, int b)`
// TODO 2b: write an overload `float add(float a, float b)`

// ---------- 3. Struct and class ----------
struct Reading {
  float temperatureC;
  float humidity;
  bool valid;
};

// TODO 3a: write `float toFahrenheit(const Reading &r)`  (F = C * 9 / 5 + 32)

class Counter {
 public:
  explicit Counter(uint32_t step = 1) : step_(step) {}
  // TODO 3b: add `void tick()` that increases value_ by step_
  // TODO 3c: add `uint32_t value() const` that returns value_
 private:
  uint32_t step_;
  uint32_t value_ = 0;
};

// ---------- 4. Pointers and references ----------
// TODO 4a: write `void swapByPointer(int *a, int *b)`
// TODO 4b: write `void swapByReference(int &a, int &b)`

static void demoPointers() {
  Serial.println("\n[4] Pointers and references");
  int x = 1, y = 2;
  // TODO 4c: call swapByPointer(&x, &y) and print x, y. Expected: 2 1
  // TODO 4d: call swapByReference(x, y) and print x, y. Expected: 1 2
  (void)x;
  (void)y;

  int data[5] = {10, 20, 30, 40, 50};
  // TODO 4e: sum the array using a pointer (const int *p = data; *(p + i)). Expected: 150
  (void)data;
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  demoTypes();

  Serial.println("\n[2] Overloading");
  // TODO 2c: print add(2, 3) and add(2.5f, 3.5f). Expected: 5 and 6.00

  Serial.println("\n[3] Struct and class");
  Reading r = {21.5f, 48.0f, true};
  (void)r;
  // TODO 3d: print toFahrenheit(r). Expected: 70.70
  Counter c(5);
  (void)c;
  // TODO 3e: call c.tick() three times and print c.value(). Expected: 15

  demoPointers();
}

void loop() {}
