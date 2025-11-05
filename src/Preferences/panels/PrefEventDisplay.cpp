#include "PrefEventDisplay.h"

namespace am {

// Define member controls for PrefEventDisplay
struct PrefEventDisplay::Data {
	// General section controls
	LabeledSlider* display_density = nullptr;
	
	// Zoom section controls
	LabeledOption* zoom_to_selection = nullptr;
	LabeledOption* zoom_preserves_position = nullptr;
	
	// Track height section controls
	LabeledSlider* default_track_height = nullptr;
	LabeledSlider* min_track_height = nullptr;
	LabeledSlider* max_track_height = nullptr;
	
	// Lane display section controls
	LabeledOption* show_track_lanes = nullptr;
	LabeledOption* show_midi_lanes = nullptr;
	LabeledOption* show_audio_lanes = nullptr;
	LabeledOption* show_video_lanes = nullptr;
	LabeledOption* show_marker_lanes = nullptr;
	LabeledOption* show_tempo_lanes = nullptr;
};

PrefEventDisplay::PrefEventDisplay() {
	data = new Data();
	
	// Initialize UI sections
	InitGeneralSection();
	InitDisplaySection();
	InitZoomSection();
	InitTrackHeightSection();
	InitLaneDisplaySection();
}

void PrefEventDisplay::Init(PreferencesModel& model) {
	// Initialize the panel with model data
}

void PrefEventDisplay::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const EventDisplayPrefs& prefs = model.GetEventDisplay();
	
	if(data->display_density) {
		data->display_density->SetData(prefs.display_density);
	}
	if(data->zoom_to_selection) {
		data->zoom_to_selection->SetData(prefs.zoom_to_selection);
	}
	if(data->zoom_preserves_position) {
		data->zoom_preserves_position->SetData(prefs.zoom_preserves_position);
	}
	if(data->default_track_height) {
		data->default_track_height->SetData(prefs.default_track_height);
	}
	if(data->min_track_height) {
		data->min_track_height->SetData(prefs.minimum_track_height);
	}
	if(data->max_track_height) {
		data->max_track_height->SetData(prefs.maximum_track_height);
	}
	if(data->show_track_lanes) {
		data->show_track_lanes->SetData(prefs.show_track_lanes);
	}
	if(data->show_midi_lanes) {
		data->show_midi_lanes->SetData(prefs.show_midi_lanes);
	}
	if(data->show_audio_lanes) {
		data->show_audio_lanes->SetData(prefs.show_audio_lanes);
	}
	if(data->show_video_lanes) {
		data->show_video_lanes->SetData(prefs.show_video_lanes);
	}
	if(data->show_marker_lanes) {
		data->show_marker_lanes->SetData(prefs.show_marker_lanes);
	}
	if(data->show_tempo_lanes) {
		data->show_tempo_lanes->SetData(prefs.show_tempo_lanes);
	}
}

