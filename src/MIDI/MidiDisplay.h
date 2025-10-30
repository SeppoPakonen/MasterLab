#ifndef _MIDI_MidiDisplay_h_
#define _MIDI_MidiDisplay_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

enum class NoteNameStyle {
	MIDI,              // C4, C#4, etc.
	MIDIValue,         // DoReMi
	Classic,           // C, C#, etc.
	ClassicGerman      // H instead of B
};

struct MidiDisplayPrefs {
	NoteNameStyle names = NoteNameStyle::MIDI;
	bool showControllers = true;
	bool editAsDrumsIfMapped = true;
};

class MidiDisplay {
public:
	MidiDisplay();
	
	const MidiDisplayPrefs& GetPrefs() const { return prefs; }
	void SetPrefs(const MidiDisplayPrefs& newPrefs);
	
	// Get note name based on current style
	Upp::String GetNoteName(int noteNum) const;
	
private:
	MidiDisplayPrefs prefs;
	
	// Helper to format note name based on style
	Upp::String FormatNoteName(int noteNum, NoteNameStyle style) const;
};

}

#endif