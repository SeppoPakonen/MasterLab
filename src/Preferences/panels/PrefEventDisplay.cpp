#include "../Preferences.h"
namespace am {

PrefEventDisplayGeneral::PrefEventDisplayGeneral() {
	Title("Event Display/General");
	
	// Initialize the controls for Event Display/General preferences
	InitControls();
}

void PrefEventDisplayGeneral::InitControls() {
	// Create and add the controls to the layout
	Add(show_event_names.VSizePos().HSizePos());
	show_event_names.SetLabel("Show Event Names");
	
	Add(transparent_events.VSizePos().HSizePos());
	transparent_events.SetLabel("Transparent Events");
	
	Add(show_data_small_heights.VSizePos().HSizePos());
	show_data_small_heights.SetLabel("Show Data on Small Track Heights");
	
	Add(colorize_event_background.VSizePos().HSizePos());
	colorize_event_background.SetLabel("Colorize Event Background");
}

void PrefEventDisplayGeneral::Init(PreferencesModel& model) {
	// The control initialization is already done in the constructor
	Load(model);
}

void PrefEventDisplayGeneral::Load(const PreferencesModel& model) {
	// Load values from the event display preferences in the model
	const EventDisplayPrefs& event_display = model.GetEventDisplay();
	
	show_event_names = event_display.show_names;
	transparent_events = event_display.transparent;
	show_data_small_heights = event_display.show_on_small_heights;
	colorize_event_background = event_display.colorize_bg;
}

void PrefEventDisplayGeneral::Store(PreferencesModel& model, BitSet& changed) {
	// Store values from the controls to the model
	EventDisplayPrefs& event_display = model.GetEventDisplay();
	
	event_display.show_names = show_event_names;
	event_display.transparent = transparent_events;
	event_display.show_on_small_heights = show_data_small_heights;
	event_display.colorize_bg = colorize_event_background;
	
	// The "changed" BitSet would be used to track which preferences were modified
	LOG("Storing Event Display/General preferences");
}

// Register this panel with the registry
REGISTER_PREF_PANEL("Event Display", "General", PrefEventDisplayGeneral)

}