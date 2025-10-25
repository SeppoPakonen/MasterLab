#ifndef _Video_VideoPrefs_h_
#define _Video_VideoPrefs_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct VideoPrefs {
	bool extractAudioOnImport = true;
	bool generateThumbnailsOnImport = true;
	int thumbnailCacheSizeMB = 3;  // Default cache size
	bool showThumbnailsInEvents = true;
};

class VideoPrefsManager {
public:
	VideoPrefsManager();
	
	const VideoPrefs& GetPrefs() const { return prefs; }
	void SetPrefs(const VideoPrefs& newPrefs);
	
	// Apply preferences to video processing
	void ApplyToVideoProcessing();
	
private:
	VideoPrefs prefs;
};

}

#endif