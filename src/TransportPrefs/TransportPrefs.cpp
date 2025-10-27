#include "TransportPrefs.h"
namespace am {

TransportPrefsManager::TransportPrefsManager() {
	// Initialize with default transport preferences
	behavior.playbackTogglePreview = false;
	behavior.zoomWhileLocating = false;
	behavior.cursorWidth = 3;
	behavior.returnToStartOnStop = false;
	behavior.deactivatePunchInOnStop = false;
	behavior.stopAfterAutoPunchOut = false;
	behavior.stopWhileWinding = false;
	behavior.stationaryCursor = false;
	behavior.locateOnEmptyClick = false;
	
	// Set default wind options
	behavior.windOptions.mode = WindOptions::AdjustToZoom;
	behavior.windOptions.speedFactor = 1;
	behavior.windOptions.fastFactor = 10;
	
	// Set default scrub preferences
	behavior.scrubPrefs.response = 50;
	behavior.scrubPrefs.volume = 50;
	behavior.scrubPrefs.cpuSaving = false;
	
	// Set default timecode preferences
	behavior.timecodePrefs.showSubframes = false;
	behavior.timecodePrefs.userFramerate = 30;
	behavior.timecodePrefs.cursorWidth = 3;
}

void TransportPrefsManager::SetTransportBehavior(const TransportBehavior& newBehavior) {
	behavior = newBehavior;
}

void TransportPrefsManager::ApplyToTransport(class Transport& transport) {
	LOG("Applying transport preferences");
	LOG("Return to start on stop: " << (behavior.returnToStartOnStop ? "yes" : "no"));
	LOG("Deactivate punch in on stop: " << (behavior.deactivatePunchInOnStop ? "yes" : "no"));
	LOG("Stop after auto punch out: " << (behavior.stopAfterAutoPunchOut ? "yes" : "no"));
	LOG("Stop while winding: " << (behavior.stopWhileWinding ? "yes" : "no"));
	LOG("Stationary cursor: " << (behavior.stationaryCursor ? "yes" : "no"));
	LOG("Locate on empty click: " << (behavior.locateOnEmptyClick ? "yes" : "no"));
	LOG("Zoom while locating: " << (behavior.zoomWhileLocating ? "yes" : "no"));
	LOG("Playback toggle preview: " << (behavior.playbackTogglePreview ? "yes" : "no"));
	LOG("User framerate: " + IntStr(behavior.timecodePrefs.userFramerate));
	LOG("Cursor width: " + IntStr(behavior.cursorWidth));
	LOG("Scrub response: " + IntStr(behavior.scrubPrefs.response));
	LOG("Scrub volume: " + IntStr(behavior.scrubPrefs.volume));
	LOG("Scrub CPU saving: " << (behavior.scrubPrefs.cpuSaving ? "yes" : "no"));
	LOG("Show subframes: " << (behavior.timecodePrefs.showSubframes ? "yes" : "no"));
}

}