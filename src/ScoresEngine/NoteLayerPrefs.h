#ifndef _ScoresEngine_NoteLayerPrefs_h_
#define _ScoresEngine_NoteLayerPrefs_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct NoteLayerPrefs {
	// Visibility/weight settings for different notation elements
	int braces = 100;                    // 0-100 visibility/weight
	int barNumbers = 100;
	int staffNames = 100;
	int stems = 100;
	int keys = 100;
	int clefs = 100;
	int barLines = 100;
	int staves = 100;
	int noteSymbols = 100;
	int graphics = 100;
	int slurs = 100;
	int notes = 100;
	int rests = 100;
	int timeSignatures = 100;
};

class NoteLayerPrefsManager {
public:
	NoteLayerPrefsManager();
	
	const NoteLayerPrefs& GetPrefs() const { return prefs; }
	void SetPrefs(const NoteLayerPrefs& newPrefs);
	
	// Apply preferences to notation display
	void ApplyToNotationDisplay();
	
private:
	NoteLayerPrefs prefs;
};

}

#endif