#include "Adafruit_TinyUSB_MIDI.h"
#include <Adafruit_TinyUSB.h>
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
  Adafruit_TinyUSB_MIDI midi = Adafruit_TinyUSB_MIDI::makeDefault();
  midi.begin();
  auto &inst = midi.getMidiInstance();

  Adafruit_TinyUSB_MIDI_Input input(midi.getMidiInstance());
  input.setHandleSysEx(onSysEx);

  // SysEx message containing a zero byte in the payload: F0 01 00 02 F7
  inst.queueInput({0x04, 0xF0, 0x01, 0x00});
  inst.queueInput({0x06, 0x02, 0xF7, 0x00});

  input.read();

  assert(sysexLen == 5);
  uint8_t expected[5] = {0xF0, 0x01, 0x00, 0x02, 0xF7};
  assert(std::memcmp(sysexData, expected, 5) == 0);
  std::cout << "SysEx zero byte test passed" << std::endl;
  return 0;
}
