#include "Adafruit_TinyUSB_MIDI.h"
#include <Adafruit_TinyUSB.h>
#include <cassert>
#include <iostream>

static bool noteOnCalled = false;
void onNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (channel == 0 && note == 0x3D && velocity == 0x55) {
    noteOnCalled = true;
  }
}

int main() {
  Adafruit_TinyUSB_MIDI midi = Adafruit_TinyUSB_MIDI::makeDefault();
  midi.begin();
  midi.sendNoteOn(0x3C, 0x7F, 0);
  auto &inst = midi.getMidiInstance();
  if (inst.sent.empty()) return 1;
  auto pkt = inst.sent.back();
  assert(pkt[0] == 0x09);
  assert(pkt[1] == 0x90);
  assert(pkt[2] == 0x3C);
  assert(pkt[3] == 0x7F);

  Adafruit_TinyUSB_MIDI_Input input(midi.getMidiInstance());
  input.setHandleNoteOn(onNoteOn);
  inst.queueInput({0x09, 0x90, 0x3D, 0x55});
  input.read();
  assert(noteOnCalled);
  std::cout << "TinyUSB send/receive test passed" << std::endl;
  return 0;
}
