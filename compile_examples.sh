#!/bin/bash
set -euo pipefail

BOARD_TINYUSB="adafruit:nrf52:feather_nrf52840_express"
BOARD_RENESAS="arduino:renesas_uno:unor4_minima"

# Build all examples for both targets
for sketch in Examples/*/*.ino; do
  echo "Building $sketch for TinyUSB"
  arduino-cli compile --fqbn "$BOARD_TINYUSB" "$sketch"
  echo "Building $sketch for Renesas"
  arduino-cli compile --fqbn "$BOARD_RENESAS" "$sketch"
done

# Host-side regression tests
mkdir -p build

echo "Compiling TinyUSB host tests"
g++ -std=c++17 -I. -Itests/stubs tests/test_tinyusb_send_receive.cpp Adafruit_TinyUSB_MIDI.cpp -o build/test_tinyusb
./build/test_tinyusb || exit 1

echo "Compiling SysEx host tests"
g++ -std=c++17 -I. -Itests/stubs tests/test_sysex_receive.cpp Adafruit_TinyUSB_MIDI.cpp -o build/test_sysex
./build/test_sysex || exit 1

echo "Compiling Renesas host tests"
g++ -std=c++17 -I. -Itests/stubs -DADAFRUIT_TINYUSB_MIDI_RENESAS tests/test_renesas_send.cpp Adafruit_TinyUSB_MIDI.cpp -o build/test_renesas
./build/test_renesas || exit 1
