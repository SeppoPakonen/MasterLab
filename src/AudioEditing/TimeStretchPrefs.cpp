#include "AudioEditing.h"
namespace am {

TimeStretchPrefsManager::TimeStretchPrefsManager() {
	// Initialize with default time stretch preferences
	prefs.algorithm = StretchAlgo::MPEX4;
	prefs.treatMutedAsDeleted = true;
	prefs.wheelAdjustsVolAndFades = false;
	prefs.hitpointsHaveQPoints = false;
	prefs.snapZero = false;
}

void TimeStretchPrefsManager::SetPrefs(const TimeStretchPrefs& newPrefs) {
	prefs = newPrefs;
}

void TimeStretchPrefsManager::ApplyToStretch(class AudioOps& ops) {
	LOG("Applying time stretch preferences");
	LOG("Algorithm: " << (prefs.algorithm == StretchAlgo::MPEX4 ? "MPEX4" : "Realtime"));
	LOG("Treat muted as deleted: " << (prefs.treatMutedAsDeleted ? "yes" : "no"));
	LOG("Wheel adjusts vol/fades: " << (prefs.wheelAdjustsVolAndFades ? "yes" : "no"));
	LOG("Hitpoints have Q-points: " << (prefs.hitpointsHaveQPoints ? "yes" : "no"));
	LOG("Snap to zero crossing: " << (prefs.snapZero ? "yes" : "no"));
}

}