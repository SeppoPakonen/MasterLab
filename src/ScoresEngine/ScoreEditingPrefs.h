#ifndef _ScoresEngine_ScoreEditingPrefs_h_
#define _ScoresEngine_ScoreEditingPrefs_h_

#include <Core/Core.h>
using namespace Upp;

namespace am {

struct ScoreEditingPrefs {
	// Visual feedback
	bool displayArrowAfterInsert = true;
	bool dblClickSymbolPencil = true;
	bool keepCrescendoHorizontal = true;
	bool keepNotesWithinKey = true;
	bool treatNotesSingleUnits = true;
	
	// Layout behavior
	bool globalStaffSpacingsAltGr = true;
	bool autoLayoutDontHideFirst = true;
	bool showBracesInEdit = true;
	bool applyClosesPropWindows = true;
	
	// Cursor behavior
	bool showPositionCursor = true;
	bool animateNoteCursor = true;
	bool showNoteInfoOnMouse = true;
	
	// Editing behavior
	bool snapSlursOnDrag = true;
	bool unlockLayoutOnSinglePart = true;
	bool dblClickFlipStaff = true;
	bool compatMode = false;
	bool hideNotesBeyondLimits = true;
	
	// Layout settings
	int defaultBarsPerStaff = 4;
};

class ScoreEditingPrefsManager {
public:
	ScoreEditingPrefsManager();
	
	const ScoreEditingPrefs& GetPrefs() const { return prefs; }
	void SetPrefs(const ScoreEditingPrefs& newPrefs);
	
	// Apply preferences to score editors
	void ApplyToScoreEditor(class ScoreEditor& editor);
	
private:
	ScoreEditingPrefs prefs;
};

}

#endif