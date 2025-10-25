#include "VstHostPrefs.h"
namespace am {

VstHostPrefsManager::VstHostPrefsManager() {
	// Initialize with default VST host preferences
	
	// Global preferences
	globalPrefs.autoConnectSends = true;
	globalPrefs.vstiCreateMidiTrack = true;
	globalPrefs.suspendWhenSilent = true;
	globalPrefs.sortByVendor = true;
	globalPrefs.warnRemoveModified = true;
	globalPrefs.openEditorAfterLoad = true;
	globalPrefs.alwaysOnTop = false;
	globalPrefs.warnOverloads = true;
	globalPrefs.defaultPanner = StereoPannerType::Dual;
	globalPrefs.linkSendRoutingPanners = true;
	globalPrefs.autoMon = AutoMonType::Manual;
	globalPrefs.delayCompThresholdMs = 10.0;
	globalPrefs.exportWarningsAsText = false;
	
	// Metering preferences
	meteringPrefs.peakHoldMs = 5000;
	meteringPrefs.slowFallbackDbps = 10;
	meteringPrefs.fastFallbackDbps = 100;
	meteringPrefs.mapInputBusToTrackInDirectMon = true;
	
	// Control room preferences
	controlRoomPrefs.showVolumeInTransport = true;
	controlRoomPrefs.disableTalkbackDuringRecord = false;
	controlRoomPrefs.phonesAsPreview = false;
	controlRoomPrefs.dimStudioDuringTalkback = false;
	controlRoomPrefs.signalPresence = false;
	controlRoomPrefs.multiChanSolo = false;
	controlRoomPrefs.showDownmix = false;
	controlRoomPrefs.metronomeInStudio = false;
	controlRoomPrefs.metronomeInControlRoom = false;
	controlRoomPrefs.showReferenceLevel = false;
	controlRoomPrefs.referenceLevelDb = -18.0;
	controlRoomPrefs.maxDimDb = 20.0;
}

void VstHostPrefsManager::SetGlobalPrefs(const VstGlobalPrefs& prefs) {
	globalPrefs = prefs;
}

void VstHostPrefsManager::SetMeteringPrefs(const MeteringPrefs& prefs) {
	meteringPrefs = prefs;
}

void VstHostPrefsManager::SetControlRoomPrefs(const ControlRoomPrefs& prefs) {
	controlRoomPrefs = prefs;
}

void VstHostPrefsManager::ApplyToVstHost(class PluginManager& pluginManager) {
	LOG("Applying VST host preferences");
	LOG("Auto connect sends: " + (globalPrefs.autoConnectSends ? "yes" : "no"));
	LOG("VSTi create MIDI track: " + (globalPrefs.vstiCreateMidiTrack ? "yes" : "no"));
	LOG("Suspend when silent: " + (globalPrefs.suspendWhenSilent ? "yes" : "no"));
	LOG("Sort by vendor: " + (globalPrefs.sortByVendor ? "yes" : "no"));
	LOG("Warn remove modified: " + (globalPrefs.warnRemoveModified ? "yes" : "no"));
	LOG("Open editor after load: " + (globalPrefs.openEditorAfterLoad ? "yes" : "no"));
	LOG("Always on top: " + (globalPrefs.alwaysOnTop ? "yes" : "no"));
	LOG("Warn overloads: " + (globalPrefs.warnOverloads ? "yes" : "no"));
	LOG("Delay comp threshold: " + DblStr(globalPrefs.delayCompThresholdMs) + " ms");
	LOG("Export warnings as text: " + (globalPrefs.exportWarningsAsText ? "yes" : "no"));
	
	String pannerStr;
	switch (globalPrefs.defaultPanner) {
		case StereoPannerType::Dual: pannerStr = "Dual"; break;
		case StereoPannerType::Combined: pannerStr = "Combined"; break;
		case StereoPannerType::Balance: pannerStr = "Balance"; break;
	}
	LOG("Default panner: " + pannerStr);
	LOG("Link send routing panners: " + (globalPrefs.linkSendRoutingPanners ? "yes" : "no"));
	
	String autoMonStr;
	switch (globalPrefs.autoMon) {
		case AutoMonType::Manual: autoMonStr = "Manual"; break;
		case AutoMonType::WhileRecordEnabled: autoMonStr = "While Record Enabled"; break;
		case AutoMonType::WhileRecordRunning: autoMonStr = "While Record Running"; break;
		case AutoMonType::TapeMachine: autoMonStr = "Tape Machine"; break;
	}
	LOG("Auto monitor: " + autoMonStr);
	
	LOG("Peak hold: " + IntStr(meteringPrefs.peakHoldMs) + " ms");
	LOG("Slow fallback: " + IntStr(meteringPrefs.slowFallbackDbps) + " dB/s");
	LOG("Fast fallback: " + IntStr(meteringPrefs.fastFallbackDbps) + " dB/s");
	LOG("Map input bus to track: " + (meteringPrefs.mapInputBusToTrackInDirectMon ? "yes" : "no"));
	LOG("Show volume in transport: " + (controlRoomPrefs.showVolumeInTransport ? "yes" : "no"));
	LOG("Disable talkback during record: " + (controlRoomPrefs.disableTalkbackDuringRecord ? "yes" : "no"));
	LOG("Phones as preview: " + (controlRoomPrefs.phonesAsPreview ? "yes" : "no"));
}

}