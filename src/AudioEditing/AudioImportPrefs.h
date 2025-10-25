#ifndef _AudioEditing_AudioImportPrefs_h_
#define _AudioEditing_AudioImportPrefs_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

enum class AudioImportMode {
	OpenOptions,
	UseSettings
};

struct AudioImportPrefs {
	AudioImportMode mode = AudioImportMode::OpenOptions;
	bool copyToWorking = false;
	bool convertIfNeeded = false;
	bool splitMultichannel = false;
	
	enum class VersioningMode {
		Ask,
		AssumeNewVersions,
		AssumeSkipping
	} versionHandling = VersioningMode::Ask;
};

class AudioImportPrefsManager {
public:
	AudioImportPrefsManager();
	
	const AudioImportPrefs& GetPrefs() const { return prefs; }
	void SetPrefs(const AudioImportPrefs& newPrefs);
	
	// Apply import preferences to audio processing
	void ApplyToImport(class Importer& importer);
	
private:
	AudioImportPrefs prefs;
};

}

#endif