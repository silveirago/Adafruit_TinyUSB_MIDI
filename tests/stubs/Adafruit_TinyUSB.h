#ifndef STUB_ADAFRUIT_TINYUSB_H
#define STUB_ADAFRUIT_TINYUSB_H
#include <array>
#include <queue>
#include <vector>
#include <cstdint>
#include <cstring>

class Adafruit_USBD_MIDI {
public:
  Adafruit_USBD_MIDI(uint8_t n_cables = 1) {}
  bool begin() { return true; }
  void writePacket(uint8_t const packet[4]) {
    std::array<uint8_t,4> p; std::memcpy(p.data(), packet, 4); sent.push_back(p);
  }
  void write(uint8_t const* data, size_t length) {}
  bool available() const { return !input.empty(); }
  bool readPacket(uint8_t* data) {
    if (input.empty()) return false; auto p = input.front(); input.pop(); std::memcpy(data,p.data(),4); return true;
  }
  void queueInput(std::array<uint8_t,4> pkt) { input.push(pkt); }
  std::vector<std::array<uint8_t,4>> sent;
private:
  std::queue<std::array<uint8_t,4>> input;
};

#endif
