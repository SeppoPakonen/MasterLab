#ifndef _AudioEditing_TimeStretchPrefs_h_
#define _AudioEditing_TimeStretchPrefs_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

enum class StretchAlgo {
	MPEX4,
	Realtime
};

struct TimeStretchPrefs {
	StretchAlgo algorithm = StretchAlgo::MPEX4;
	bool treatMutedAsDeleted = true;
	bool wheelAdjustsVolAndFades = false;
	bool hitpointsHaveQPoints = false;
	bool snapZero = false;
};

class TimeStretchPrefsManager {
public:
	TimeStretchPrefsManager();
	
	const TimeStretchPrefs& GetPrefs() const { return prefs; }
	void SetPrefs(const TimeStretchPrefs& newPrefs);
	
	// Apply stretch preferences to audio processing
	void ApplyToStretch(class AudioOps& ops);
	
private:
	TimeStretchPrefs prefs;
};

}

#endif