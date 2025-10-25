#include "AudioEditing.h"
#include <Editors/Editors.h>
namespace am {

SnapSettingsManager::SnapSettingsManager() {
	// Initialize with default snap settings
	settings.snapToZeroCrossing = false;
	settings.snapToGrid = true;
	settings.snapToEvents = true;
	settings.snapToMarkers = true;
	settings.snapToLoop = true;
	settings.snapTolerance = 100;
}

void SnapSettingsManager::SetSettings(const SnapSettings& newSettings) {
	settings = newSettings;
}

void SnapSettingsManager::ApplyToEditor(class KeyEditor& editor) {
	LOG("Applying snap settings to Key Editor");
}

void SnapSettingsManager::ApplyToEditor(class DrumEditor& editor) {
	LOG("Applying snap settings to Drum Editor");
}

void SnapSettingsManager::ApplyToEditor(class ListEditor& editor) {
	LOG("Applying snap settings to List Editor");
}

}