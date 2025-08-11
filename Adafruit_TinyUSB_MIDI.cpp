#include "Adafruit_TinyUSB_MIDI.h"

#if defined(ARDUINO_ARCH_RENESAS)
static RenesasUSBTransport _defaultTransport;
#else
static TinyUSBTransport _defaultTransport;
#endif

Adafruit_TinyUSB_MIDI MIDI(_defaultTransport);

// Adafruit_TinyUSB_MIDI constructor
Adafruit_TinyUSB_MIDI::Adafruit_TinyUSB_MIDI(IMIDITransport &transport) : _transport(transport) {}

// Begin MIDI interface
bool Adafruit_TinyUSB_MIDI::begin() {
    return _transport.begin();
}

// Expose the transport
IMIDITransport& Adafruit_TinyUSB_MIDI::getTransport() {
    return _transport;
}

// Implementing the sending functions

void Adafruit_TinyUSB_MIDI::sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {
    _transport.sendNoteOn(note, velocity, channel);
}

void Adafruit_TinyUSB_MIDI::sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) {
    _transport.sendNoteOff(note, velocity, channel);
}

// Control Change
void Adafruit_TinyUSB_MIDI::sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel) {
    _transport.sendControlChange(controlNumber, controlValue, channel);
}

// Program Change
void Adafruit_TinyUSB_MIDI::sendProgramChange(uint8_t programNumber, uint8_t channel) {
    _transport.sendProgramChange(programNumber, channel);
}

// Pitch Bend
void Adafruit_TinyUSB_MIDI::sendPitchBend(int16_t bendValue, uint8_t channel) {
    _transport.sendPitchBend(bendValue, channel);
}

// SysEx
void Adafruit_TinyUSB_MIDI::sendSysEx(size_t length, uint8_t *data) {
    _transport.sendSysEx(length, data);
}

// Channel Pressure
void Adafruit_TinyUSB_MIDI::sendChannelPressure(uint8_t pressure, uint8_t channel) {
    _transport.sendChannelPressure(pressure, channel);
}

// Aftertouch
void Adafruit_TinyUSB_MIDI::sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel) {
    _transport.sendAfterTouch(note, pressure, channel);
}

// Poly Pressure
void Adafruit_TinyUSB_MIDI::sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel) {
    _transport.sendPolyPressure(note, pressure, channel);
}

// Time Code Quarter Frame
void Adafruit_TinyUSB_MIDI::sendTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble) {
    _transport.sendTimeCodeQuarterFrame(typeNibble, valuesNibble);
}

// Song Position
void Adafruit_TinyUSB_MIDI::sendSongPosition(uint16_t beats) {
    _transport.sendSongPosition(beats);
}

// Song Select
void Adafruit_TinyUSB_MIDI::sendSongSelect(uint8_t songNumber) {
    _transport.sendSongSelect(songNumber);
}

// Tune Request
void Adafruit_TinyUSB_MIDI::sendTuneRequest() {
    _transport.sendTuneRequest();
}

// Real-Time Messages
void Adafruit_TinyUSB_MIDI::sendRealTime(uint8_t realTimeType) {
    _transport.sendRealTime(realTimeType);
}

// Adafruit_TinyUSB_MIDI_Input constructor
Adafruit_TinyUSB_MIDI_Input::Adafruit_TinyUSB_MIDI_Input(IMIDITransport &transport) : _transport(transport) {
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
    uint8_t data[4]; // Buffer for incoming MIDI data

    while (_transport.available()) { // Check if there is data available
        if (_transport.readPacket(data)) { // Read the incoming packet into the data buffer
            parseMessage(data, 4); // Parse the incoming message
        }
    }
}

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
