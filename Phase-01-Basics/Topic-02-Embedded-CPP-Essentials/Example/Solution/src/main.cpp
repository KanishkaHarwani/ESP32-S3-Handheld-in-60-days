// Topic 02 Solution: embedded C++ essentials
// (types, functions, structs/classes, pointers and references)

#include <Arduino.h>

// ---------- 1. Types ----------
static void demoTypes() {
  Serial.println("\n[1] Types");
  uint8_t small = 250;
  small += 10;  // wraps around: 260 % 256 = 4
  Serial.printf("uint8_t 250 + 10 = %u\n", (unsigned)small);
  Serial.printf("sizeof: int=%u uint8_t=%u float=%u double=%u void*=%u\n",
                (unsigned)sizeof(int), (unsigned)sizeof(uint8_t), (unsigned)sizeof(float),
                (unsigned)sizeof(double), (unsigned)sizeof(void *));
}

// ---------- 2. Functions and overloading ----------
static int add(int a, int b) { return a + b; }
static float add(float a, float b) { return a + b; }

// ---------- 3. Struct and class ----------
struct Reading {
  float temperatureC;
  float humidity;
  bool valid;
};

static float toFahrenheit(const Reading &r) { return r.temperatureC * 9.0f / 5.0f + 32.0f; }

class Counter {
 public:
  explicit Counter(uint32_t step = 1) : step_(step) {}
  void tick() { value_ += step_; }
  uint32_t value() const { return value_; }

 private:
  uint32_t step_;
  uint32_t value_ = 0;
};

// ---------- 4. Pointers and references ----------
static void swapByPointer(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static void swapByReference(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

static void demoPointers() {
  Serial.println("\n[4] Pointers and references");
  int x = 1, y = 2;
  swapByPointer(&x, &y);
  Serial.printf("after swapByPointer:   x=%d y=%d\n", x, y);
  swapByReference(x, y);
  Serial.printf("after swapByReference: x=%d y=%d\n", x, y);

  int data[5] = {10, 20, 30, 40, 50};
  const int *p = data;
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += *(p + i);
  }
  Serial.printf("sum via pointer = %d\n", sum);
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  demoTypes();

  Serial.println("\n[2] Overloading");
  Serial.printf("add(2, 3) = %d\n", add(2, 3));
  Serial.printf("add(2.5f, 3.5f) = %.2f\n", add(2.5f, 3.5f));

  Serial.println("\n[3] Struct and class");
  Reading r = {21.5f, 48.0f, true};
  Serial.printf("%.1f C = %.2f F\n", r.temperatureC, toFahrenheit(r));
  Counter c(5);
  c.tick();
  c.tick();
  c.tick();
  Serial.printf("counter after 3 ticks (step 5) = %lu\n", (unsigned long)c.value());

  demoPointers();
}

void loop() {}
