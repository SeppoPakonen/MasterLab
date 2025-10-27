#include "ScoresEngine.h"
#include <Editors/Editors.h>
namespace am {

ScoreEditingPrefsManager::ScoreEditingPrefsManager() {
	// Initialize with default score editing preferences
	prefs.displayArrowAfterInsert = true;
	prefs.dblClickSymbolPencil = true;
	prefs.keepCrescendoHorizontal = true;
	prefs.keepNotesWithinKey = true;
	prefs.treatNotesSingleUnits = true;
	prefs.globalStaffSpacingsAltGr = true;
	prefs.autoLayoutDontHideFirst = true;
	prefs.showBracesInEdit = true;
	prefs.applyClosesPropWindows = true;
	prefs.showPositionCursor = true;
	prefs.animateNoteCursor = true;
	prefs.showNoteInfoOnMouse = true;
	prefs.snapSlursOnDrag = true;
	prefs.unlockLayoutOnSinglePart = true;
	prefs.dblClickFlipStaff = true;
	prefs.compatMode = false;
	prefs.hideNotesBeyondLimits = true;
	prefs.defaultBarsPerStaff = 4;
}

void ScoreEditingPrefsManager::SetPrefs(const ScoreEditingPrefs& newPrefs) {
	prefs = newPrefs;
}

void ScoreEditingPrefsManager::ApplyToScoreEditor(class ScoreEditor& editor) {
	LOG("Applying score editing preferences");
	LOG("Display arrow after insert: " << (prefs.displayArrowAfterInsert ? "yes" : "no"));
	LOG("Double click symbol pencil: " << (prefs.dblClickSymbolPencil ? "yes" : "no"));
	LOG("Keep crescendo horizontal: " << (prefs.keepCrescendoHorizontal ? "yes" : "no"));
	LOG("Keep notes within key: " << (prefs.keepNotesWithinKey ? "yes" : "no"));
	LOG("Treat notes as single units: " << (prefs.treatNotesSingleUnits ? "yes" : "no"));
	LOG("Global staff spacings AltGr: " << (prefs.globalStaffSpacingsAltGr ? "yes" : "no"));
	LOG("Auto layout don't hide first: " << (prefs.autoLayoutDontHideFirst ? "yes" : "no"));
	LOG("Show braces in edit: " << (prefs.showBracesInEdit ? "yes" : "no"));
	LOG("Apply closes prop windows: " << (prefs.applyClosesPropWindows ? "yes" : "no"));
	LOG("Show position cursor: " << (prefs.showPositionCursor ? "yes" : "no"));
	LOG("Animate note cursor: " << (prefs.animateNoteCursor ? "yes" : "no"));
	LOG("Show note info on mouse: " << (prefs.showNoteInfoOnMouse ? "yes" : "no"));
	LOG("Snap slurs on drag: " << (prefs.snapSlursOnDrag ? "yes" : "no"));
	LOG("Unlock layout on single part: " << (prefs.unlockLayoutOnSinglePart ? "yes" : "no"));
	LOG("Double click flip staff: " << (prefs.dblClickFlipStaff ? "yes" : "no"));
	LOG("Compatibility mode: " << (prefs.compatMode ? "yes" : "no"));
	LOG("Hide notes beyond limits: " << (prefs.hideNotesBeyondLimits ? "yes" : "no"));
	LOG("Default bars per staff: " + IntStr(prefs.defaultBarsPerStaff));
}

}