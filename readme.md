# Toy Light
A minimal low-power programmable LED light originally designed to be embedded within plastic toys.
## Hardware
A TPS61040 boost converter is used to provide a constant current for 2-8 white LEDs in series. An ATtiny10 is used to provide PWM control to the boost converter. A momentary switch us used for power and mode control. The schematic includes pull-up resistors for the button and reset line, however internal pull-ups appear to be sufficient. If low forward-voltage diodes are used the light can be operated below 1V per cell.
## Firmware
### Overview
The firmware has 4 modes - off, low brightness, full brightness and flashing. Other modes can be added by modifying the main switch statement.
### Building
The `build.sh` script can be used to build and flash the firmware. The script requires `avr-gcc`, `avr-objcopy` and `avrdude` to be installed. By default it expects a USBASP programmer.