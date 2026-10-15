# Topic 02: Embedded C++ Essentials

**Week 1** · Study this after Topic 04, so you can run the examples on the Xiao.

This is the C++ you will actually use in this repo: not the whole language, just the parts that matter once you model hardware in code.

## Variables and fixed-width types

In regular C++ you might casually use `int`. In embedded work, size matters. You often need to know *exactly* how many bits something takes, because memory is small and hardware registers are specific.

```cpp
uint8_t  brightness  = 200;   // 0-255, one byte: perfect for PWM/LED values
uint16_t sensorRaw   = 1023;  // 0-65535, two bytes
int32_t  temperature = -540;  // signed, four bytes
bool     isOn        = true;
```

`uint8_t` means "unsigned integer, 8 bits." You will see these constantly in datasheets and libraries.

## Functions

Small functions with clear inputs and outputs keep `loop()` readable:

```cpp
float celsiusToFahrenheit(float c) {
  return c * 9.0f / 5.0f + 32.0f;
}
```

Prefer `const` for values that never change and `constexpr` for compile-time constants (pin numbers, thresholds). They cost no RAM and prevent accidents:

```cpp
constexpr uint8_t LED_PIN = D0;
```

## Structs: grouping related data

A `struct` bundles related values into one thing instead of several loose variables:

```cpp
struct SensorReading {
  float    temperatureC;
  float    humidityPct;
  uint32_t timestampMs;
  bool     valid;
};
```

## Classes: data plus behaviour

A `class` is a struct that also owns *functions* acting on its own data. This is the shape you will use to model real components (an LED, a sensor, a display).

```cpp
class Led {
  public:
    explicit Led(uint8_t pin) : pin_(pin), isOn_(false) {}

    void turnOn()  { isOn_ = true; }
    void turnOff() { isOn_ = false; }
    bool isOn() const { return isOn_; }

  private:
    uint8_t pin_;
    bool isOn_;
};
```

`private` means the internal state can only be changed through the methods you provide. That is what a "clean interface" means in practice, and Phase 2's driver-development topic builds on it.

## Pointers and references: the short version

You do not need pointer arithmetic for this repo, but you must recognise two patterns:

```cpp
void turnOn(Led& led) {    // reference: modify the real Led, not a copy
  led.turnOn();
}

void turnOn(Led* led) {    // pointer: same idea, but can be "nothing" (nullptr)
  if (led != nullptr) {
    led->turnOn();
  }
}
```

- **Reference (`&`)**: a second name for an existing variable. Use it when the thing always exists and you want to avoid copying it.
- **Pointer (`*`)**: an address that *can* be empty (`nullptr`). Use it when something might not exist yet, or when a library asks for one.

Always check a pointer for `nullptr` before using it. A bad pointer on a microcontroller usually means a crash and reboot.

## Avoid in embedded code (for now)

- `String` in tight loops (it allocates heap memory and can fragment it); prefer `char` buffers or `snprintf`.
- `new` / `delete` at runtime. Allocate things once, up front.

## Check yourself

- What is the difference between `uint8_t` and `int`, and why does it matter here?
- When would you pick a pointer over a reference?
- Why is `private` useful when two parts of the code touch the same LED?

## What's next

Do the `Example/`: build a small class that models a hardware component. Then Topic 05 sets up Git, and Topic 03 tours the chip.
