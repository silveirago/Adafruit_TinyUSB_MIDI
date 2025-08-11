#include "Adafruit_TinyUSB_MIDI.h"
#include <cassert>
#include <cstring>
#include <iostream>

static size_t sysexLen = 0;
static uint8_t sysexData[16];

void onSysEx(size_t len, uint8_t *data) {
  sysexLen = len;
  std::memcpy(sysexData, data, len);
}

int main() {
  Adafruit_TinyUSB_MIDI midi;
  midi.begin();
  auto &inst = midi.getMidiInstance();

  Adafruit_TinyUSB_MIDI_Input input(midi.getMidiInstance());
  input.setHandleSysEx(onSysEx);

  // queue a SysEx message split across three packets
  inst.queueInput({0x04, 0xF0, 0x01, 0x02});
  inst.queueInput({0x04, 0x03, 0x04, 0x05});
  inst.queueInput({0x05, 0xF7, 0x00, 0x00});

  input.read();

  assert(sysexLen == 7);
  uint8_t expected[7] = {0xF0,0x01,0x02,0x03,0x04,0x05,0xF7};
  assert(std::memcmp(sysexData, expected, 7) == 0);
  std::cout << "SysEx receive test passed" << std::endl;
  return 0;
}
