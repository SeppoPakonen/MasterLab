#include "MIDI.h"
namespace am {

MidiFilterConfig::MidiFilterConfig() {
	// Initialize with default filter settings
	// Enable all channels by default (bits 0-15)
	prefs.channels.SetCount(16, true);  // 16 channels, all enabled by default
	prefs.record.SetCount(16, true);    // 16 channels, all enabled by default
	prefs.thru.SetCount(16, true);      // 16 channels, all enabled by default
}

void MidiFilterConfig::SetPrefs(const MidiFilterPrefs& newPrefs) {
	prefs.record = pick(newPrefs.record);
	prefs.thru = pick(newPrefs.thru);
	prefs.channels = pick(newPrefs.channels);
	prefs.controllerBlockList = pick(newPrefs.controllerBlockList);
}

bool MidiFilterConfig::ShouldFilter(int channel, int eventType) const {
	// Check if the specific channel is enabled
	if (!IsChannelEnabled(channel)) {
		return true; // Filter if channel is disabled
	}
	
	// Check record/thru filters if applicable
	// eventType would indicate if this is for record or thru
	
	return false; // For now, don't filter by default
}

bool MidiFilterConfig::IsControllerBlocked(int controllerNum) const {
	for (int blocked : prefs.controllerBlockList) {
		if (blocked == controllerNum) {
			return true;
		}
	}
	return false;
}

bool MidiFilterConfig::IsChannelEnabled(int channel) const {
	// Channel is 1-16, but BitSet is 0-15
	if (channel < 1 || channel > 16) {
		return false;
	}
	return prefs.channels[channel - 1];
}

}