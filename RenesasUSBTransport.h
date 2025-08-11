#ifndef RENESAS_USB_TRANSPORT_H
#define RENESAS_USB_TRANSPORT_H

#include "IMIDITransport.h"

#if defined(ARDUINO_ARCH_RENESAS)
#include <USB-MIDI.h>

class RenesasUSBTransport : public IMIDITransport {
public:
    RenesasUSBTransport(uint8_t n_cables = 1);

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

    USBMIDI& getMIDI();

private:
    USBMIDI _midi;
};

#endif // ARDUINO_ARCH_RENESAS

#endif // RENESAS_USB_TRANSPORT_H
