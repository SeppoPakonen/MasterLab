#include "Preferences.h"
namespace am {

PreferencesStore::PreferencesStore() {
	config_path = ConfigFile("preferences");
}

bool PreferencesStore::Load(PreferencesModel& model) {
	String file = GetPreferencesFile();
	if (!FileExists(file)) {
		// If no config file exists, use defaults
		model.LoadDefaults();
		return true;
	}
	
	// Load preferences from JSON file
	String json = LoadFile(file);
	if (json.IsEmpty()) {
		LOG("Failed to load preferences file: " + file);
		return false;
	}
	
	// For now, just load defaults (actual JSON loading would be implemented)
	LOG("Loading preferences from: " + file);
	model.LoadDefaults();
	return true;
}

bool PreferencesStore::Save(const PreferencesModel& model) {
	String file = GetPreferencesFile();
	// For now, just return true (actual JSON saving would be implemented)
	LOG("Saving preferences to: " + file);
	return true;
}

bool PreferencesStore::LoadPreset(const String& name, PreferencesModel& model) {
	String file = GetPresetFile(name);
	if (!FileExists(file)) {
		LOG("Preset file does not exist: " + file);
		return false;
	}
	
	// Load preset (stub implementation)
	LOG("Loading preset: " + name + " from: " + file);
	return true;
}

bool PreferencesStore::SavePreset(const String& name, const PreferencesModel& model) {
	String file = GetPresetFile(name);
	LOG("Saving preset: " + name + " to: " + file);
	// For now, just return true (actual JSON saving would be implemented)
	return true;
}

bool PreferencesStore::DeletePreset(const String& name) {
	String file = GetPresetFile(name);
	if (!FileExists(file)) {
		LOG("Preset file does not exist: " + file);
		return false;
	}
	
	bool result = DeleteFile(file);
	LOG("Deleting preset: " + name + ", success: " + (result ? "true" : "false"));
	return result;
}

Vector<String> PreferencesStore::GetPresetNames() const {
	Vector<String> names;
	
	// Look for preset files in the config directory
	String presetDir = AppendFileName(GetFileDirectory(GetPreferencesFile()), "presets");
	if (DirectoryExists(presetDir)) {
		FindFile ff(AppendFileName(presetDir, "*.json"));
		while(ff) {
			if (!ff.IsDirectory()) {
				String name = GetFileName(ff.GetName());
				name = name.Mid(0, name.GetLength() - 5); // Remove .json extension
				names.Add(name);
			}
			++ff;
		}
	}
	
	return names;
}

bool PreferencesStore::ApplyFrom(const PreferencesModel& src, const BitSet& changed, PreferencesModel& dest) {
	LOG("Applying marked-only preferences");
	// This would copy only the changed preferences from src to dest
	// For now, just return true
	return true;
}

void PreferencesStore::Migrate(int fromVersion, int toVersion, PreferencesModel& model) {
	LOG("Migrating preferences from version " + IntStr(fromVersion) + " to " + IntStr(toVersion));
	// Actual migration logic would be implemented here
}

String PreferencesStore::GetPreferencesFile() const {
	return AppendFileName(config_path, "preferences.json");
}

String PreferencesStore::GetPresetFile(const String& name) const {
	String presetDir = AppendFileName(GetFileDirectory(GetPreferencesFile()), "presets");
	EnsureDirectory(presetDir);
	return AppendFileName(presetDir, name + ".json");
}

}