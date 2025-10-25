#include "MIDI.h"
namespace am {

MidiFilePrefs::MidiFilePrefs() {
	// Initialize export preferences with defaults
	exportPrefs.inspectorPatch = false;
	exportPrefs.inspectorVolumePan = false;
	exportPrefs.exportAutomation = false;
	exportPrefs.exportInserts = true;
	exportPrefs.exportSends = false;
	exportPrefs.exportMarkers = true;
	exportPrefs.exportAsType0 = false;
	exportPrefs.exportLocatorRange = false;
	exportPrefs.exportIncludesDelay = false;
	exportPrefs.exportResolution = 480;
	
	// Initialize import preferences with defaults
	importPrefs.extractFirstPatch = false;
	importPrefs.extractFirstVolumePan = false;
	importPrefs.importControllersAsAutomation = false;
	importPrefs.importToLeftLocator = false;
	importPrefs.importMarkers = true;
	importPrefs.importAsSinglePart = false;
	importPrefs.ignoreMasterTrackEvents = true;
	importPrefs.autoDissolveFormat0 = true;
	importPrefs.importToInstrumentTracks = true;
}

void MidiFilePrefs::SetExportPrefs(const MidiFileExportPrefs& prefs) {
	exportPrefs = prefs;
}

void MidiFilePrefs::SetImportPrefs(const MidiFileImportPrefs& prefs) {
	importPrefs = prefs;
}

}