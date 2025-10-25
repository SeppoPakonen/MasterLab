#include "ScoresEngine.h"
namespace am {

NoteLayerPrefsManager::NoteLayerPrefsManager() {
	// Initialize with default note layer preferences
	prefs.braces = 100;
	prefs.barNumbers = 100;
	prefs.staffNames = 100;
	prefs.stems = 100;
	prefs.keys = 100;
	prefs.clefs = 100;
	prefs.barLines = 100;
	prefs.staves = 100;
	prefs.noteSymbols = 100;
	prefs.graphics = 100;
	prefs.slurs = 100;
	prefs.notes = 100;
	prefs.rests = 100;
	prefs.timeSignatures = 100;
}

void NoteLayerPrefsManager::SetPrefs(const NoteLayerPrefs& newPrefs) {
	prefs = newPrefs;
}

void NoteLayerPrefsManager::ApplyToNotationDisplay() {
	LOG("Applying note layer preferences to notation display");
	LOG("Braces: " + IntStr(prefs.braces));
	LOG("Bar Numbers: " + IntStr(prefs.barNumbers));
	LOG("Staff Names: " + IntStr(prefs.staffNames));
	LOG("Stems: " + IntStr(prefs.stems));
	LOG("Keys: " + IntStr(prefs.keys));
	LOG("Clefs: " + IntStr(prefs.clefs));
	LOG("Bar Lines: " + IntStr(prefs.barLines));
	LOG("Staves: " + IntStr(prefs.staves));
	LOG("Note Symbols: " + IntStr(prefs.noteSymbols));
	LOG("Graphics: " + IntStr(prefs.graphics));
	LOG("Slurs: " + IntStr(prefs.slurs));
	LOG("Notes: " + IntStr(prefs.notes));
	LOG("Rests: " + IntStr(prefs.rests));
	LOG("Time Signatures: " + IntStr(prefs.timeSignatures));
}

}