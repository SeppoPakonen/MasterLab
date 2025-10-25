#ifndef _TransportPrefs_TransportPrefs_h_
#define _TransportPrefs_TransportPrefs_h_

#include <AudioCore/AudioCore.h>
using namespace Upp;

namespace am {

struct ScrubPrefs {
	int response = 50;    // 0-100
	int volume = 50;      // 0-100
	bool cpuSaving = false;
};

struct TimecodePrefs {
	bool showSubframes = false;
	int userFramerate = 30;
	int cursorWidth = 3;
};

struct WindOptions {
	enum Mode { AdjustToZoom, Fixed };
	Mode mode = AdjustToZoom;
	int speedFactor = 1;
	int fastFactor = 10;
};

struct TransportBehavior {
	bool playbackTogglePreview = false;
	bool zoomWhileLocating = false;
	int cursorWidth = 3;
	bool returnToStartOnStop = false;
	bool deactivatePunchInOnStop = false;
	bool stopAfterAutoPunchOut = false;
	bool stopWhileWinding = false;
	bool stationaryCursor = false;
	bool locateOnEmptyClick = false;
	
	WindOptions windOptions;
	ScrubPrefs scrubPrefs;
	TimecodePrefs timecodePrefs;
};

class TransportPrefsManager {
public:
	TransportPrefsManager();
	
	const TransportBehavior& GetTransportBehavior() const { return behavior; }
	void SetTransportBehavior(const TransportBehavior& newBehavior);
	
	// Apply preferences to transport system
	void ApplyToTransport(class Transport& transport);
	
private:
	TransportBehavior behavior;
};

}

#endif