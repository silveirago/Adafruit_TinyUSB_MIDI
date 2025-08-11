# Manual Test Checklist

This checklist covers flashing the examples from the `Adafruit_TinyUSB_MIDI` library to Arduino UNO R4 Minima, UNO R4 WiFi, and Nano R4 boards, and verifying USB MIDI functionality.

## Prerequisites
- Arduino IDE 2.x or Arduino CLI.
- `Adafruit TinyUSB MIDI` library installed.
- USB-C cable for each board.
- A host computer with a MIDI monitor or DAW (e.g. MIDI-OX on Windows, `aseqdump`/`amidi` on Linux, or "MIDI Monitor" on macOS).

## Flashing Examples
1. Connect the board to your computer via USB.
2. In the Arduino IDE:
   - Select **Board**: "Arduino UNO R4 Minima", "Arduino UNO R4 WiFi", or "Arduino Nano R4".
   - Open **File → Examples → Adafruit TinyUSB MIDI → MIDI_write** (for transmit) or **MIDI_read** (for receive).
   - Compile and upload the sketch.
3. After upload, the board should reset and enumerate as a USB MIDI device.

## Expected USB VID/PID
- **UNO R4 Minima**: VID `0x2341`, PID `0x0061`
- **UNO R4 WiFi**: VID `0x2341`, PID `0x0062`
- **Nano R4**: VID `0x2341`, PID `0x0063`

Verify enumeration:
- **Linux**: `lsusb | grep 2341`
- **macOS**: `system_profiler SPUSBDataType | grep 2341`
- **Windows**: Device Manager → Sound, video and game controllers

## Checking MIDI Messages
### From Board to Host
1. Upload the **MIDI_write** example.
2. Open your MIDI monitor/DAW and select the board as the MIDI input.
3. The example sends Note On/Off messages on channel 0 every second. Confirm messages appear in the monitor/DAW.

### From Host to Board
1. Upload the **MIDI_read** example.
2. In your MIDI monitor/DAW, select the board as the MIDI output.
3. Send a Note On/Off message. The sketch prints the message to Serial and toggles the built-in LED. Confirm both actions occur.

## Bidirectional Communication Test
1. Upload the **MIDI_read** example.
2. Open two sessions in your MIDI monitor/DAW: one for output to the board and one for input from the board.
3. Send a Note On message from the host to the board and observe the LED and serial output.
4. Modify the sketch to echo received messages back using `MidiUSB.sendMIDI()` or use a combined read/write sketch.
5. Confirm that messages sent from the host are echoed back and appear in the monitor, verifying two-way communication.

Repeat all steps for UNO R4 Minima, UNO R4 WiFi, and Nano R4 boards to ensure consistent behavior.

