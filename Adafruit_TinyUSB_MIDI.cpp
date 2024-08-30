#include "Adafruit_TinyUSB_MIDI.h"

// Global instance of the MIDI object
Adafruit_TinyUSB_MIDI_Class MIDI;

Adafruit_TinyUSB_MIDI_Class::Adafruit_TinyUSB_MIDI_Class(uint8_t n_cables)
    : _midi(n_cables) {}

bool Adafruit_TinyUSB_MIDI_Class::begin() {
    return _midi.begin();
}

void Adafruit_TinyUSB_MIDI_Class::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t packet[4] = {
        static_cast<uint8_t>(0x09),
        static_cast<uint8_t>(0x90 | (channel & 0x0F)),
        note,
        velocity
    };
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI_Class::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    uint8_t packet[4] = {
        static_cast<uint8_t>(0x08),
        static_cast<uint8_t>(0x80 | (channel & 0x0F)),
        note,
        velocity
    };
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI_Class::sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel) {
    uint8_t packet[4] = {
        static_cast<uint8_t>(0x0B),
        static_cast<uint8_t>(0xB0 | (channel & 0x0F)),
        controlNumber,
        controlValue
    };
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI_Class::sendProgramChange(uint8_t programNumber, uint8_t channel) {
    uint8_t packet[4] = {
        static_cast<uint8_t>(0x0C),
        static_cast<uint8_t>(0xC0 | (channel & 0x0F)),
        programNumber,
        0
    };
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI_Class::sendPitchBend(int16_t bendValue, uint8_t channel) {
    uint8_t packet[4] = {
        static_cast<uint8_t>(0x0E),
        static_cast<uint8_t>(0xE0 | (channel & 0x0F)),
        static_cast<uint8_t>(bendValue & 0x7F),
        static_cast<uint8_t>((bendValue >> 7) & 0x7F)
    };
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI_Class::sendSysEx(size_t length, uint8_t *data) {
    for (size_t i = 0; i < length; i += 3) {
        uint8_t packet[4] = {
            static_cast<uint8_t>(0x04),
            data[i],
            data[i + 1],
            data[i + 2]
        };
        _midi.writePacket(packet);
    }
}

void Adafruit_TinyUSB_MIDI_Class::sendChannelPressure(uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {
        static_cast<uint8_t>(0x0D),
        static_cast<uint8_t>(0xD0 | (channel & 0x0F)),
        pressure,
        0
    };
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI_Class::sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {
        static_cast<uint8_t>(0x0A),
        static_cast<uint8_t>(0xA0 | (channel & 0x0F)),
        note,
        pressure
    };
    _midi.writePacket(packet);
}

void Adafruit_TinyUSB_MIDI_Class::sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel) {
    uint8_t packet[4] = {
        static_cast<uint8_t>(0x0A),
        static_cast<uint8_t>(0xA0 | (channel & 0x0F)),
        note,
        pressure
    };
    _midi.writePacket(packet);
}
