#ifndef TINYUSB_TRANSPORT_H
#define TINYUSB_TRANSPORT_H

#include <Adafruit_TinyUSB.h>
#include "IMIDITransport.h"

class TinyUSBTransport : public IMIDITransport {
public:
    TinyUSBTransport(uint8_t n_cables = 1);

    bool begin() override;
    bool available() override;
    bool readPacket(uint8_t *data) override;

    void sendNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) override;
    void sendNoteOff(uint8_t note, uint8_t velocity, uint8_t channel) override;
    void sendControlChange(uint8_t controlNumber, uint8_t controlValue, uint8_t channel) override;
    void sendProgramChange(uint8_t programNumber, uint8_t channel) override;
    void sendPitchBend(int16_t bendValue, uint8_t channel) override;
    void sendSysEx(size_t length, uint8_t *data) override;
    void sendChannelPressure(uint8_t pressure, uint8_t channel) override;
    void sendAfterTouch(uint8_t note, uint8_t pressure, uint8_t channel) override;
    void sendPolyPressure(uint8_t note, uint8_t pressure, uint8_t channel) override;
    void sendTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble) override;
    void sendSongPosition(uint16_t beats) override;
    void sendSongSelect(uint8_t songNumber) override;
    void sendTuneRequest() override;
    void sendRealTime(uint8_t realTimeType) override;

    Adafruit_USBD_MIDI& getMIDI();

private:
    Adafruit_USBD_MIDI _midi;
};

#endif // TINYUSB_TRANSPORT_H
