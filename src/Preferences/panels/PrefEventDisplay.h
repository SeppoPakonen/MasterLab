#ifndef _Preferences_PrefEventDisplay_h_
#define _Preferences_PrefEventDisplay_h_

#include "../Preferences.h"

namespace am {

class PrefEventDisplay : public PreferencesPane {
public:
	typedef PrefEventDisplay CLASSNAME;
	PrefEventDisplay();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Upp::Vector<bool>& changed) override;
	
private:
	void InitGeneralSection();
	void InitDisplaySection();
	void InitZoomSection();
	void InitTrackHeightSection();
	void InitLaneDisplaySection();
	
	// Data structure to hold UI controls
	struct Data;
	Data* data;
};

}

#endif