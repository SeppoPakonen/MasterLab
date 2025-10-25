#ifndef _Preferences_PrefPresets_h_
#define _Preferences_PrefPresets_h_

#include <Core/Core.h>
#include "PrefModel.h"
using namespace Upp;

namespace am {

class PreferencePresetManager {
public:
	PreferencePresetManager();
	
	// Preset CRUD operations
	bool CreatePreset(const String& name, const PreferencesModel& model);
	bool LoadPreset(const String& name, PreferencesModel& model);
	bool UpdatePreset(const String& name, const PreferencesModel& model);
	bool DeletePreset(const String& name);
	Vector<String> GetPresetNames() const;
	
	// "Store marked only" functionality
	bool SaveMarkedOnly(const String& name, const PreferencesModel& model, const BitSet& changed);
	
	// Apply preset
	bool ApplyPreset(const String& name, PreferencesModel& model);
	
private:
	String presets_directory;
};

}

#endif