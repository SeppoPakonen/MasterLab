#ifndef _MIDI_MidiChase_h_
#define _MIDI_MidiChase_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct MidiChasePrefs {
	bool note = true;
	bool polyPressure = true;
	bool controller = true;
	bool progChange = true;
	bool aftertouch = true;
	bool pitchbend = true;
	bool sysex = false;
	bool ignorePartBounds = true;
};

class MidiChase {
public:
	MidiChase();
	
	const MidiChasePrefs& GetPrefs() const { return prefs; }
	void SetPrefs(const MidiChasePrefs& newPrefs);
	
	// Apply chase events based on preferences
	void ApplyChaseEvents();
	
private:
	MidiChasePrefs prefs;
};

}

#endif