#include "TinyUSBTransport.h"

TinyUSBTransport::TinyUSBTransport(uint8_t n_cables) : _midi(n_cables) {}

bool TinyUSBTransport::begin() { return _midi.begin(); }

bool TinyUSBTransport::available() { return _midi.available(); }

bool TinyUSBTransport::readPacket(uint8_t *data) { return _midi.readPacket(data); }

void TinyUSBTransport::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x09), static_cast<uint8_t>(0x90 | (channel & 0x0F)), note, velocity};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x08), static_cast<uint8_t>(0x80 | (channel & 0x0F)), note, velocity};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0B), static_cast<uint8_t>(0xB0 | (channel & 0x0F)), controlNumber, controlValue};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendProgramChange(uint8_t programNumber, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0C), static_cast<uint8_t>(0xC0 | (channel & 0x0F)), programNumber, 0};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendPitchBend(int16_t bendValue, uint8_t channel) {
    uint8_t lsb = bendValue & 0x7F;
    uint8_t msb = (bendValue >> 7) & 0x7F;
    uint8_t packet[4] = {static_cast<uint8_t>(0x0E), static_cast<uint8_t>(0xE0 | (channel & 0x0F)), lsb, msb};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendSysEx(size_t length, uint8_t *data) {
    _midi.write(data, length);
}

void TinyUSBTransport::sendChannelPressure(uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0D), static_cast<uint8_t>(0xD0 | (channel & 0x0F)), pressure, 0};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0A), static_cast<uint8_t>(0xA0 | (channel & 0x0F)), note, pressure};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0A), static_cast<uint8_t>(0xA0 | (channel & 0x0F)), note, pressure};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x02), static_cast<uint8_t>(0xF1), static_cast<uint8_t>((typeNibble << 4) | (valuesNibble & 0x0F)), 0};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendSongPosition(uint16_t beats) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x03), static_cast<uint8_t>(0xF2), static_cast<uint8_t>(beats & 0x7F), static_cast<uint8_t>((beats >> 7) & 0x7F)};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendSongSelect(uint8_t songNumber) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x02), static_cast<uint8_t>(0xF3), songNumber, 0};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendTuneRequest() {
    uint8_t packet[4] = {static_cast<uint8_t>(0x01), static_cast<uint8_t>(0xF6), 0, 0};
    _midi.writePacket(packet);
}

void TinyUSBTransport::sendRealTime(uint8_t realTimeType) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x01), realTimeType, 0, 0};
    _midi.writePacket(packet);
}

Adafruit_USBD_MIDI& TinyUSBTransport::getMIDI() { return _midi; }
