#ifndef _Preferences_PrefScores_h_
#define _Preferences_PrefScores_h_

#include "../Preferences.h"

namespace am {

class PrefScores : public PreferencesPane {
public:
	typedef PrefScores CLASSNAME;
	PrefScores();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Vector<bool>& changed) override;
	
private:
	void InitDisplaySection();
	void InitNotationSection();
	void InitPlaybackSection();
};

}

#endif