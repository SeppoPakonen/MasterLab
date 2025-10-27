#ifndef _Theme_WorkAreaTheme_h_
#define _Theme_WorkAreaTheme_h_

#include <Draw/Draw.h>
using namespace Upp;

namespace am {

struct WorkAreaTheme {
	Color bg = White();
	Color gridH = LtGray();      // Horizontal grid
	Color gridV1 = LtGray();     // Vertical grid level 1
	Color gridV2 = Gray();       // Vertical grid level 2
	Color gridV3 = LtGray();     // Vertical grid level 3
	double cycleIntensity = 0.5; // Intensity of cycle region
	
	// Project window specific
	double workAreaBrightness = 0.5;
	
	// Edit window specific
	// (Same grid colors apply)
	
	// Key editor specific
	double blackNoteGridIntensity = 0.5;
	
	// Drum editor specific
	double activeDrumLaneIntensity = 0.5;
};

class ThemeManager {
public:
	ThemeManager();
	
	// Work area theme methods
	const WorkAreaTheme& GetWorkArea() const { return work_area_theme; }
	void SetWorkArea(const WorkAreaTheme& theme);
	
	// Signal when theme changes
	Event<> WhenChanged;
	
	// Apply theme to various UI elements
	void ApplyTo(class MainWindow& window);
	void ApplyTo(class KeyEditor& editor);
	void ApplyTo(class DrumEditor& editor);
	void ApplyTo(class ScoreEditor& editor);
	void ApplyTo(class ListEditor& editor);
	void ApplyTo(class InPlaceEditor& editor);
	
private:
	WorkAreaTheme work_area_theme;
};

}

#endif