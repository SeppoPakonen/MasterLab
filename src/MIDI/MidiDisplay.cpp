#include "MIDI.h"
namespace am {

MidiDisplay::MidiDisplay() {
	// Initialize with default display preferences
	prefs.names = NoteNameStyle::MIDI;
	prefs.showControllers = true;
	prefs.editAsDrumsIfMapped = true;
}

void MidiDisplay::SetPrefs(const MidiDisplayPrefs& newPrefs) {
	prefs = newPrefs;
}

String MidiDisplay::GetNoteName(int noteNum) const {
	return FormatNoteName(noteNum, prefs.names);
}

String MidiDisplay::FormatNoteName(int noteNum, NoteNameStyle style) const {
	// Calculate note and octave
	int octave = noteNum / 12 - 1;  // MIDI standard: C4 is 60
	int noteInOctave = noteNum % 12;
	
	static const char* notesMIDI[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	static const char* notesClassic[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
	static const char* notesClassicGerman[] = {"C", "C#", "D", "D#", "D", "F", "F#", "G", "G#", "A", "A#", "H"}; // B is H in German
	
	String noteStr;
	switch (style) {
		case NoteNameStyle::MIDI:
		case NoteNameStyle::MIDIValue:
			noteStr = notesMIDI[noteInOctave];
			break;
		case NoteNameStyle::Classic:
			noteStr = notesClassic[noteInOctave];
			break;
		case NoteNameStyle::ClassicGerman:
			noteStr = notesClassicGerman[noteInOctave];
			break;
	}
	
	return noteStr + AsString(octave);
}

}