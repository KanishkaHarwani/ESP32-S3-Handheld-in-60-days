# Topic 01: What Is Embedded Systems Programming

**Week 1** · No code, no board. Just the mental model you need before anything else makes sense.

## The core idea

When you write a normal app, an operating system sits between your code and the hardware. It manages memory, schedules your program alongside a hundred others, and cleans up after you if you mess up.

Embedded programming removes that safety net. Your code often *is* the whole system. It talks directly to real circuits: it reads a voltage, it flips a physical pin, and if it locks up, nothing reboots it for you. That is why it feels more like "controlling a machine" than "writing software."

## Three things that make embedded different

**1. Resources are tiny and fixed.**
Your ESP32-S3 does not get more RAM if it runs low. There is no swap file and no cloud burst. A few hundred KB of RAM is what you get, so embedded C++ leans on being deliberate about memory instead of trusting a garbage collector.

**2. Time is real.**
A sensor might need reading within microseconds of an event, or a display refresh might need to happen on a strict schedule. In app development, "a bit slow" is annoying. In embedded, it can mean a missed signal, a corrupted reading, or a damaged component. This is called **real-time** behaviour: not "fast", but "predictably on time."

**3. You are touching hardware directly.**
A line of code does not just change a variable. It can turn on an LED, sound a buzzer, or send data over a wire to another chip. That physical effect is the payoff of embedded work.

## Memory, at a glance

| Kind | Holds | Survives power-off? |
| ---- | ----- | ------------------- |
| Flash | your compiled program, saved settings | yes |
| RAM | variables, the stack, live data | no |

Topic 03 puts real numbers on these for the ESP32-S3.

## Why this repo uses C++

C++ gives you low-level control (you can talk to hardware directly) and structure (classes, templates, abstractions) so your code does not become an unreadable pile of raw pin manipulation as the project grows. That balance suits this repo: simple sketches early on, real architecture by Phase 3.

## Check yourself

- Why can't an embedded program "just allocate more memory"?
- What is the difference between "fast" and "real-time"?
- What happens when your program hangs and there is no OS?

## What's next

Topic 04 sets up the toolchain so you can run code on the Xiao ESP32S3. Then Topic 02 covers the C++ you will lean on most.