void PrefEventDisplay::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	EventDisplayPrefs& prefs = model.GetEventDisplay();
	
	// Check if values have changed and update the model
	if(data->display_density) {
		int new_val = data->display_density->GetData();
		changed.Add(new_val != prefs.display_density);
		prefs.display_density = new_val;
	}
	if(data->zoom_to_selection) {
		bool new_val = data->zoom_to_selection->GetData();
		changed.Add(new_val != prefs.zoom_to_selection);
		prefs.zoom_to_selection = new_val;
	}
	if(data->zoom_preserves_position) {
		bool new_val = data->zoom_preserves_position->GetData();
		changed.Add(new_val != prefs.zoom_preserves_position);
		prefs.zoom_preserves_position = new_val;
	}
	if(data->default_track_height) {
		int new_val = data->default_track_height->GetData();
		changed.Add(new_val != prefs.default_track_height);
		prefs.default_track_height = new_val;
	}
	if(data->min_track_height) {
		int new_val = data->min_track_height->GetData();
		changed.Add(new_val != prefs.minimum_track_height);
		prefs.minimum_track_height = new_val;
	}
	if(data->max_track_height) {
		int new_val = data->max_track_height->GetData();
		changed.Add(new_val != prefs.maximum_track_height);
		prefs.maximum_track_height = new_val;
	}
	if(data->show_track_lanes) {
		bool new_val = data->show_track_lanes->GetData();
		changed.Add(new_val != prefs.show_track_lanes);
		prefs.show_track_lanes = new_val;
	}
	if(data->show_midi_lanes) {
		bool new_val = data->show_midi_lanes->GetData();
		changed.Add(new_val != prefs.show_midi_lanes);
		prefs.show_midi_lanes = new_val;
	}
	if(data->show_audio_lanes) {
		bool new_val = data->show_audio_lanes->GetData();
		changed.Add(new_val != prefs.show_audio_lanes);
		prefs.show_audio_lanes = new_val;
	}
	if(data->show_video_lanes) {
		bool new_val = data->show_video_lanes->GetData();
		changed.Add(new_val != prefs.show_video_lanes);
		prefs.show_video_lanes = new_val;
	}
	if(data->show_marker_lanes) {
		bool new_val = data->show_marker_lanes->GetData();
		changed.Add(new_val != prefs.show_marker_lanes);
		prefs.show_marker_lanes = new_val;
	}
	if(data->show_tempo_lanes) {
		bool new_val = data->show_tempo_lanes->GetData();
		changed.Add(new_val != prefs.show_tempo_lanes);
		prefs.show_tempo_lanes = new_val;
	}
}

void PrefEventDisplay::InitGeneralSection() {
	// Initialize general event display settings
	LabelBox* general_box = new LabelBox("General");
	
	data->display_density = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Display Density", 0, 100, 50));
	general_box->Add(data->display_density->SizePos());
	
	Add(general_box->SizePos());
}

void PrefEventDisplay::InitDisplaySection() {
	// Initialize display settings
	LabelBox* display_box = new LabelBox("Display");
	
	Add(display_box->SizePos());
}

void PrefEventDisplay::InitZoomSection() {
	// Initialize zoom settings
	LabelBox* zoom_box = new LabelBox("Zoom");
	
	data->zoom_to_selection = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Zoom to Selection", true));
	zoom_box->Add(data->zoom_to_selection->SizePos());
	
	data->zoom_preserves_position = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Zoom Preserves Position", false));
	zoom_box->Add(data->zoom_preserves_position->SizePos());
	
	Add(zoom_box->SizePos());
}

void PrefEventDisplay::InitTrackHeightSection() {
	// Initialize track height settings
	LabelBox* height_box = new LabelBox("Track Height");
	
	data->default_track_height = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Default Track Height (px)", 8, 200, 24));
	height_box->Add(data->default_track_height->SizePos());
	
	data->min_track_height = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Minimum Track Height (px)", 8, 100, 16));
	height_box->Add(data->min_track_height->SizePos());
	
	data->max_track_height = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Maximum Track Height (px)", 16, 500, 64));
	height_box->Add(data->max_track_height->SizePos());
	
	Add(height_box->SizePos());
}

void PrefEventDisplay::InitLaneDisplaySection() {
	// Initialize lane display settings
	LabelBox* lane_box = new LabelBox("Lane Display");
	
	data->show_track_lanes = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Track Lanes", true));
	lane_box->Add(data->show_track_lanes->SizePos());
	
	data->show_midi_lanes = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show MIDI Lanes", true));
	lane_box->Add(data->show_midi_lanes->SizePos());
	
	data->show_audio_lanes = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Audio Lanes", true));
	lane_box->Add(data->show_audio_lanes->SizePos());
	
	data->show_video_lanes = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Video Lanes", true));
	lane_box->Add(data->show_video_lanes->SizePos());
	
	data->show_marker_lanes = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Marker Lanes", true));
	lane_box->Add(data->show_marker_lanes->SizePos());
	
	data->show_tempo_lanes = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Tempo Lanes", true));
	lane_box->Add(data->show_tempo_lanes->SizePos());
	
	Add(lane_box->SizePos());
}

REGISTER_PREF_PANEL("Event Display", "General", PrefEventDisplay)

}