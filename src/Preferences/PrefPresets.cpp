#include "Preferences.h"
namespace am {

PreferencePresetManager::PreferencePresetManager() {
	presets_directory = ConfigFile("presets");
	EnsureDirectory(presets_directory);
}

bool PreferencePresetManager::CreatePreset(const String& name, const PreferencesModel& model) {
	LOG("Creating preset: " + name);
	// In a real implementation, this would save the model to a preset file
	// For now, we'll just use the standard store functionality
	PreferencesStore store;
	return store.SavePreset(name, model);
}

bool PreferencePresetManager::LoadPreset(const String& name, PreferencesModel& model) {
	LOG("Loading preset: " + name);
	// In a real implementation, this would load the model from a preset file
	// For now, we'll just use the standard store functionality
	PreferencesStore store;
	return store.LoadPreset(name, model);
}

bool PreferencePresetManager::UpdatePreset(const String& name, const PreferencesModel& model) {
	LOG("Updating preset: " + name);
	// In a real implementation, this would update an existing preset
	// For now, we'll just use the standard store functionality to save again
	PreferencesStore store;
	return store.SavePreset(name, model);
}

bool PreferencePresetManager::DeletePreset(const String& name) {
	LOG("Deleting preset: " + name);
	// In a real implementation, this would delete the preset file
	// For now, we'll just use the standard store functionality
	PreferencesStore store;
	return store.DeletePreset(name);
}

Vector<String> PreferencePresetManager::GetPresetNames() const {
	LOG("Getting preset names");
	// In a real implementation, this would scan the presets directory
	// For now, we'll just use the standard store functionality
	PreferencesStore store;
	return store.GetPresetNames();
}

bool PreferencePresetManager::SaveMarkedOnly(const String& name, const PreferencesModel& model, const BitSet& changed) {
	LOG("Saving marked-only preset: " + name);
	// This would save only the preferences that are marked as changed
	PreferencesStore store;
	return store.ApplyFrom(model, changed, const_cast<PreferencesModel&>(model));
}

bool PreferencePresetManager::ApplyPreset(const String& name, PreferencesModel& model) {
	LOG("Applying preset: " + name);
	return LoadPreset(name, model);
}

}