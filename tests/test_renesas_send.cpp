#include "Adafruit_TinyUSB_MIDI.h"
#include <cassert>
#include <iostream>

int main() {
  Adafruit_TinyUSB_MIDI midi;
  midi.begin();
  midi.sendNoteOn(60, 127, 0);
  auto &inst = midi.getMidiInstance();
  if (inst.sent.empty()) return 1;
  auto call = inst.sent.back();
  assert(call[0] == 0x90);
  assert(call[1] == 60);
  assert(call[2] == 127);
  std::cout << "Renesas send test passed" << std::endl;
  return 0;
}
