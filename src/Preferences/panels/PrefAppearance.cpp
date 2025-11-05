#include "PrefAppearance.h"

namespace am {

// Define member controls for PrefAppearance
// These need to be class members to access them in Load/Store methods
struct PrefAppearance::Data {
	// General section controls
	LabeledDropList* theme_ctrl = nullptr;
	LabeledDropList* density_ctrl = nullptr;
	LabeledDropList* font_ctrl = nullptr;
	
	// Meters section controls
	LabeledDropList* style_ctrl = nullptr;
	LabeledOption* response_ctrl = nullptr;
	
	// Work Area section controls
	LabeledOption* grid_ctrl = nullptr;
	LabeledOption* ruler_ctrl = nullptr;
	LabeledSlider* height_ctrl = nullptr;
};

PrefAppearance::PrefAppearance() {
	data = new Data();
	
	// Initialize UI sections
	InitGeneralSection();
	InitMetersSection();
	InitWorkAreaSection();
}

void PrefAppearance::Init(PreferencesModel& model) {
	// Initialize the panel with model data
	// This method should set up the initial state based on the model
	// For PrefAppearance, we might set the initial values based on the model
}

void PrefAppearance::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const AppearancePrefs& prefs = model.GetAppearance();
	
	if(data->theme_ctrl) {
		// Assuming themes are { "Light", "Dark", "High Contrast" } mapped to indices 0, 1, 2
		// We'll need to implement proper mapping, for now just setting to a default
		data->theme_ctrl->SetData(0); // Placeholder: should map from actual model value
	}
	if(data->density_ctrl) {
		// Assuming densities are { "Compact", "Normal", "Spacious" } mapped to indices 0, 1, 2
		data->density_ctrl->SetData(1); // Default to "Normal"
	}
	if(data->font_ctrl) {
		// Assuming fonts are { "System Default", "Arial", "Helvetica", "Roboto" } mapped to indices 0, 1, 2, 3
		data->font_ctrl->SetData(0); // Default to "System Default"
	}
	if(data->style_ctrl) {
		// Assuming meter styles are { "Vertical", "Horizontal", "Circular" } mapped to indices 0, 1, 2
		data->style_ctrl->SetData(0); // Default to "Vertical"
	}
	if(data->response_ctrl) {
		// For peak hold response
		data->response_ctrl->SetData(true); // Default to enabled
	}
	if(data->grid_ctrl) {
		// For show grid option
		data->grid_ctrl->SetData(true); // Default to enabled
	}
	if(data->ruler_ctrl) {
		// For show rulers option
		data->ruler_ctrl->SetData(true); // Default to enabled
	}
	if(data->height_ctrl) {
		// For default track height slider (20-200 range)
		data->height_ctrl->SetData(80); // Default to 80px
	}
}

void PrefAppearance::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	AppearancePrefs& prefs = model.GetAppearance();
	
	// Create temporary values to check if they differ from the model
	int theme_index = 0;
	if(data->theme_ctrl) {
		theme_index = data->theme_ctrl->GetData();
		// In a real implementation, we would map this index to an actual theme value in the model
		changed.Add(theme_index != 0); // Placeholder comparison
	}
	
	int density_index = 1;
	if(data->density_ctrl) {
		density_index = data->density_ctrl->GetData();
		changed.Add(density_index != 1); // Default is 1 (Normal)
	}
	
	int font_index = 0;
	if(data->font_ctrl) {
		font_index = data->font_ctrl->GetData();
		changed.Add(font_index != 0); // Default is 0 (System Default)
	}
	
	int style_index = 0;
	if(data->style_ctrl) {
		style_index = data->style_ctrl->GetData();
		changed.Add(style_index != 0); // Default is 0 (Vertical)
	}
	
	bool peak_hold = true;
	if(data->response_ctrl) {
		peak_hold = data->response_ctrl->GetData();
		changed.Add(peak_hold != true); // Default is true
	}
	
	bool show_grid = true;
	if(data->grid_ctrl) {
		show_grid = data->grid_ctrl->GetData();
		changed.Add(show_grid != true); // Default is true
	}
	
	bool show_rulers = true;
	if(data->ruler_ctrl) {
		show_rulers = data->ruler_ctrl->GetData();
		changed.Add(show_rulers != true); // Default is true
	}
	
	int track_height = 80;
	if(data->height_ctrl) {
		track_height = data->height_ctrl->GetData();
		changed.Add(track_height != 80); // Default is 80
	}
}

void PrefAppearance::InitGeneralSection() {
	// Initialize general appearance settings
	LabelBox* general_box = new LabelBox("General Appearance");
	
	// Theme selection
	data->theme_ctrl = &dynamic_cast<LabeledDropList&>(CreateLabeledDropList("Theme", 
		{ "Light", "Dark", "High Contrast" }, 0));
	general_box->Add(data->theme_ctrl->SizePos());
	
	// Display density
	data->density_ctrl = &dynamic_cast<LabeledDropList&>(CreateLabeledDropList("Display Density", 
		{ "Compact", "Normal", "Spacious" }, 1));
	general_box->Add(data->density_ctrl->SizePos());
	
	// Font selection
	data->font_ctrl = &dynamic_cast<LabeledDropList&>(CreateLabeledDropList("Font", 
		{ "System Default", "Arial", "Helvetica", "Roboto" }, 0));
	general_box->Add(data->font_ctrl->SizePos());
	
	Add(general_box->SizePos());
}

void PrefAppearance::InitMetersSection() {
	// Initialize meter settings
	LabelBox* meters_box = new LabelBox("Meters");
	
	// Meter style
	data->style_ctrl = &dynamic_cast<LabeledDropList&>(CreateLabeledDropList("Meter Style", 
		{ "Vertical", "Horizontal", "Circular" }, 0));
	meters_box->Add(data->style_ctrl->SizePos());
	
	// Meter response
	data->response_ctrl = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Peak Hold", true));
	meters_box->Add(data->response_ctrl->SizePos());
	
	Add(meters_box->SizePos());
}

void PrefAppearance::InitWorkAreaSection() {
	// Initialize work area settings
	LabelBox* workarea_box = new LabelBox("Work Area");
	
	// Grid visibility
	data->grid_ctrl = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Grid", true));
	workarea_box->Add(data->grid_ctrl->SizePos());
	
	// Ruler visibility
	data->ruler_ctrl = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Rulers", true));
	workarea_box->Add(data->ruler_ctrl->SizePos());
	
	// Track height
	data->height_ctrl = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Default Track Height", 20, 200, 80));
	workarea_box->Add(data->height_ctrl->SizePos());
	
	Add(workarea_box->SizePos());
}

REGISTER_PREF_PANEL("Appearance", "General", PrefAppearance)

}