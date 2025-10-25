#ifndef _AudioEditing_SnapSettings_h_
#define _AudioEditing_SnapSettings_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct SnapSettings {
	bool snapToZeroCrossing = false;
	bool snapToGrid = true;
	bool snapToEvents = true;
	bool snapToMarkers = true;
	bool snapToLoop = true;
	
	// Tolerance in samples
	int snapTolerance = 100;
};

class SnapSettingsManager {
public:
	SnapSettingsManager();
	
	const SnapSettings& GetSettings() const { return settings; }
	void SetSettings(const SnapSettings& newSettings);
	
	// Apply snap settings to editing operations
	void ApplyToEditor(class KeyEditor& editor);
	void ApplyToEditor(class DrumEditor& editor);
	void ApplyToEditor(class ListEditor& editor);
	
private:
	SnapSettings settings;
};

}

#endif