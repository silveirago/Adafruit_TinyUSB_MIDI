#include <Adafruit_TinyUSB_MIDI.h>

Adafruit_TinyUSB_MIDI_Class MIDI;

int delayTime = 30;

void setup() {
  // Initialize MIDI communication
  MIDI.begin();
}

void loop() {

  // Send MIDI notes from C2 to B2
  for (int i = 36; i < 48; i++) {
    MIDI.sendNoteOn(i, 127, 1);  // note, velocity, channel
    delay(delayTime);
    MIDI.sendNoteOff(i, 0, 1);  // note, velocity, channel (Note Off)
    delay(delayTime);
  }

  // Send Control Change messages
  for (int i = 1; i < 128; i++) {
    MIDI.sendControlChange(10, i, 10);  // cc number, cc value, channel
    delay(50);
  }

  // Send Program Change messages
  for (int i = 0; i < 128; i++) {
    MIDI.sendProgramChange(i, 1);  // program number, channel
    delay(delayTime);
  }

  // Send Pitch Bend messages
  for (int i = -8192; i <= 8191; i += 512) {  // Pitch bend range: -8192 to 8191
    MIDI.sendPitchBend(i, 1);  // bend value, channel
    delay(delayTime);
  }

  // Send Channel Pressure messages
  for (int i = 0; i < 128; i++) {
    MIDI.sendChannelPressure(i, 1);  // pressure value, channel
    delay(delayTime);
  }

  // Send Aftertouch messages
  for (int i = 36; i < 48; i++) {
    MIDI.sendAfterTouch(i, 64, 1);  // note, pressure, channel
    delay(delayTime);
  }

  // Send Polyphonic Aftertouch messages
  for (int i = 36; i < 48; i++) {
    MIDI.sendPolyPressure(i, 64, 1);  // note, pressure, channel
    delay(delayTime);
  }

  // Send SysEx messages
  uint8_t sysexData[3] = {0x7E, 0x7F, 0x09};  // Example SysEx data
  MIDI.sendSysEx(3, sysexData);
  delay(delayTime);

  // Send Time Code Quarter Frame messages
  for (int i = 0; i < 8; i++) {
    MIDI.sendTimeCodeQuarterFrame(i, 0);
    delay(delayTime);
  }

  // Send Song Position Pointer
  for (int i = 0; i < 16384; i += 128) {  // Value range 0 - 16383
    MIDI.sendSongPosition(i);
    delay(delayTime);
  }

  // Send Song Select messages
  for (int i = 0; i < 128; i++) {
    MIDI.sendSongSelect(i);
    delay(delayTime);
  }

  // Send Tune Request message
  MIDI.sendTuneRequest();
  delay(delayTime);

  // Send System Real-Time Messages
  // Clock
  for (int i = 0; i < 24; i++) {
    MIDI.sendRealTime(0xF8);
    delay(20);  // Send 24 clock messages per quarter note
  }

  // Start
  MIDI.sendRealTime(0xFA);
  delay(delayTime);

  // Stop
  MIDI.sendRealTime(0xFC);
  delay(delayTime);

  // Active Sensing
  MIDI.sendRealTime(0xFE);
  delay(delayTime);

  // System Reset
  MIDI.sendRealTime(0xFF);
  delay(delayTime);
}
