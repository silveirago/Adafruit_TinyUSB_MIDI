#ifndef IMIDI_TRANSPORT_H
#define IMIDI_TRANSPORT_H

#include <Arduino.h>
#include <stddef.h>

class IMIDITransport {
public:
    virtual ~IMIDITransport() {}

    virtual bool begin() = 0;
    virtual bool available() = 0;
    virtual bool readPacket(uint8_t *data) = 0;

    virtual void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) = 0;
    virtual void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) = 0;
    virtual void sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel) = 0;
    virtual void sendProgramChange(uint8_t programNumber, uint8_t channel) = 0;
    virtual void sendPitchBend(int16_t bendValue, uint8_t channel) = 0;
    virtual void sendSysEx(size_t length, uint8_t *data) = 0;
    virtual void sendChannelPressure(uint8_t pressure, uint8_t channel) = 0;
    virtual void sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel) = 0;
    virtual void sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel) = 0;
    virtual void sendTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble) = 0;
    virtual void sendSongPosition(uint16_t beats) = 0;
    virtual void sendSongSelect(uint8_t songNumber) = 0;
    virtual void sendTuneRequest() = 0;
    virtual void sendRealTime(uint8_t realTimeType) = 0;
};

#endif // IMIDI_TRANSPORT_H
