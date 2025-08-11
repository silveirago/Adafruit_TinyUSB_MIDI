// Adafruit TinyUSB MIDI implementation
#if defined(ARDUINO_UNOR4_MINIMA) || defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4) || defined(ADAFRUIT_TINYUSB_MIDI_RENESAS)
#include <USBMIDI.h>
#else
#include <Adafruit_TinyUSB.h>
#endif
#include "Adafruit_TinyUSB_MIDI.h"

// Helper factory that chooses an available transport at runtime.
static TinyUSBMIDI_Device &selectTransport(uint8_t n_cables) {
#ifdef ADAFRUIT_TINYUSB_MIDI_RENESAS
    (void)n_cables;
    static TinyUSBMIDI_Device transport;  // Renesas USBMIDI doesn't take cable count
#else
    static TinyUSBMIDI_Device transport(n_cables);
#endif
    return transport;
}

Adafruit_TinyUSB_MIDI Adafruit_TinyUSB_MIDI::makeDefault(uint8_t n_cables) {
    return Adafruit_TinyUSB_MIDI(selectTransport(n_cables));
}

// Initialize the global MIDI instance using the factory
Adafruit_TinyUSB_MIDI MIDI = Adafruit_TinyUSB_MIDI::makeDefault();

Adafruit_TinyUSB_MIDI::Adafruit_TinyUSB_MIDI(TinyUSBMIDI_Device &transport)
    : _midi(transport) {}

#ifdef ADAFRUIT_TINYUSB_MIDI_RENESAS

bool Adafruit_TinyUSB_MIDI::begin() {
    _midi.begin();
    return true;
}

TinyUSBMIDI_Device& Adafruit_TinyUSB_MIDI::getMidiInstance() {
    return _midi;
}

void Adafruit_TinyUSB_MIDI::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    _midi.sendNoteOn(note, velocity, channel);
}

void Adafruit_TinyUSB_MIDI::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    _midi.sendNoteOff(note, velocity, channel);
}

void Adafruit_TinyUSB_MIDI::sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel) {
    _midi.sendControlChange(controlNumber, controlValue, channel);
}

void Adafruit_TinyUSB_MIDI::sendProgramChange(uint8_t programNumber, uint8_t channel) {
    _midi.sendProgramChange(programNumber, channel);
}

void Adafruit_TinyUSB_MIDI::sendPitchBend(int16_t bendValue, uint8_t channel) {
    _midi.sendPitchBend(bendValue, channel);
}

void Adafruit_TinyUSB_MIDI::sendSysEx(size_t length, uint8_t *data) {
    _midi.sendSysEx(data, length);
}

void Adafruit_TinyUSB_MIDI::sendAfterTouch(uint8_t pressure, uint8_t channel) {
    _midi.sendChannelPressure(pressure, channel);
}

void Adafruit_TinyUSB_MIDI::sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel) {
    _midi.sendPolyPressure(note, pressure, channel);
}

void Adafruit_TinyUSB_MIDI::sendTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble) {
    _midi.sendTimeCodeQuarterFrame(typeNibble, valuesNibble);
}

void Adafruit_TinyUSB_MIDI::sendSongPosition(uint16_t beats) {
    _midi.sendSongPosition(beats);
}

void Adafruit_TinyUSB_MIDI::sendSongSelect(uint8_t songNumber) {
    _midi.sendSongSelect(songNumber);
}

void Adafruit_TinyUSB_MIDI::sendTuneRequest() {
    _midi.sendTuneRequest();
}

void Adafruit_TinyUSB_MIDI::sendRealTime(uint8_t realTimeType) {
    _midi.sendRealTime(realTimeType);
}

#else

bool Adafruit_TinyUSB_MIDI::begin() {
    return _midi.begin();
}

TinyUSBMIDI_Device& Adafruit_TinyUSB_MIDI::getMidiInstance() {
    return _midi;
}

