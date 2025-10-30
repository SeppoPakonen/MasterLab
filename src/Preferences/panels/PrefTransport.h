#ifndef _Preferences_PrefTransport_h_
#define _Preferences_PrefTransport_h_

#include "../Preferences.h"

namespace am {

class PrefTransport : public PreferencesPane {
public:
	typedef PrefTransport CLASSNAME;
	PrefTransport();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Upp::Vector<bool>& changed) override;
	
private:
	void InitDisplaySection();
	void InitBehaviorSection();
	void InitAdvancedBehaviorSection();
	void InitScrubbingSection();
};

}

#endif