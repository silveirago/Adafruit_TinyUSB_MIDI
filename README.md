# Adafruit_TinyUSB_MIDI Library

The `Adafruit_TinyUSB_MIDI` library is an Arduino-compatible library that simplifies sending MIDI messages over USB using the Adafruit TinyUSB stack. This library allows you to easily send various MIDI messages such as Note On/Off, Control Change, Program Change, Pitch Bend, and more.

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

## Usage

### Basic Example

```cpp
#include <Adafruit_TinyUSB_MIDI.h>

void setup() {
  // Initialize MIDI communication
  MIDI.begin();
}

int delayTime = 200;

void loop() {
  // Send MIDI notes from C2 to B2
  for (int i = 36; i < 48; i++) {
    MIDI.sendNoteOn(i, 127, 1);  // note, velocity, channel
    delay(delayTime);
    MIDI.sendNoteOn(i, 0, 1);    // note, velocity, channel (Note Off)
    delay(delayTime);
  }

  // Send Control Change messages
  for (int i = 1; i < 128; i++) {
    MIDI.sendControlChange(10, i, 10);  // cc number, cc value, channel
    delay(50);
  }

  // Additional MIDI messages can be sent similarly...
}