void Adafruit_TinyUSB_MIDI::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t packet[4] = {0x09, static_cast<uint8_t>(0x90 | (channel & 0x0F)), note, velocity};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t packet[4] = {0x08, static_cast<uint8_t>(0x80 | (channel & 0x0F)), note, velocity};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel) {
    uint8_t packet[4] = {0x0B, static_cast<uint8_t>(0xB0 | (channel & 0x0F)), controlNumber, controlValue};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendProgramChange(uint8_t programNumber, uint8_t channel) {
    uint8_t packet[4] = {0x0C, static_cast<uint8_t>(0xC0 | (channel & 0x0F)), programNumber, 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendPitchBend(int16_t bendValue, uint8_t channel) {
    uint8_t lsb = bendValue & 0x7F;
    uint8_t msb = (bendValue >> 7) & 0x7F;
    uint8_t packet[4] = {0x0E, static_cast<uint8_t>(0xE0 | (channel & 0x0F)), lsb, msb};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendSysEx(size_t length, uint8_t *data) {
    _midi.write(data, length);
}

void Adafruit_TinyUSB_MIDI::sendAfterTouch(uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {0x0D, static_cast<uint8_t>(0xD0 | (channel & 0x0F)), pressure, 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {0x0A, static_cast<uint8_t>(0xA0 | (channel & 0x0F)), note, pressure};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble) {
    uint8_t packet[4] = {0x02, 0xF1, static_cast<uint8_t>((typeNibble << 4) | (valuesNibble & 0x0F)), 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendSongPosition(uint16_t beats) {
    uint8_t packet[4] = {0x03, 0xF2, static_cast<uint8_t>(beats & 0x7F), static_cast<uint8_t>((beats >> 7) & 0x7F)};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendSongSelect(uint8_t songNumber) {
    uint8_t packet[4] = {0x02, 0xF3, songNumber, 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendTuneRequest() {
    uint8_t packet[4] = {0x01, 0xF6, 0, 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendRealTime(uint8_t realTimeType) {
    uint8_t packet[4] = {0x01, realTimeType, 0, 0};
    _midi.writePacket(packet);
}

#endif // ADAFRUIT_TINYUSB_MIDI_RENESAS

#ifndef ADAFRUIT_TINYUSB_MIDI_RENESAS

Adafruit_TinyUSB_MIDI_Input::Adafruit_TinyUSB_MIDI_Input(TinyUSBMIDI_Device &midiInstance)
    : _midi(midiInstance), _sysexLength(0), _inSysEx(false),
      handleNoteOn(nullptr), handleNoteOff(nullptr),
      handleControlChange(nullptr), handleProgramChange(nullptr),
      handlePitchBend(nullptr), handleChannelPressure(nullptr),
      handleAfterTouch(nullptr), handlePolyPressure(nullptr),
      handleSysEx(nullptr), handleTimeCodeQuarterFrame(nullptr),
      handleSongPosition(nullptr), handleSongSelect(nullptr),
      handleTuneRequest(nullptr), handleRealTime(nullptr) {}

void Adafruit_TinyUSB_MIDI_Input::setHandleNoteOn(void (*fptr)(uint8_t, uint8_t, uint8_t)) { handleNoteOn = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleNoteOff(void (*fptr)(uint8_t, uint8_t, uint8_t)) { handleNoteOff = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleControlChange(void (*fptr)(uint8_t, uint8_t, uint8_t)) { handleControlChange = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleProgramChange(void (*fptr)(uint8_t, uint8_t)) { handleProgramChange = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandlePitchBend(void (*fptr)(uint8_t, int16_t)) { handlePitchBend = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleChannelPressure(void (*fptr)(uint8_t, uint8_t)) { handleChannelPressure = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleAfterTouch(void (*fptr)(uint8_t, uint8_t, uint8_t)) { handleAfterTouch = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandlePolyPressure(void (*fptr)(uint8_t, uint8_t, uint8_t)) { handlePolyPressure = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleSysEx(void (*fptr)(size_t, uint8_t *)) { handleSysEx = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleTimeCodeQuarterFrame(void (*fptr)(uint8_t, uint8_t)) { handleTimeCodeQuarterFrame = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleSongPosition(void (*fptr)(uint16_t)) { handleSongPosition = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleSongSelect(void (*fptr)(uint8_t)) { handleSongSelect = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleTuneRequest(void (*fptr)()) { handleTuneRequest = fptr; }
void Adafruit_TinyUSB_MIDI_Input::setHandleRealTime(void (*fptr)(uint8_t)) { handleRealTime = fptr; }

void Adafruit_TinyUSB_MIDI_Input::read() {
    uint8_t data[4];
    while (_midi.available()) {
        if (_midi.readPacket(data)) {
            parseMessage(data, 4);
        }
    }
}

void Adafruit_TinyUSB_MIDI_Input::parseMessage(uint8_t *data, size_t length) {
    (void)length;
    bool processedSysEx = false;

    for (size_t i = 1; i < 4; ++i) {
        uint8_t b = data[i];
        if (b == 0) continue;

        if (b >= 0xF8) { if (handleRealTime) handleRealTime(b); continue; }

        if (_inSysEx) {
            if (_sysexLength < sizeof(_sysexBuffer)) _sysexBuffer[_sysexLength++] = b;
            if (b == 0xF7) { if (handleSysEx) handleSysEx(_sysexLength, _sysexBuffer); _sysexLength = 0; _inSysEx = false; }
            processedSysEx = true; continue;
        }

        if (b == 0xF0) {
            _inSysEx = true; _sysexLength = 0;
            if (_sysexLength < sizeof(_sysexBuffer)) _sysexBuffer[_sysexLength++] = b;
            processedSysEx = true; continue;
        }
    }

    if (processedSysEx || _inSysEx) return;
    if (data[1] >= 0xF8) return;

    uint8_t statusByte = data[1] & 0xF0;
    uint8_t channel = data[1] & 0x0F;

    switch (statusByte) {
        case 0x90: if (handleNoteOn && data[3] > 0) handleNoteOn(channel, data[2], data[3]); else if (handleNoteOff && data[3] == 0) handleNoteOff(channel, data[2], data[3]); break;
        case 0x80: if (handleNoteOff) handleNoteOff(channel, data[2], data[3]); break;
        case 0xB0: if (handleControlChange) handleControlChange(channel, data[2], data[3]); break;
        case 0xC0: if (handleProgramChange) handleProgramChange(channel, data[2]); break;
        case 0xE0: if (handlePitchBend) handlePitchBend(channel, (data[3] << 7) | data[2]); break;
        case 0xD0: if (handleChannelPressure) handleChannelPressure(channel, data[2]); break;
        case 0xA0: if (handlePolyPressure) handlePolyPressure(channel, data[2], data[3]); break;
        case 0xF0:
            if (data[1] == 0xF1 && handleTimeCodeQuarterFrame) handleTimeCodeQuarterFrame((data[2] >> 4) & 0x07, data[2] & 0x0F);
            else if (data[1] == 0xF2 && handleSongPosition) handleSongPosition((data[3] << 7) | data[2]);
            else if (data[1] == 0xF3 && handleSongSelect) handleSongSelect(data[2]);
            else if (data[1] == 0xF6 && handleTuneRequest) handleTuneRequest();
            break;
    }
}

#endif // ADAFRUIT_TINYUSB_MIDI_RENESAS
