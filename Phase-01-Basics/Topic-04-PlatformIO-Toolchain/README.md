# Topic 04: PlatformIO Toolchain

**Week 1** · Do this right after Topic 01. By the end you will have real code running on your Xiao ESP32S3.

## Why PlatformIO instead of Arduino IDE

Arduino IDE is fine for tiny sketches but gets awkward fast: manual library management, no real project structure, weak editor support. **PlatformIO** is a proper build system. One config file handles toolchain, libraries and board, and it runs inside VS Code with real autocomplete.

## Install

1. Install [VS Code](https://code.visualstudio.com/).
2. Install the **PlatformIO IDE** extension (Extensions panel, search "PlatformIO IDE").
3. Restart VS Code. PlatformIO downloads its toolchain on first run, which takes a few minutes.

## Anatomy of a PlatformIO project

```
my-project/
├── platformio.ini      # board, framework, libraries: the heart of the project
├── src/
│   └── main.cpp        # your code
├── include/            # optional headers
└── lib/                # optional private libraries
```

A minimal `platformio.ini` for the Xiao ESP32S3:

```ini
[env:seeed_xiao_esp32s3]
platform = espressif32
board = seeed_xiao_esp32s3
framework = arduino
monitor_speed = 115200
build_flags =
    -DARDUINO_USB_CDC_ON_BOOT=1
```

- **`platform`**: which chip family's toolchain to install
- **`board`**: the exact board definition (pins, flash size)
- **`framework`**: `arduino` gives you `setup()` / `loop()` and a huge library ecosystem, with real C++ underneath
- **`monitor_speed`**: baud rate for the serial monitor (Topic 07)
- **`build_flags`**: routes `Serial` to the native USB port. Without it you may see no output in the monitor. If it is not needed on your setup, remove it.

## The core workflow

```bash
pio run                    # build (compile)
pio run --target upload    # build + flash to the board
pio device monitor         # open the serial monitor
```

Build, upload, monitor: you will use this loop for the rest of the repo. The same three actions are buttons in the VS Code status bar.

## Libraries

Add libraries to `platformio.ini` instead of installing them by hand:

```ini
lib_deps =
    adafruit/Adafruit AHTX0
```

## If the board is not detected

- Use a **data** USB cable (many cables are charge-only).
- Hold the **BOOT** button while plugging in USB to enter bootloader mode, then upload again.
- Close any open serial monitor before uploading.

## Check yourself

- What does `board =` control that `framework =` does not?
- What are the three commands of the core loop?
- Why is the build flag needed on the Xiao?

## What's next

Do the `Example/`: blink an LED and print "hello" over serial. Then commit it, and move to Topic 02 (C++) and Topic 05 (Git).
