#ifndef _Preferences_PrefEditingAudio_h_
#define _Preferences_PrefEditingAudio_h_

#include "../Preferences.h"

namespace am {

class PrefEditingAudio : public PreferencesPane {
public:
	typedef PrefEditingAudio CLASSNAME;
	PrefEditingAudio();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Upp::Vector<bool>& changed) override;
	
private:
	void InitControls();
};

}

#endif