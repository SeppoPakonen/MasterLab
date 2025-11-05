#include "PrefTransport.h"

namespace am {

// Define member controls for PrefTransport
struct PrefTransport::Data {
	// Display section controls
	LabeledOption* show_transport = nullptr;
	LabeledOption* show_time_display = nullptr;
	LabeledOption* show_locator = nullptr;
	
	// Behavior section controls
	LabeledOption* auto_return = nullptr;
	LabeledOption* stop_at_end = nullptr;
	LabeledOption* stop_on_focus = nullptr;
	
	// Advanced behavior section controls
	LabeledOption* playback_preview = nullptr;
	LabeledOption* zoom_while_locating = nullptr;
	LabeledSlider* cursor_width = nullptr;
	
	// Scrubbing section controls
	LabeledSlider* scrub_response = nullptr;
	LabeledSlider* scrub_volume = nullptr;
	LabeledOption* cpu_saving = nullptr;
};

PrefTransport::PrefTransport() {
	data = new Data();
	
	// Initialize UI sections
	InitDisplaySection();
	InitBehaviorSection();
	InitAdvancedBehaviorSection();
	InitScrubbingSection();
}

void PrefTransport::Init(PreferencesModel& model) {
	// Initialize the panel with model data
	// This method should set up the initial state based on the model
}

void PrefTransport::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const TransportPrefs& prefs = model.GetTransport();
	
	if(data->show_transport) {
		data->show_transport->SetData(prefs.show_transport);
	}
	if(data->show_time_display) {
		data->show_time_display->SetData(prefs.show_time_display);
	}
	if(data->show_locator) {
		data->show_locator->SetData(prefs.show_locator);
	}
	if(data->auto_return) {
		data->auto_return->SetData(prefs.auto_return_to_start);
	}
	if(data->stop_at_end) {
		data->stop_at_end->SetData(prefs.stop_at_end_of_loop);
	}
	if(data->stop_on_focus) {
		data->stop_on_focus->SetData(prefs.stop_on_lost_focus);
	}
	if(data->playback_preview) {
		data->playback_preview->SetData(prefs.playback_toggle_preview);
	}
	if(data->zoom_while_locating) {
		data->zoom_while_locating->SetData(prefs.zoom_while_locating);
	}
	if(data->cursor_width) {
		data->cursor_width->SetData(prefs.cursor_width);
	}
	if(data->scrub_response) {
		data->scrub_response->SetData(prefs.scrub.response);
	}
	if(data->scrub_volume) {
		data->scrub_volume->SetData(prefs.scrub.volume);
	}
	if(data->cpu_saving) {
		data->cpu_saving->SetData(prefs.scrub.cpu_saving);
	}
}

void PrefTransport::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	TransportPrefs& prefs = model.GetTransport();
	
	// Check if values have changed and update the model
	if(data->show_transport) {
		bool new_val = data->show_transport->GetData();
		changed.Add(new_val != prefs.show_transport);
		prefs.show_transport = new_val;
	}
	if(data->show_time_display) {
		bool new_val = data->show_time_display->GetData();
		changed.Add(new_val != prefs.show_time_display);
		prefs.show_time_display = new_val;
	}
	if(data->show_locator) {
		bool new_val = data->show_locator->GetData();
		changed.Add(new_val != prefs.show_locator);
		prefs.show_locator = new_val;
	}
	if(data->auto_return) {
		bool new_val = data->auto_return->GetData();
		changed.Add(new_val != prefs.auto_return_to_start);
		prefs.auto_return_to_start = new_val;
	}
	if(data->stop_at_end) {
		bool new_val = data->stop_at_end->GetData();
		changed.Add(new_val != prefs.stop_at_end_of_loop);
		prefs.stop_at_end_of_loop = new_val;
	}
	if(data->stop_on_focus) {
		bool new_val = data->stop_on_focus->GetData();
		changed.Add(new_val != prefs.stop_on_lost_focus);
		prefs.stop_on_lost_focus = new_val;
	}
	if(data->playback_preview) {
		bool new_val = data->playback_preview->GetData();
		changed.Add(new_val != prefs.playback_toggle_preview);
		prefs.playback_toggle_preview = new_val;
	}
	if(data->zoom_while_locating) {
		bool new_val = data->zoom_while_locating->GetData();
		changed.Add(new_val != prefs.zoom_while_locating);
		prefs.zoom_while_locating = new_val;
	}
	if(data->cursor_width) {
		int new_val = data->cursor_width->GetData();
		changed.Add(new_val != prefs.cursor_width);
		prefs.cursor_width = new_val;
	}
	if(data->scrub_response) {
		int new_val = data->scrub_response->GetData();
		changed.Add(new_val != prefs.scrub.response);
		prefs.scrub.response = new_val;
	}
	if(data->scrub_volume) {
		int new_val = data->scrub_volume->GetData();
		changed.Add(new_val != prefs.scrub.volume);
		prefs.scrub.volume = new_val;
	}
	if(data->cpu_saving) {
		bool new_val = data->cpu_saving->GetData();
		changed.Add(new_val != prefs.scrub.cpu_saving);
		prefs.scrub.cpu_saving = new_val;
	}
}

void PrefTransport::InitDisplaySection() {
	// Initialize display settings
	LabelBox* display_box = new LabelBox("Display");
	
	data->show_transport = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Transport", true));
	display_box->Add(data->show_transport->SizePos());
	
	data->show_time_display = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Time Display", true));
	display_box->Add(data->show_time_display->SizePos());
	
	data->show_locator = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Locator", true));
	display_box->Add(data->show_locator->SizePos());
	
	Add(display_box->SizePos());
}

void PrefTransport::InitBehaviorSection() {
	// Initialize behavior settings
	LabelBox* behavior_box = new LabelBox("Behavior");
	
	data->auto_return = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Auto Return to Start", true));
	behavior_box->Add(data->auto_return->SizePos());
	
	data->stop_at_end = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Stop at End of Loop", false));
	behavior_box->Add(data->stop_at_end->SizePos());
	
	data->stop_on_focus = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Stop on Lost Focus", false));
	behavior_box->Add(data->stop_on_focus->SizePos());
	
	Add(behavior_box->SizePos());
}

void PrefTransport::InitAdvancedBehaviorSection() {
	// Initialize advanced behavior settings
	LabelBox* advanced_box = new LabelBox("Advanced Behavior");
	
	data->playback_preview = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Playback Toggle Preview", false));
	advanced_box->Add(data->playback_preview->SizePos());
	
	data->zoom_while_locating = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Zoom While Locating", false));
	advanced_box->Add(data->zoom_while_locating->SizePos());
	
	data->cursor_width = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Cursor Width (pixels)", 1, 10, 3));
	advanced_box->Add(data->cursor_width->SizePos());
	
	Add(advanced_box->SizePos());
}

void PrefTransport::InitScrubbingSection() {
	// Initialize scrubbing settings
	LabelBox* scrubbing_box = new LabelBox("Scrubbing");
	
	data->scrub_response = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Scrub Response", 0, 100, 50));
	scrubbing_box->Add(data->scrub_response->SizePos());
	
	data->scrub_volume = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Scrub Volume", 0, 100, 50));
	scrubbing_box->Add(data->scrub_volume->SizePos());
	
	data->cpu_saving = &dynamic_cast<LabeledOption&>(CreateLabeledOption("CPU Saving Mode", false));
	scrubbing_box->Add(data->cpu_saving->SizePos());
	
	Add(scrubbing_box->SizePos());
}

REGISTER_PREF_PANEL("Transport", "General", PrefTransport)

}