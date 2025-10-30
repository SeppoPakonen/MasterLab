#include "PrefTransport.h"

namespace am {

PrefTransport::PrefTransport() {
	Title("Transport");
	
	// Create a simple layout for the transport panel
	StaticRect bg;
	bg.Frame(Single(1));
	bg.Rect(0, 0, 20, 20);
	bg.Ink(LtGray());
	Add(bg.SizePos());
}

void PrefTransport::Init(PreferencesModel& model) {
	// Initialize the panel with model data
}

void PrefTransport::Load(const PreferencesModel& model) {
	// Load data from model to UI
}

void PrefTransport::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
}

void PrefTransport::InitDisplaySection() {
	// Initialize display settings
}

void PrefTransport::InitBehaviorSection() {
	// Initialize behavior settings
}

void PrefTransport::InitAdvancedBehaviorSection() {
	// Initialize advanced behavior settings
}

void PrefTransport::InitScrubbingSection() {
	// Initialize scrubbing settings
}

REGISTER_PREF_PANEL("Transport", "General", PrefTransport)

}