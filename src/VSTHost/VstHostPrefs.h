#ifndef _VSTHost_VstHostPrefs_h_
#define _VSTHost_VstHostPrefs_h_

#include <Devices/Devices.h>
#include <AudioFX/AudioFX.h>
#include <AudioCore/AudioCore.h>
using namespace Upp;

namespace am {

enum class StereoPannerType {
	Dual,
	Combined,
	Balance
};

enum class AutoMonType {
	Manual,
	WhileRecordEnabled,
	WhileRecordRunning,
	TapeMachine
};

struct VstGlobalPrefs {
	// Core
	bool autoConnectSends = true;
	bool vstiCreateMidiTrack = true;
	bool suspendWhenSilent = true;
	bool sortByVendor = true;
	bool warnRemoveModified = true;
	bool openEditorAfterLoad = true;
	bool alwaysOnTop = false;
	bool warnOverloads = true;
	StereoPannerType defaultPanner = StereoPannerType::Dual;
	bool linkSendRoutingPanners = true;
	AutoMonType autoMon = AutoMonType::Manual;
	double delayCompThresholdMs = 10.0;
	bool exportWarningsAsText = false;
};

struct MeteringPrefs {
	int peakHoldMs = 5000;
	int slowFallbackDbps = 10;
	int fastFallbackDbps = 100;
	bool mapInputBusToTrackInDirectMon = true;
};

struct ControlRoomPrefs {
	bool showVolumeInTransport = true;
	bool disableTalkbackDuringRecord = false;
	bool phonesAsPreview = false;
	bool dimStudioDuringTalkback = false;
	bool signalPresence = false;
	bool multiChanSolo = false;
	bool showDownmix = false;
	bool metronomeInStudio = false;
	bool metronomeInControlRoom = false;
	bool showReferenceLevel = false;
	double referenceLevelDb = -18.0;
	double maxDimDb = 20.0;
};

class VstHostPrefsManager {
public:
	VstHostPrefsManager();
	
	// Get preferences
	const VstGlobalPrefs& GetGlobalPrefs() const { return globalPrefs; }
	const MeteringPrefs& GetMeteringPrefs() const { return meteringPrefs; }
	const ControlRoomPrefs& GetControlRoomPrefs() const { return controlRoomPrefs; }
	
	// Set preferences
	void SetGlobalPrefs(const VstGlobalPrefs& prefs);
	void SetMeteringPrefs(const MeteringPrefs& prefs);
	void SetControlRoomPrefs(const ControlRoomPrefs& prefs);
	
	// Apply preferences to VST host system
	void ApplyToVstHost(class PluginManager& pluginManager);
	
private:
	VstGlobalPrefs globalPrefs;
	MeteringPrefs meteringPrefs;
	ControlRoomPrefs controlRoomPrefs;
};

}

#endif