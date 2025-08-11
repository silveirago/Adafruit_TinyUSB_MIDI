#ifndef ADAFRUIT_TINYUSB_MIDI_H
#define ADAFRUIT_TINYUSB_MIDI_H

#include <Arduino.h>

#if defined(ARDUINO_UNOR4_MINIMA) || defined(ARDUINO_UNOR4_WIFI) || defined(ARDUINO_NANO_R4)
#define ADAFRUIT_TINYUSB_MIDI_RENESAS
class USBMIDI;
using TinyUSBMIDI_Device = USBMIDI;
#else
class Adafruit_USBD_MIDI;
using TinyUSBMIDI_Device = Adafruit_USBD_MIDI;
#endif

// MIDI class definition for sending MIDI messages
class Adafruit_TinyUSB_MIDI {
public:
    Adafruit_TinyUSB_MIDI(uint8_t n_cables = 1);

    bool begin();

    void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel);
    void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel);

    void sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel);
    void sendProgramChange(uint8_t programNumber, uint8_t channel);
    void sendPitchBend(int16_t bendValue, uint8_t channel);

    void sendSysEx(size_t length, uint8_t *data);
    void sendAfterTouch(uint8_t pressure, uint8_t channel);
    void sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel);

    void sendTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble);
    void sendSongPosition(uint16_t beats);
    void sendSongSelect(uint8_t songNumber);
    void sendTuneRequest();
    void sendRealTime(uint8_t realTimeType);

    TinyUSBMIDI_Device& getMidiInstance();

private:
    TinyUSBMIDI_Device _midi;
};

extern Adafruit_TinyUSB_MIDI MIDI;  // Global MIDI instance provided by the library

// MIDI Input class definition for receiving MIDI messages
#ifndef ADAFRUIT_TINYUSB_MIDI_RENESAS
class Adafruit_TinyUSB_MIDI_Input {
public:
    // Constructor
    Adafruit_TinyUSB_MIDI_Input(TinyUSBMIDI_Device &midiInstance);

    // Functions to set callback functions
    void setHandleNoteOn(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity));
    void setHandleNoteOff(void (*fptr)(uint8_t channel, uint8_t note, uint8_t velocity));
    void setHandleControlChange(void (*fptr)(uint8_t channel, uint8_t controlNumber, uint8_t controlValue));
    void setHandleProgramChange(void (*fptr)(uint8_t channel, uint8_t programNumber));
    void setHandlePitchBend(void (*fptr)(uint8_t channel, int16_t bendValue));
    void setHandleChannelPressure(void (*fptr)(uint8_t channel, uint8_t pressure));
    void setHandleAfterTouch(void (*fptr)(uint8_t channel, uint8_t note, uint8_t pressure));
    void setHandlePolyPressure(void (*fptr)(uint8_t channel, uint8_t note, uint8_t pressure));
    void setHandleSysEx(void (*fptr)(size_t length, uint8_t *data));
    void setHandleTimeCodeQuarterFrame(void (*fptr)(uint8_t typeNibble, uint8_t valuesNibble));
    void setHandleSongPosition(void (*fptr)(uint16_t beats));
    void setHandleSongSelect(void (*fptr)(uint8_t songNumber));
    void setHandleTuneRequest(void (*fptr)());
    void setHandleRealTime(void (*fptr)(uint8_t realTimeType));

    // Function to process incoming MIDI data
    void read();

private:
    // Reference to MIDI instance
    TinyUSBMIDI_Device &_midi;

    // Callback function pointers
    void (*handleNoteOn)(uint8_t channel, uint8_t note, uint8_t velocity);
    void (*handleNoteOff)(uint8_t channel, uint8_t note, uint8_t velocity);
    void (*handleControlChange)(uint8_t channel, uint8_t controlNumber, uint8_t controlValue);
    void (*handleProgramChange)(uint8_t channel, uint8_t programNumber);
    void (*handlePitchBend)(uint8_t channel, int16_t bendValue);
    void (*handleChannelPressure)(uint8_t channel, uint8_t pressure);
    void (*handleAfterTouch)(uint8_t channel, uint8_t note, uint8_t pressure);
    void (*handlePolyPressure)(uint8_t channel, uint8_t note, uint8_t pressure);
    void (*handleSysEx)(size_t length, uint8_t *data);
    void (*handleTimeCodeQuarterFrame)(uint8_t typeNibble, uint8_t valuesNibble);
    void (*handleSongPosition)(uint16_t beats);
    void (*handleSongSelect)(uint8_t songNumber);
    void (*handleTuneRequest)();
    void (*handleRealTime)(uint8_t realTimeType);

    // Buffer for assembling SysEx messages
    uint8_t _sysexBuffer[256];
    size_t _sysexLength;
    bool _inSysEx;

    // Function to parse incoming MIDI data
    void parseMessage(uint8_t *data, size_t length);
};
#endif

#endif // ADAFRUIT_TINYUSB_MIDI_H
