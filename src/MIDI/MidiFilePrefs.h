#ifndef _MIDI_MidiFilePrefs_h_
#define _MIDI_MidiFilePrefs_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct MidiFileExportPrefs {
	bool inspectorPatch = false;
	bool inspectorVolumePan = false;
	bool exportAutomation = false;
	bool exportInserts = true;
	bool exportSends = false;
	bool exportMarkers = true;
	bool exportAsType0 = false;
	bool exportLocatorRange = false;
	bool exportIncludesDelay = false;
	int exportResolution = 480;  // PPQ resolution
};

struct MidiFileImportPrefs {
	bool extractFirstPatch = false;
	bool extractFirstVolumePan = false;
	bool importControllersAsAutomation = false;
	bool importToLeftLocator = false;
	bool importMarkers = true;
	bool importAsSinglePart = false;
	bool ignoreMasterTrackEvents = true;
	bool autoDissolveFormat0 = true;
	bool importToInstrumentTracks = true;
};

class MidiFilePrefs {
public:
	MidiFilePrefs();
	
	// Export preferences
	const MidiFileExportPrefs& GetExportPrefs() const { return exportPrefs; }
	void SetExportPrefs(const MidiFileExportPrefs& prefs);
	
	// Import preferences
	const MidiFileImportPrefs& GetImportPrefs() const { return importPrefs; }
	void SetImportPrefs(const MidiFileImportPrefs& prefs);
	
private:
	MidiFileExportPrefs exportPrefs;
	MidiFileImportPrefs importPrefs;
};

}

#endif