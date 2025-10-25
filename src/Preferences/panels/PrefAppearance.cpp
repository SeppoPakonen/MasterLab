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
	// Load values from the model
	// For now, just log
	LOG("Loading Appearance preferences");
}

void PrefAppearance::Store(PreferencesModel& model, BitSet& changed) {
	// Store values to the model
	// For now, just log
	LOG("Storing Appearance preferences");
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

}