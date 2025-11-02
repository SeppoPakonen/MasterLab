#ifndef _Preferences_PrefAppearance_h_
#define _Preferences_PrefAppearance_h_

#include "../Preferences.h"

namespace am {

class PrefAppearance : public PreferencesPane {
public:
	typedef PrefAppearance CLASSNAME;
	PrefAppearance();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Upp::Vector<bool>& changed) override;
	
private:
	void InitGeneralSection();
	void InitMetersSection();
	void InitWorkAreaSection();
	
	// Data structure to hold UI controls
	struct Data;
	Data* data;
};

}

#endif