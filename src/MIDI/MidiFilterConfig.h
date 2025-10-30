#ifndef _MIDI_MidiFilterConfig_h_
#define _MIDI_MidiFilterConfig_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct MidiFilterPrefs : public Moveable<MidiFilterPrefs> {
	Upp::Vector<bool> record;        // Record filter - 0-15 for MIDI channels
	Upp::Vector<bool> thru;          // Thru filter - 0-15 for MIDI channels
	Upp::Vector<bool> channels;      // Channels 1-16 (bit 0-15)
	Upp::Vector<int> controllerBlockList;  // Blocked controller numbers
};

class MidiFilterConfig {
public:
	MidiFilterConfig();
	
	const MidiFilterPrefs& GetPrefs() const { return prefs; }
	void SetPrefs(const MidiFilterPrefs& newPrefs);
	
	// Check if MIDI message should be filtered
	bool ShouldFilter(int channel, int eventType) const;
	
	// Check if controller should be blocked
	bool IsControllerBlocked(int controllerNum) const;
	
	// Channel operations
	bool IsChannelEnabled(int channel) const; // Channel 1-16
	
private:
	MidiFilterPrefs prefs;
};

}

#endif