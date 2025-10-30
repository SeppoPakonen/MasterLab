#ifndef _Preferences_PrefMediaBay_h_
#define _Preferences_PrefMediaBay_h_

#include "../Preferences.h"

namespace am {

class PrefMediaBay : public PreferencesPane {
public:
	typedef PrefMediaBay CLASSNAME;
	PrefMediaBay();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Upp::Vector<bool>& changed) override;
	
private:
	void InitDisplaySection();
	void InitSearchSection();
	void InitOrganizationSection();
	void InitAdvancedSection();
};

}

#endif