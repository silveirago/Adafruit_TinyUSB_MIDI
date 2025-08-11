#ifndef STUB_USBMIDI_H
#define STUB_USBMIDI_H
#include <array>
#include <vector>
#include <cstdint>

class USBMIDI {
public:
  USBMIDI(uint8_t n_cables = 1) {}
  void begin() {}
  void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    sent.push_back({static_cast<uint8_t>(0x90 | (channel & 0x0F)), note, velocity});
  }
  void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    sent.push_back({static_cast<uint8_t>(0x80 | (channel & 0x0F)), note, velocity});
  }
  void sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel) {
    sent.push_back({static_cast<uint8_t>(0xB0 | (channel & 0x0F)), controlNumber, controlValue});
  }
  void sendProgramChange(uint8_t programNumber, uint8_t channel) {
    sent.push_back({static_cast<uint8_t>(0xC0 | (channel & 0x0F)), programNumber, 0});
  }
  void sendPitchBend(int16_t bendValue, uint8_t channel) {
    sent.push_back({static_cast<uint8_t>(0xE0 | (channel & 0x0F)), static_cast<uint8_t>(bendValue & 0x7F), static_cast<uint8_t>((bendValue >> 7) & 0x7F)});
  }
  void sendSysEx(uint8_t *data, size_t length) {}
  void sendChannelPressure(uint8_t pressure, uint8_t channel) {
    sent.push_back({static_cast<uint8_t>(0xD0 | (channel & 0x0F)), pressure, 0});
  }
  void sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel) {
    sent.push_back({static_cast<uint8_t>(0xA0 | (channel & 0x0F)), note, pressure});
  }
  void sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel) {
    sent.push_back({static_cast<uint8_t>(0xA0 | (channel & 0x0F)), note, pressure});
  }
  void sendTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble) {}
  void sendSongPosition(uint16_t beats) {}
  void sendSongSelect(uint8_t songNumber) {}
  void sendTuneRequest() {}
  void sendRealTime(uint8_t realTimeType) {}

  std::vector<std::array<uint8_t,3>> sent;
};

#endif
