#ifndef _Preferences_PrefPresets_h_
#define _Preferences_PrefPresets_h_

#include <Core/Core.h>
#include "PrefModel.h"
using namespace Upp;

namespace am {

class PreferencePresetManager {
public:
	PreferencePresetManager();
	
	void LoadPresets();
	void SavePreset(const String& name, const PreferencesModel& model);
	void LoadPreset(const String& name, PreferencesModel& model);
	void DeletePreset(const String& name);
	Vector<String> GetPresetNames() const;
	
	// CRUD operations for presets
	void CreatePreset(const String& name, const PreferencesModel& model);
	void UpdatePreset(const String& name, const PreferencesModel& model);
	void ReadPreset(const String& name, PreferencesModel& model);
	void DeletePreset(const String& name);
	
	// Functionality for "store marked only"
	void SetMarkedOnly(bool marked_only);
	bool IsMarkedOnly() const;
	
private:
	HashMap<String, PreferencesModel> presets;
	bool marked_only = false;
};

}

#endif