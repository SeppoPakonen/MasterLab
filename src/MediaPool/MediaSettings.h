#ifndef _MediaPool_MediaSettings_h_
#define _MediaPool_MediaSettings_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct MediaViewerPrefs {
	int maxResults = 100000;
	bool allowEdit = false;
	bool stopScanOnClose = true;
	bool showExtensions = false;
};

class MediaSettings {
public:
	MediaSettings();
	
	// Viewer preferences
	const MediaViewerPrefs& GetViewerPrefs() const { return viewer_prefs; }
	void SetViewerPrefs(const MediaViewerPrefs& prefs);
	
	// Apply settings to the media pool
	void ApplyToMediaPool(class MediaPool& pool);
	
private:
	MediaViewerPrefs viewer_prefs;
};

}

#endif