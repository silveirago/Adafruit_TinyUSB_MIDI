#include <Adafruit_TinyUSB_MIDI.h>

// Global instance for MIDI Input
Adafruit_TinyUSB_MIDI_Input MIDI_Input(MIDI.getMidiInstance());

bool ledState = false;  // Variable to keep track of LED state

void setup() {
  // Start Serial communication for debugging
  Serial.begin(115200);

  // Initialize the MIDI Output
  MIDI.begin();

  // Initialize the MIDI Input callbacks
  MIDI_Input.setHandleNoteOn(handleNoteOn);
  MIDI_Input.setHandleNoteOff(handleNoteOff);
  MIDI_Input.setHandleControlChange(handleControlChange);
  MIDI_Input.setHandleProgramChange(handleProgramChange);
  MIDI_Input.setHandlePitchBend(handlePitchBend);
  MIDI_Input.setHandleChannelPressure(handleChannelPressure);
  MIDI_Input.setHandleAfterTouch(handleAfterTouch);
  MIDI_Input.setHandlePolyPressure(handlePolyPressure);
  MIDI_Input.setHandleSysEx(handleSysEx);
  MIDI_Input.setHandleTimeCodeQuarterFrame(handleTimeCodeQuarterFrame);
  MIDI_Input.setHandleSongPosition(handleSongPosition);
  MIDI_Input.setHandleSongSelect(handleSongSelect);
  MIDI_Input.setHandleTuneRequest(handleTuneRequest);
  MIDI_Input.setHandleRealTime(handleRealTime);

  // Set LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  // Ensure LED is off initially
}

void loop() {
  // Process incoming MIDI messages
  MIDI_Input.read();
}

// Callback function for handling incoming Note On messages
void handleNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  Serial.print("Note On received. Channel: ");
  Serial.print(channel);
  Serial.print(", Note: ");
  Serial.print(note);
  Serial.print(", Velocity: ");
  Serial.println(velocity);

  // Toggle LED state
  toggleLED();
}

// Callback function for handling incoming Note Off messages
void handleNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  Serial.print("Note Off received. Channel: ");
  Serial.print(channel);
  Serial.print(", Note: ");
  Serial.print(note);
  Serial.print(", Velocity: ");
  Serial.println(velocity);

  // Toggle LED state
  toggleLED();
}

// Callback function for handling Control Change messages
void handleControlChange(uint8_t channel, uint8_t controlNumber, uint8_t controlValue) {
  Serial.print("Control Change received. Channel: ");
  Serial.print(channel);
  Serial.print(", Control Number: ");
  Serial.print(controlNumber);
  Serial.print(", Control Value: ");
  Serial.println(controlValue);

  // Toggle LED state or perform any action
  toggleLED();
}


// Callback function for handling Program Change messages
void handleProgramChange(uint8_t channel, uint8_t programNumber) {
  Serial.print("Program Change received. Channel: ");
  Serial.print(channel);
  Serial.print(", Program Number: ");
  Serial.println(programNumber);

  // Toggle LED state
  toggleLED();
}

// Callback function for handling Pitch Bend messages
void handlePitchBend(uint8_t channel, int16_t bendValue) {
  Serial.print("Pitch Bend received. Channel: ");
  Serial.print(channel);
  Serial.print(", Bend Value: ");
  Serial.println(bendValue);

  // Toggle LED state
  toggleLED();
}

// Callback function for handling Channel Pressure (Aftertouch) messages
void handleChannelPressure(uint8_t channel, uint8_t pressure) {
  Serial.print("Channel Pressure received. Channel: ");
  Serial.print(channel);
  Serial.print(", Pressure: ");
  Serial.println(pressure);

  // Toggle LED state
  toggleLED();
}

// Callback function for handling Polyphonic Key Pressure (Poly Aftertouch) messages
void handlePolyPressure(uint8_t channel, uint8_t note, uint8_t pressure) {
  Serial.print("Poly Pressure received. Channel: ");
  Serial.print(channel);
  Serial.print(", Note: ");
  Serial.print(note);
  Serial.print(", Pressure: ");
  Serial.println(pressure);

  // Toggle LED state
  toggleLED();
}

// Callback function for handling Aftertouch messages
void handleAfterTouch(uint8_t channel, uint8_t note, uint8_t pressure) {
  Serial.print("Aftertouch received. Channel: ");
  Serial.print(channel);
  Serial.print(", Note: ");
  Serial.print(note);
  Serial.print(", Pressure: ");
  Serial.println(pressure);

  // Toggle LED state
  toggleLED();
}


// Callback function for handling System Exclusive (SysEx) messages
void handleSysEx(size_t length, uint8_t *data) {
  Serial.print("SysEx message received. Length: ");
  Serial.println(length);
  Serial.print("Data: ");
  for (size_t i = 0; i < length; i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Toggle LED state
  toggleLED();
}

// Callback function for handling Time Code Quarter Frame messages
void handleTimeCodeQuarterFrame(uint8_t typeNibble, uint8_t valuesNibble) {
  Serial.print("Time Code Quarter Frame received. Type: ");
  Serial.print(typeNibble);
  Serial.print(", Value: ");
  Serial.println(valuesNibble);

  // Toggle LED state
  toggleLED();
}

// Callback function for handling Song Position Pointer messages
void handleSongPosition(uint16_t beats) {
  Serial.print("Song Position received. Beats: ");
  Serial.println(beats);

  // Toggle LED state
  toggleLED();
}

// Callback function for handling Song Select messages
void handleSongSelect(uint8_t songNumber) {
  Serial.print("Song Select received. Song Number: ");
  Serial.println(songNumber);

  // Toggle LED state
  toggleLED();
}

// Callback function for handling Tune Request messages
void handleTuneRequest() {
  Serial.println("Tune Request received.");

  // Toggle LED state
  toggleLED();
}

// Callback function for handling System Real-Time messages (e.g., Clock, Start, Stop)
void handleRealTime(uint8_t realTimeType) {
  Serial.print("Real Time message received. Type: ");
  Serial.println(realTimeType, HEX);

  // Toggle LED state
  toggleLED();
}

// Function to toggle the built-in LED state
void toggleLED() {
  ledState = !ledState;                              // Toggle LED state
  digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);  // Set LED
}
