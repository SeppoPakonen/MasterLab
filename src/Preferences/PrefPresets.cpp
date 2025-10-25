#include "Preferences.h"
namespace am {

PreferencePresetManager::PreferencePresetManager() {
	// Initialize preset manager
	LoadPresets();  // Load existing presets
}

void PreferencePresetManager::LoadPresets() {
	LOG("Loading preference presets");
	// In a real implementation, this would load presets from files
	// For now, just add a default preset
	PreferencesModel default_model;
	default_model.LoadDefaults();
	presets.Add("Default", default_model);
}

void PreferencePresetManager::SavePreset(const String& name, const PreferencesModel& model) {
	LOG("Saving preset: " + name);
	presets.GetAdd(name) = model;
}

void PreferencePresetManager::LoadPreset(const String& name, PreferencesModel& model) {
	LOG("Loading preset: " + name);
	if (presets.Find(name) >= 0) {
		model = presets.Get(name);
	}
}

void PreferencePresetManager::DeletePreset(const String& name) {
	LOG("Deleting preset: " + name);
	presets.RemoveKey(name);
}

Vector<String> PreferencePresetManager::GetPresetNames() const {
	Vector<String> names;
	for(int i = 0; i < presets.GetCount(); i++) {
		names.Add(presets.GetKey(i));
	}
	return names;
}

void PreferencePresetManager::CreatePreset(const String& name, const PreferencesModel& model) {
	SavePreset(name, model);
}

void PreferencePresetManager::UpdatePreset(const String& name, const PreferencesModel& model) {
	SavePreset(name, model);
}

void PreferencePresetManager::ReadPreset(const String& name, PreferencesModel& model) {
	LoadPreset(name, model);
}

void PreferencePresetManager::SetMarkedOnly(bool marked_only) {
	this->marked_only = marked_only;
}

bool PreferencePresetManager::IsMarkedOnly() const {
	return marked_only;
}

}