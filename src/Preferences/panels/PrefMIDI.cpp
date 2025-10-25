#include "../Preferences.h"
namespace am {

PrefMIDIGeneral::PrefMIDIGeneral() {
	Title("MIDI/General");
	
	// Initialize the controls for MIDI/General preferences
	InitControls();
}

void PrefMIDIGeneral::InitControls() {
	// Create and add the controls to the layout
	Add(midi_thru_active.VSizePos().HSizePos());
	midi_thru_active.SetLabel("MIDI Thru Active");
	
	Add(reset_on_stop.VSizePos().HSizePos());
	reset_on_stop.SetLabel("Reset on Stop");
	
	Add(length_adjust_ticks.VSizePos().HSizePos());
	length_adjust_ticks.SetLabel("Length Adjustment (Ticks)");
	length_adjust_ticks.SetRange(-10, 10);  // Range of -10 to 10 ticks
	length_adjust_ticks <<= -2;  // Default value from model
	
	Add(insert_reset_after_record.VSizePos().HSizePos());
	insert_reset_after_record.SetLabel("Insert Reset Events after Record");
	
	Add(audition_through_inserts.VSizePos().HSizePos());
	audition_through_inserts.SetLabel("Audition through MIDI Inserts/Sends");
	
	Add(max_feedback_ms.VSizePos().HSizePos());
	max_feedback_ms.SetLabel("MIDI Max. Feedback in ms");
	max_feedback_ms.SetRange(0, 1000);  // Range of 0 to 1000 ms
	max_feedback_ms <<= 250;  // Default value from model
}

void PrefMIDIGeneral::Init(PreferencesModel& model) {
	// The control initialization is already done in the constructor
	Load(model);
}

void PrefMIDIGeneral::Load(const PreferencesModel& model) {
	// Load values from the MIDI preferences in the model
	const MIDIPrefs& midi = model.GetMIDI();
	
	midi_thru_active = midi.thru_active;
	reset_on_stop = midi.reset_on_stop;
	length_adjust_ticks = midi.length_adjust_ticks;
	insert_reset_after_record = midi.insert_reset_after_record;
	audition_through_inserts = midi.audition_through_inserts;
	max_feedback_ms = midi.max_feedback_ms;
}

void PrefMIDIGeneral::Store(PreferencesModel& model, BitSet& changed) {
	// Store values from the controls to the model
	MIDIPrefs& midi = model.GetMIDI();
	
	midi.thru_active = midi_thru_active;
	midi.reset_on_stop = reset_on_stop;
	midi.length_adjust_ticks = length_adjust_ticks;
	midi.insert_reset_after_record = insert_reset_after_record;
	midi.audition_through_inserts = audition_through_inserts;
	midi.max_feedback_ms = max_feedback_ms;
	
	// The "changed" BitSet would be used to track which preferences were modified
	LOG("Storing MIDI/General preferences");
}

// Register this panel with the registry
REGISTER_PREF_PANEL("MIDI", "General", PrefMIDIGeneral)

}