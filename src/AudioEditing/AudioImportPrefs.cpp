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
	LOG("Mode: " + (prefs.mode == AudioImportMode::OpenOptions ? "Open Options" : "Use Settings"));
	LOG("Copy to working: " + (prefs.copyToWorking ? "yes" : "no"));
	LOG("Convert if needed: " + (prefs.convertIfNeeded ? "yes" : "no"));
	LOG("Split multichannel: " + (prefs.splitMultichannel ? "yes" : "no"));
	LOG("Version handling: ask");
}

}