#ifndef _TransportPrefs_TransportPrefs_h_
#define _TransportPrefs_TransportPrefs_h_

#include <AudioCore/AudioCore.h>
using namespace Upp;

namespace am {

// Import the definitions from AudioCore to avoid redefinition
using ::am::ScrubPrefs;
using ::am::TimecodePrefs;
using ::am::WindOptions;

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