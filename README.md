# Adafruit_TinyUSB_MIDI Library

The `Adafruit_TinyUSB_MIDI` library is an Arduino-compatible library that simplifies sending MIDI messages over USB using the Adafruit TinyUSB stack. This library allows you to easily send various MIDI messages such as Note On/Off, Control Change, Program Change, Pitch Bend, and more.

by Gustavo Silveira | Nerd Musician

## Project Overview

This repository contains the core library files `Adafruit_TinyUSB_MIDI.h` and `Adafruit_TinyUSB_MIDI.cpp`, input support through the `Adafruit_TinyUSB_MIDI_Input` class, and example sketches in the `Examples/` directory.

### USB-MIDI packets

USB-MIDI messages are transmitted in 32-bit packets that bundle message status and data bytes for efficient USB transfers.

### Callback model

Incoming MIDI events are handled via callbacks, letting your sketch react to messages as they arrive.

### Global vs. local MIDI instances

You can use the provided global `MIDI` object for simple sketches or create local instances to manage multiple MIDI interfaces.

### Supplying a custom transport

The library can bind to any `TinyUSBMIDI_Device` transport.  Pass your
transport instance to the constructor to avoid scattering `#ifdef`
checks in your sketch:

```cpp
#include <Adafruit_TinyUSB_MIDI.h>
#include <Adafruit_TinyUSB.h>

Adafruit_USBD_MIDI usb_midi;      // or USBMIDI on UNO R4 boards
Adafruit_TinyUSB_MIDI midi(usb_midi);

void setup() {
  midi.begin();
}
```

If you don't need a custom transport, use the built-in factory which
selects an available transport at runtime:

```cpp
Adafruit_TinyUSB_MIDI MIDI = Adafruit_TinyUSB_MIDI::makeDefault();
```

### Next Steps

- Explore the MIDI protocol to understand message structure.
- Learn more about the TinyUSB stack that enables USB connectivity.
- Experiment with the example sketches in the `Examples/` folder.

## Watch the full tutorial

[Make a MIDI Controller with the Raspberry Pi Pico: a MIDI Fidget Spinner](https://youtu.be/V3-PUsuYGzs)

## Features

- **Send MIDI Note On/Off**: Play and stop notes on a connected MIDI device.
- **Control Change**: Send control change messages to modify parameters like volume, pan, etc.
- **Program Change**: Change instruments or presets on a connected MIDI device.
- **Pitch Bend**: Bend the pitch of notes smoothly up or down.
- **Aftertouch**: Send aftertouch (channel pressure) messages for expressive playing.
- **Polyphonic Aftertouch**: Send individual pressure values for each note.
- **System Exclusive (SysEx)**: Send custom data to MIDI devices.

## Installation

1. **Download the Library**: [Download ZIP](#)
2. **Extract the ZIP file**: Unzip the downloaded file.
3. **Copy to Arduino Libraries Folder**:
    - Move the `Adafruit_TinyUSB_MIDI` folder to your Arduino libraries directory:
      - Windows: `Documents/Arduino/libraries/`
      - macOS/Linux: `~/Documents/Arduino/libraries/`
4. **Restart the Arduino IDE**: Restart your Arduino IDE to recognize the new library.

## Using with UNO R4 / Minima / Nano R4

The Renesas-based UNO R4 family ships with its own USBMIDI implementation.  Install the
**Arduino UNO R4 Boards** package version **1.0.7 or later** from the Board Manager, then
select the appropriate board under `Tools → Board`:

* **UNO R4 Minima** – `Arduino UNO R4 Minima`
* **UNO R4 WiFi** – `Arduino UNO R4 WiFi`
* **Nano R4** – `Arduino Nano R4`

These boards use the built-in `USBMIDI` class instead of the `Adafruit_USBD_MIDI` object
shown in the other examples.  Instantiate `USBMIDI` in your sketch and call `MIDI.begin()`
normally.

After uploading the sketch the board will reboot and enumerate as a class‑compliant
USB‑MIDI controller.  Check your operating system’s MIDI device list (e.g. **Audio MIDI
Setup** on macOS or **Device Manager → Sound, video and game controllers** on Windows) to
verify it appears.  If the device is not listed, press the reset button once to trigger
USB re‑enumeration.


## Learn how to build your MIDI controllers

- [Nerd Musician Pro (all the courses)](https://go.musiconerd.com/nerd-musician-pro)
- [DIY MIDI Controller Workshop (free course)](https://go.musiconerd.com/diy-midi-controller-workshop)
- [Fazendo Música com Arduino (Português)](https://go.musiconerd.com/fazendo-musica-com-arduino)