#include "AudioEditing.h"
#include <FileIO/Import.h>  // For Importer class
namespace am {

AudioImportPrefsManager::AudioImportPrefsManager() {
	// Initialize with default import preferences
	prefs.mode = AudioImportMode::OpenOptions;
	prefs.copyToWorking = false;
	prefs.convertIfNeeded = false;
	prefs.splitMultichannel = false;
	prefs.versionHandling = AudioImportPrefs::VersioningMode::Ask;
}

void AudioImportPrefsManager::SetPrefs(const AudioImportPrefs& newPrefs) {
	prefs = newPrefs;
}

void AudioImportPrefsManager::ApplyToImport(class Importer& importer) {
	LOG("Applying audio import preferences");
	LOG("Mode: " + Upp::String(prefs.mode == AudioImportMode::OpenOptions ? "Open Options" : "Use Settings"));
	LOG("Copy to working: " + Upp::String(prefs.copyToWorking ? "yes" : "no"));
	LOG("Convert if needed: " + Upp::String(prefs.convertIfNeeded ? "yes" : "no"));
	LOG("Split multichannel: " + Upp::String(prefs.splitMultichannel ? "yes" : "no"));
	LOG("Version handling: ask");
}

}