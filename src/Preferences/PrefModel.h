#ifndef _Preferences_PrefModel_h_
#define _Preferences_PrefModel_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
using namespace Upp;

namespace am {

// Struct definitions for preference types











class PreferencesModel {
public:
	PreferencesModel();
	
	// Model access
	AppearancePrefs& GetAppearance() { return appearance; }
	EditingPrefs& GetEditing() { return editing; }
	EventDisplayPrefs& GetEventDisplay() { return event_display; }
	GeneralPrefs& GetGeneral() { return general; }
	MIDIPrefs& GetMIDI() { return midi; }
	MediaBayPrefs& GetMediaBay() { return mediabay; }
	RecordPrefs& GetRecord() { return record; }
	ScoresPrefs& GetScores() { return scores; }
	TransportPrefs& GetTransport() { return transport; }
	VSTPrefs& GetVST() { return vst; }
	VariAudioPrefs& GetVariAudio() { return variaudio; }
	
	// Version for schema versioning
	int GetVersion() const { return version; }
	void SetVersion(int v) { version = v; }
	
	// Load defaults
	void LoadDefaults();
	
private:
	int version = 1;  // Schema version
	
	AppearancePrefs appearance;
	EditingPrefs editing;
	EventDisplayPrefs event_display;
	GeneralPrefs general;
	MIDIPrefs midi;
	MediaBayPrefs mediabay;
	RecordPrefs record;
	ScoresPrefs scores;
	TransportPrefs transport;
	VSTPrefs vst;
	VariAudioPrefs variaudio;
};

// Basic preference structures











}

#endif