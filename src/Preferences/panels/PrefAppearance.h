#ifndef _Preferences_PrefAppearance_h_
#define _Preferences_PrefAppearance_h_

#include "PrefUI.h"
using namespace Upp;

namespace am {

class PrefAppearance : public PreferencesPane {
public:
	typedef PrefAppearance CLASSNAME;
	PrefAppearance();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, BitSet& changed) override;
	
private:
	void InitGeneralSection();
	void InitMetersSection();
	void InitWorkAreaSection();
	
	// Controls for Appearance/General
	Option general_meters_option;
	Option general_work_area_option;
	
	// Controls for Appearance/Meters
	StaticRect preview_vu_rect;
	// VUMarkerEditor would be implemented here
	
	// Controls for Appearance/Work Area
	// GridColorEditor would be implemented here
	
};

}

#endif