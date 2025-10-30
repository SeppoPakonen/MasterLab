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
	void SavePreset(const Upp::String& name, const PreferencesModel& model);
	void LoadPreset(const Upp::String& name, PreferencesModel& model);
	void DeletePreset(const Upp::String& name);
	Upp::Vector<Upp::String> GetPresetNames() const;
	
	// CRUD operations for presets
	void CreatePreset(const Upp::String& name, const PreferencesModel& model);
	void UpdatePreset(const Upp::String& name, const PreferencesModel& model);
	void ReadPreset(const Upp::String& name, PreferencesModel& model);
	
	// Functionality for "store marked only"
	void SetMarkedOnly(bool marked_only);
	bool IsMarkedOnly() const;
	
private:
	VectorMap<Upp::String, PreferencesModel> presets;
	bool marked_only = false;
};

}

#endif