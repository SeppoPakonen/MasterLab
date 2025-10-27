#include "MIDI.h"
namespace am {

MidiChase::MidiChase() {
	// Initialize with default chase preferences
	prefs.note = true;
	prefs.polyPressure = true;
	prefs.controller = true;
	prefs.progChange = true;
	prefs.aftertouch = true;
	prefs.pitchbend = true;
	prefs.sysex = false;
	prefs.ignorePartBounds = true;
}

void MidiChase::SetPrefs(const MidiChasePrefs& newPrefs) {
	prefs = newPrefs;
}

void MidiChase::ApplyChaseEvents() {
	LOG("Applying MIDI chase events");
	LOG("Note: " << (prefs.note ? "enabled" : "disabled"));
	LOG("Poly Pressure: " << (prefs.polyPressure ? "enabled" : "disabled"));
	LOG("Controller: " << (prefs.controller ? "enabled" : "disabled"));
	LOG("Program Change: " << (prefs.progChange ? "enabled" : "disabled"));
	LOG("Aftertouch: " << (prefs.aftertouch ? "enabled" : "disabled"));
	LOG("Pitchbend: " << (prefs.pitchbend ? "enabled" : "disabled"));
	LOG("SysEx: " << (prefs.sysex ? "enabled" : "disabled"));
	LOG("Ignore part bounds: " << (prefs.ignorePartBounds ? "yes" : "no"));
}

}