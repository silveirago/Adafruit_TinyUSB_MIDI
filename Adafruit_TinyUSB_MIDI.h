#ifndef ADAFRUIT_TINYUSB_MIDI_H
#define ADAFRUIT_TINYUSB_MIDI_H

#include <Adafruit_TinyUSB.h>

// MIDI class definition
class Adafruit_TinyUSB_MIDI_Class {
public:
    Adafruit_TinyUSB_MIDI_Class(uint8_t n_cables = 1);  // Constructor

    bool begin();  // Initialize MIDI interface

    void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);

    void sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel);
    void sendProgramChange(uint8_t programNumber, uint8_t channel);
    void sendPitchBend(int16_t bendValue, uint8_t channel);

    void sendSysEx(size_t length, uint8_t *data);
    void sendChannelPressure(uint8_t pressure, uint8_t channel);
    void sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel);
    void sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel);

private:
    Adafruit_USBD_MIDI _midi;
};

extern Adafruit_TinyUSB_MIDI_Class MIDI;  // Global MIDI instance

#endif // ADAFRUIT_TINYUSB_MIDI_H
