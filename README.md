# K42-Peripheral-Libraries

A set of libraries for using the hardware peripherals in PIC18FxxK42 microcontrollers.

For additional reference information, please refer to the [processor datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/PIC18LF26-27-45-46-47-55-56-57K42-Data-Sheet-40001919E.pdf).

# Getting Started

This project is designed to be included in your project as a git "submodule", which will cause a copy of this repo to be downloaded into your project so it can be compiled like normal, but it doesn't add those files to your project's source control. This makes it easier to keep a common set of code in sync between multiple projects without error-prone copy/pasting.

In your own repository, run:

```
git submodule add https://github.com/DaelonSuzuka/K42-Peripheral-Libraries src/peripherals
```

This should add the submodule info to your git repository, and download the code to `src/peripherals`.

Once the repo is downloaded, you should be able to use it in your own code by simply `#include`ing the desired header.

Note: when you `git clone` your own repo that contains submodules, you will also need to run `git submodule update --init --recursive` in order to also download any submodules that are in your repo.

# Peripheral Libraries

To prevent myself from writing stupid code with bad abstractions, I've only written drivers for peripherals that I've actually used in production code.

These peripherals currently have drivers (a-z order):
 - Analog-to-Digital Converter(ch. 36)
 - Configurable Logic Cells(ch. 27)
 - Device Information Area(ch. 5)
 - Fixed Voltage Reference/Temperature Indicator Module(ch. 34, ch. 35)
 - High/Low Voltage Detect(ch. 39)
 - Interrupt(ch. 9)
 - Nonvolatile Memory(ch. 13)
 - Numerically Controlled Oscillator(ch. 28)
 - Oscillator(ch. 7)
 - Ports(ch. 16)
 - Peripheral Pin Select(ch. 17)
 - Reset Handler(ch. 6)
 - Signal Measurement Timer(ch. 25)
 - Timers(ch. 20, ch. 21, ch. 22)
 - UARTs(ch. 31)

There peripherals do not yet have drivers (datasheet chapter order):
 - Reference Clock Output Module(ch. 8)
 - Windowed Watchdog Timer(ch. 11)
 - Cyclic Redundancy Check Module(ch. 14)
 - Direct Memory Access(ch. 15)
 - Peripheral Module Disable(ch. 19)
 - Capture/Compare/PWM Module(ch. 23)
 - Pulse-Width Modulation(ch. 24)
 - Complementary Waveform Generator(ch. 26)
 - Zero-Cross Detection Module(ch. 29)
 - Data Signal Modulator(ch. 30)
 - SPI(ch. 32)
 - I2C(ch. 33)
 - Digital-to-Analog Converter(ch. 37)
 - Comparator(ch. 38)

# Details on individual drivers

coming soon