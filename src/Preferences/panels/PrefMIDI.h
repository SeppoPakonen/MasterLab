#ifndef _Preferences_PrefMIDI_h_
#define _Preferences_PrefMIDI_h_

#include "../Preferences.h"

namespace am {

class PrefMIDI : public PreferencesPane {
public:
	typedef PrefMIDI CLASSNAME;
	PrefMIDI();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Upp::Vector<bool>& changed) override;
	
private:
	void InitDefaultsSection();
	void InitBehaviorSection();
	void InitEditorSection();
	void InitRealtimeSection();
	void InitChaseSection();
	void InitTimingSection();
};

}

#endif