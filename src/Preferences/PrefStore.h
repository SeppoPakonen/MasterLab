#ifndef _Preferences_PrefStore_h_
#define _Preferences_PrefStore_h_

#include <Core/Core.h>
#include "PrefModel.h"
using namespace Upp;

namespace am {

class PreferencesStore {
public:
	PreferencesStore();
	
	void Load(PreferencesModel& model);
	void Save(const PreferencesModel& model);
	void Migrate(PreferencesModel& model);  // For handling version changes
	
private:
	// For Ini/Json storage
	ValueMap data;
};

}

#endif