// Adafruit TinyUSB MIDI implementation
#include "Adafruit_TinyUSB_MIDI.h"

// Initialize the global MIDI instance
//Adafruit_TinyUSB_MIDI MIDI;

#ifdef ADAFRUIT_TINYUSB_MIDI_RENESAS

Adafruit_TinyUSB_MIDI::Adafruit_TinyUSB_MIDI(uint8_t n_cables) : _midi() {}

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

void Adafruit_TinyUSB_MIDI::sendChannelPressure(uint8_t pressure, uint8_t channel) {
    _midi.sendChannelPressure(pressure, channel);
}

void Adafruit_TinyUSB_MIDI::sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel) {
    _midi.sendAfterTouch(note, pressure, channel);
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

Adafruit_TinyUSB_MIDI::Adafruit_TinyUSB_MIDI(uint8_t n_cables) : _midi(n_cables) {}

bool Adafruit_TinyUSB_MIDI::begin() {
    return _midi.begin();
}

TinyUSBMIDI_Device& Adafruit_TinyUSB_MIDI::getMidiInstance() {
    return _midi;
}

void Adafruit_TinyUSB_MIDI::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x09), static_cast<uint8_t>(0x90 | (channel & 0x0F)), note, velocity};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x08), static_cast<uint8_t>(0x80 | (channel & 0x0F)), note, velocity};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0B), static_cast<uint8_t>(0xB0 | (channel & 0x0F)), controlNumber, controlValue};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendProgramChange(uint8_t programNumber, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0C), static_cast<uint8_t>(0xC0 | (channel & 0x0F)), programNumber, 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendPitchBend(int16_t bendValue, uint8_t channel) {
    uint8_t lsb = bendValue & 0x7F;
    uint8_t msb = (bendValue >> 7) & 0x7F;
    uint8_t packet[4] = {static_cast<uint8_t>(0x0E), static_cast<uint8_t>(0xE0 | (channel & 0x0F)), lsb, msb};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendSysEx(size_t length, uint8_t *data) {
    _midi.write(data, length);
}

void Adafruit_TinyUSB_MIDI::sendChannelPressure(uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0D), static_cast<uint8_t>(0xD0 | (channel & 0x0F)), pressure, 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0A), static_cast<uint8_t>(0xA0 | (channel & 0x0F)), note, pressure};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x0A), static_cast<uint8_t>(0xA0 | (channel & 0x0F)), note, pressure};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x02), static_cast<uint8_t>(0xF1), static_cast<uint8_t>((typeNibble << 4) | (valuesNibble & 0x0F)), 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendSongPosition(uint16_t beats) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x03), static_cast<uint8_t>(0xF2), static_cast<uint8_t>(beats & 0x7F), static_cast<uint8_t>((beats >> 7) & 0x7F)};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendSongSelect(uint8_t songNumber) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x02), static_cast<uint8_t>(0xF3), songNumber, 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendTuneRequest() {
    uint8_t packet[4] = {static_cast<uint8_t>(0x01), static_cast<uint8_t>(0xF6), 0, 0};
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI::sendRealTime(uint8_t realTimeType) {
    uint8_t packet[4] = {static_cast<uint8_t>(0x01), realTimeType, 0, 0};
    _midi.writePacket(packet);
}

#endif // ADAFRUIT_TINYUSB_MIDI_RENESAS

#ifndef ADAFRUIT_TINYUSB_MIDI_RENESAS

Adafruit_TinyUSB_MIDI_Input::Adafruit_TinyUSB_MIDI_Input(TinyUSBMIDI_Device &midiInstance) : _midi(midiInstance) {
    // Initialize callback pointers to nullptr
    handleNoteOn = nullptr;
    handleNoteOff = nullptr;
    handleControlChange = nullptr;
    handleProgramChange = nullptr;
    handlePitchBend = nullptr;
    handleChannelPressure = nullptr;
    handleAfterTouch = nullptr;
    handlePolyPressure = nullptr;
    handleSysEx = nullptr;
    handleTimeCodeQuarterFrame = nullptr;
    handleSongPosition = nullptr;
    handleSongSelect = nullptr;
    handleTuneRequest = nullptr;
    handleRealTime = nullptr;
}

// Implementing the set callback functions

void Adafruit_TinyUSB_MIDI_Input::setHandleNoteOn(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
    handleNoteOn = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleNoteOff(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity)) {
    handleNoteOff = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleControlChange(void (*fptr)(uint8_t channel, uint8_t controlNumber, uint8_t controlValue)) {
    handleControlChange = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleProgramChange(void (*fptr)(uint8_t channel, uint8_t programNumber)) {
    handleProgramChange = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandlePitchBend(void (*fptr)(uint8_t channel, int16_t bendValue)) {
    handlePitchBend = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleChannelPressure(void (*fptr)(uint8_t channel, uint8_t pressure)) {
    handleChannelPressure = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleAfterTouch(void (*fptr)(uint8_t channel, uint8_t note, uint8_t pressure)) {
    handleAfterTouch = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandlePolyPressure(void (*fptr)(uint8_t channel, uint8_t note, uint8_t pressure)) {
    handlePolyPressure = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleSysEx(void (*fptr)(size_t length, uint8_t *data)) {
    handleSysEx = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleTimeCodeQuarterFrame(void (*fptr)(uint8_t typeNibble, uint8_t valuesNibble)) {
    handleTimeCodeQuarterFrame = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleSongPosition(void (*fptr)(uint16_t beats)) {
    handleSongPosition = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleSongSelect(void (*fptr)(uint8_t songNumber)) {
    handleSongSelect = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleTuneRequest(void (*fptr)()) {
    handleTuneRequest = fptr;
}

void Adafruit_TinyUSB_MIDI_Input::setHandleRealTime(void (*fptr)(uint8_t realTimeType)) {
    handleRealTime = fptr;
}

// Function to process incoming MIDI data
void Adafruit_TinyUSB_MIDI_Input::read() {
    uint8_t data[4];
    while (_midi.available()) {
        if (_midi.readPacket(data)) {
            parseMessage(data, 4);
        }
    }
}

// Function to parse incoming MIDI messages
// Function to parse incoming MIDI messages
void Adafruit_TinyUSB_MIDI_Input::parseMessage(uint8_t *data, size_t length) {
    uint8_t statusByte = data[1] & 0xF0;
    uint8_t channel = data[1] & 0x0F;

    switch (statusByte) {
        case 0x90: // Note On
            if (handleNoteOn && data[3] > 0) {
                handleNoteOn(channel, data[2], data[3]);
            } else if (handleNoteOff && data[3] == 0) { // Treat Note On with 0 velocity as Note Off
                handleNoteOff(channel, data[2], data[3]);
            }
            break;

        case 0x80: // Note Off
            if (handleNoteOff) {
                handleNoteOff(channel, data[2], data[3]);
            }
            break;

        case 0xB0: // Control Change
            if (handleControlChange) {
                handleControlChange(channel, data[2], data[3]);
            }
            break;

        case 0xC0: // Program Change
            if (handleProgramChange) {
                handleProgramChange(channel, data[2]);
            }
            break;

        case 0xE0: // Pitch Bend
            if (handlePitchBend) {
                int16_t bendValue = (data[3] << 7) | data[2]; // Combine MSB and LSB
                handlePitchBend(channel, bendValue);
            }
            break;

        case 0xD0: // Channel Pressure (Aftertouch)
            if (handleChannelPressure) {
                handleChannelPressure(channel, data[2]);
            }
            break;

        case 0xA0: // Polyphonic Key Pressure (Poly Aftertouch)
            if (handlePolyPressure) {
                handlePolyPressure(channel, data[2], data[3]);
            }
            break;

        case 0xF0: // System Messages
            if (data[1] == 0xF0 && handleSysEx) { // SysEx
                handleSysEx(length, data);
            } else if (data[1] == 0xF8 || data[1] == 0xFA || data[1] == 0xFB || data[1] == 0xFC || data[1] == 0xFE || data[1] == 0xFF) {
                if (handleRealTime) {
                    handleRealTime(data[1]);
                }
            }
            break;

        default:
            // Other MIDI message types can be handled here
            break;
    }
}

#endif // ADAFRUIT_TINYUSB_MIDI_RENESAS
