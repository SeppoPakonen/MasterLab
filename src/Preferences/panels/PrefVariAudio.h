#ifndef _Preferences_PrefVariAudio_h_
#define _Preferences_PrefVariAudio_h_

#include "../Preferences.h"

namespace am {

class PrefVariAudio : public PreferencesPane {
public:
	typedef PrefVariAudio CLASSNAME;
	PrefVariAudio();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Vector<bool>& changed) override;
	
private:
	void InitAnalysisSection();
	void InitProcessingSection();
	void InitDisplaySection();
	void InitWarningsSection();
};

}

#endif