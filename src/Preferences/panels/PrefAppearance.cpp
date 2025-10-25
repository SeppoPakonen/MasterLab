#include "../Preferences.h"
namespace am {

PrefAppearance::PrefAppearance() {
	Title("Appearance");
	
	// Create a simple layout for the appearance panel
	StaticRect bg;
	bg.SetFrame(1);
	bg.SetInk(LtGray());
	Add(bg.SizePos());
	
	// Initialize sections
	InitGeneralSection();
	InitMetersSection();
	InitWorkAreaSection();
}

void PrefAppearance::Init(PreferencesModel& model) {
	// Initialize the panel with the model
	Load(model);
}

void PrefAppearance::Load(const PreferencesModel& model) {
	// Load values from the appearance preferences in the model
	const AppearancePrefs& appearance = model.GetAppearance();
	
	// For now, just log - in a full implementation we would load the values
	// into the appropriate controls
	LOG("Loading Appearance preferences");
	LOG("Saturation: " + IntStr(appearance.saturation));
	LOG("Brightness: " + IntStr(appearance.brightness));
	LOG("Button Brightness: " + IntStr(appearance.button_brightness));
}

void PrefAppearance::Store(PreferencesModel& model, BitSet& changed) {
	// Store values from the controls to the model
	AppearancePrefs& appearance = model.GetAppearance();
	
	// In a full implementation we would store the control values
	// to the appropriate model fields
	LOG("Storing Appearance preferences");
	
	// For now, just update the model with some values
	// appearance.saturation = ...; // value from control
	// appearance.brightness = ...; // value from control
	// appearance.button_brightness = ...; // value from control
}

void PrefAppearance::InitGeneralSection() {
	// Initialize controls for Appearance/General
	LOG("Initializing Appearance General section");
}

void PrefAppearance::InitMetersSection() {
	// Initialize controls for Appearance/Meters
	LOG("Initializing Appearance Meters section");
	
	// Create preview VU meter
	preview_vu_rect.SetFrame(1);
	preview_vu_rect.SetInk(LtBlue());
	// Add more sophisticated meter preview as needed
}

void PrefAppearance::InitWorkAreaSection() {
	// Initialize controls for Appearance/Work Area
	LOG("Initializing Appearance Work Area section");
}

// Register this panel with the registry
REGISTER_PREF_PANEL("Appearance", "General", PrefAppearance)

}