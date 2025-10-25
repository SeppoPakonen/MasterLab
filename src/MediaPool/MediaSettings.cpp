#include "MediaPool.h"
namespace am {

MediaSettings::MediaSettings() {
	// Initialize with default preferences
	viewer_prefs.maxResults = 100000;
	viewer_prefs.allowEdit = false;
	viewer_prefs.stopScanOnClose = true;
	viewer_prefs.showExtensions = false;
}

void MediaSettings::SetViewerPrefs(const MediaViewerPrefs& prefs) {
	viewer_prefs = prefs;
}

void MediaSettings::ApplyToMediaPool(class MediaPool& pool) {
	// Apply the settings to the media pool
	// This is a stub - would connect to actual media pool functionality
	LOG("Applying media settings to media pool");
}

}