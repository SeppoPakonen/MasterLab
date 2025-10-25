#ifndef _Preferences_PrefStore_h_
#define _Preferences_PrefStore_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "PrefModel.h"
using namespace Upp;

namespace am {

class PreferencesStore {
public:
	PreferencesStore();
	
	// Basic persistence
	bool Load(PreferencesModel& model);
	bool Save(const PreferencesModel& model);
	
	// Preset management
	bool LoadPreset(const String& name, PreferencesModel& model);
	bool SavePreset(const String& name, const PreferencesModel& model);
	bool DeletePreset(const String& name);
	Vector<String> GetPresetNames() const;
	
	// Marked-only store
	bool ApplyFrom(const PreferencesModel& src, const BitSet& changed, PreferencesModel& dest);
	
	// Migration
	void Migrate(int fromVersion, int toVersion, PreferencesModel& model);
	
	// File paths
	void SetConfigPath(const String& path) { config_path = path; }
	String GetConfigPath() const { return config_path; }
	
private:
	String config_path;
	
	// Internal helper methods
	String GetPreferencesFile() const;
	String GetPresetFile(const String& name) const;
};

}

#endif