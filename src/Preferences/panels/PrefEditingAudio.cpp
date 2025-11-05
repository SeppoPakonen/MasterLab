#include "PrefEditingAudio.h"

namespace am {

// Define member controls for PrefEditingAudio
struct PrefEditingAudio::Data {
	// General editing controls
	LabeledDropList* default_track_time_type = nullptr;
	LabeledOption* auto_select_under_cursor = nullptr;
	LabeledOption* cycle_follows_range = nullptr;
	LabeledOption* delete_overlaps = nullptr;
	LabeledOption* link_editors = nullptr;
	LabeledOption* parts_get_track_names = nullptr;
	LabeledOption* quick_zoom = nullptr;
	LabeledSlider* drag_delay_ms = nullptr;
	
	// Event color controls
	LabeledOption* color_events_by_track = nullptr;
	LabeledOption* color_events_by_type = nullptr;
	LabeledOption* color_events_by_velocity = nullptr;
};

PrefEditingAudio::PrefEditingAudio() {
	data = new Data();
	
	// Initialize UI sections
	InitControls();
}

void PrefEditingAudio::Init(PreferencesModel& model) {
	// Initialize the panel with model data
}

void PrefEditingAudio::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const EditingPrefs& prefs = model.GetEditing();
	
	// For default_track_time_type, we'll assume the options are { "musical", "time_linear", "follow_transport" }
	if(data->default_track_time_type) {
		int index = 0;
		if(prefs.default_track_time_type == "time_linear") index = 1;
		else if(prefs.default_track_time_type == "follow_transport") index = 2;
		data->default_track_time_type->SetData(index);
	}
	if(data->auto_select_under_cursor) {
		data->auto_select_under_cursor->SetData(prefs.auto_select_under_cursor);
	}
	if(data->cycle_follows_range) {
		data->cycle_follows_range->SetData(prefs.cycle_follows_range);
	}
	if(data->delete_overlaps) {
		data->delete_overlaps->SetData(prefs.delete_overlaps);
	}
	if(data->link_editors) {
		data->link_editors->SetData(prefs.link_editors);
	}
	if(data->parts_get_track_names) {
		data->parts_get_track_names->SetData(prefs.parts_get_track_names);
	}
	if(data->quick_zoom) {
		data->quick_zoom->SetData(prefs.quick_zoom);
	}
	if(data->drag_delay_ms) {
		data->drag_delay_ms->SetData(prefs.drag_delay_ms);
	}
	if(data->color_events_by_track) {
		data->color_events_by_track->SetData(prefs.color_events_by_track);
	}
	if(data->color_events_by_type) {
		data->color_events_by_type->SetData(prefs.color_events_by_type);
	}
	if(data->color_events_by_velocity) {
		data->color_events_by_velocity->SetData(prefs.color_events_by_velocity);
	}
}

void PrefEditingAudio::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	EditingPrefs& prefs = model.GetEditing();
	
	// Check if values have changed and update the model
	if(data->default_track_time_type) {
		int index = data->default_track_time_type->GetData();
		String time_type = "musical"; // Default
		if(index == 1) time_type = "time_linear";
		else if(index == 2) time_type = "follow_transport";
		
		changed.Add(time_type != prefs.default_track_time_type);
		prefs.default_track_time_type = time_type;
	}
	if(data->auto_select_under_cursor) {
		bool new_val = data->auto_select_under_cursor->GetData();
		changed.Add(new_val != prefs.auto_select_under_cursor);
		prefs.auto_select_under_cursor = new_val;
	}
	if(data->cycle_follows_range) {
		bool new_val = data->cycle_follows_range->GetData();
		changed.Add(new_val != prefs.cycle_follows_range);
		prefs.cycle_follows_range = new_val;
	}
	if(data->delete_overlaps) {
		bool new_val = data->delete_overlaps->GetData();
		changed.Add(new_val != prefs.delete_overlaps);
		prefs.delete_overlaps = new_val;
	}
	if(data->link_editors) {
		bool new_val = data->link_editors->GetData();
		changed.Add(new_val != prefs.link_editors);
		prefs.link_editors = new_val;
	}
	if(data->parts_get_track_names) {
		bool new_val = data->parts_get_track_names->GetData();
		changed.Add(new_val != prefs.parts_get_track_names);
		prefs.parts_get_track_names = new_val;
	}
	if(data->quick_zoom) {
		bool new_val = data->quick_zoom->GetData();
		changed.Add(new_val != prefs.quick_zoom);
		prefs.quick_zoom = new_val;
	}
	if(data->drag_delay_ms) {
		int new_val = data->drag_delay_ms->GetData();
		changed.Add(new_val != prefs.drag_delay_ms);
		prefs.drag_delay_ms = new_val;
	}
	if(data->color_events_by_track) {
		bool new_val = data->color_events_by_track->GetData();
		changed.Add(new_val != prefs.color_events_by_track);
		prefs.color_events_by_track = new_val;
	}
	if(data->color_events_by_type) {
		bool new_val = data->color_events_by_type->GetData();
		changed.Add(new_val != prefs.color_events_by_type);
		prefs.color_events_by_type = new_val;
	}
	if(data->color_events_by_velocity) {
		bool new_val = data->color_events_by_velocity->GetData();
		changed.Add(new_val != prefs.color_events_by_velocity);
		prefs.color_events_by_velocity = new_val;
	}
}

void PrefEditingAudio::InitControls() {
	// Initialize editing controls
	LabelBox* editing_box = new LabelBox("General Editing");
	
	// Default track time type options: { "musical", "time_linear", "follow_transport" }
	data->default_track_time_type = &dynamic_cast<LabeledDropList&>(CreateLabeledDropList("Default Track Time Type", 
		{ "Musical", "Time Linear", "Follow Transport" }, 0));
	editing_box->Add(data->default_track_time_type->SizePos());
	
	data->auto_select_under_cursor = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Auto-select Under Cursor", false));
	editing_box->Add(data->auto_select_under_cursor->SizePos());
	
	data->cycle_follows_range = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Cycle Follows Range", false));
	editing_box->Add(data->cycle_follows_range->SizePos());
	
	data->delete_overlaps = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Delete Overlaps", false));
	editing_box->Add(data->delete_overlaps->SizePos());
	
	data->link_editors = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Link Editors", true));
	editing_box->Add(data->link_editors->SizePos());
	
	data->parts_get_track_names = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Parts Get Track Names", false));
	editing_box->Add(data->parts_get_track_names->SizePos());
	
	data->quick_zoom = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Quick Zoom", false));
	editing_box->Add(data->quick_zoom->SizePos());
	
	data->drag_delay_ms = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Drag Delay (ms)", 0, 1000, 200));
	editing_box->Add(data->drag_delay_ms->SizePos());
	
	Add(editing_box->SizePos());
	
	// Event color controls
	LabelBox* event_colors_box = new LabelBox("Event Colors");
	
	data->color_events_by_track = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Color Events by Track", true));
	event_colors_box->Add(data->color_events_by_track->SizePos());
	
	data->color_events_by_type = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Color Events by Type", false));
	event_colors_box->Add(data->color_events_by_type->SizePos());
	
	data->color_events_by_velocity = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Color Events by Velocity", false));
	event_colors_box->Add(data->color_events_by_velocity->SizePos());
	
	Add(event_colors_box->SizePos());
}

REGISTER_PREF_PANEL("Editing", "Audio", PrefEditingAudio)

}