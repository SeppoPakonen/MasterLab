#include "Video.h"  // The main video package header
namespace am {

VideoPrefsManager::VideoPrefsManager() {
	// Initialize with default video preferences
	prefs.extractAudioOnImport = true;
	prefs.generateThumbnailsOnImport = true;
	prefs.thumbnailCacheSizeMB = 3;
	prefs.showThumbnailsInEvents = true;
}

void VideoPrefsManager::SetPrefs(const VideoPrefs& newPrefs) {
	prefs = newPrefs;
}

void VideoPrefsManager::ApplyToVideoProcessing() {
	LOG("Applying video preferences");
	LOG("Extract audio on import: " << (prefs.extractAudioOnImport ? "yes" : "no"));
	LOG("Generate thumbnails on import: " << (prefs.generateThumbnailsOnImport ? "yes" : "no"));
	LOG("Thumbnail cache size: " + IntStr(prefs.thumbnailCacheSizeMB) + " MB");
	LOG("Show thumbnails in events: " << (prefs.showThumbnailsInEvents ? "yes" : "no"));
}

}