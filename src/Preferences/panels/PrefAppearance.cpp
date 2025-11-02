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
	
	// For now, we're using placeholder values since we need to properly connect controls
	// In a real implementation, we would set the values of the actual controls here
	if(data->theme_ctrl) {
		// Theme mapping would be implemented here
	}
	if(data->density_ctrl) {
		// Density mapping would be implemented here
	}
	if(data->font_ctrl) {
		// Font mapping would be implemented here
	}
	if(data->style_ctrl) {
		// Meter style mapping would be implemented here
	}
	if(data->response_ctrl) {
		// Peak hold mapping would be implemented here
	}
	if(data->grid_ctrl) {
		// Show grid mapping would be implemented here
	}
	if(data->ruler_ctrl) {
		// Show rulers mapping would be implemented here
	}
	if(data->height_ctrl) {
		// Default track height mapping would be implemented here
		// For now, just setting to a placeholder value
		// In real implementation would use actual model value
	}
}

void PrefAppearance::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	AppearancePrefs& prefs = model.GetAppearance();
	
	// Check if values have changed and update the model
	if(data->theme_ctrl) {
		// Get value from theme_ctrl and update the model
		// For now, using placeholder logic
	}
	if(data->density_ctrl) {
		// Get value from density_ctrl and update the model
	}
	if(data->font_ctrl) {
		// Get value from font_ctrl and update the model
	}
	if(data->style_ctrl) {
		// Get value from style_ctrl and update the model
	}
	if(data->response_ctrl) {
		// Get value from response_ctrl and update the model
	}
	if(data->grid_ctrl) {
		// Get value from grid_ctrl and update the model
	}
	if(data->ruler_ctrl) {
		// Get value from ruler_ctrl and update the model
	}
	if(data->height_ctrl) {
		// Get value from height_ctrl and update the model
		// In real implementation would use actual control value
	}
	
	changed.Add(false); // Placeholder - in real implementation, would track actual changes
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