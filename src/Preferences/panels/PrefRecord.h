#ifndef _Preferences_PrefRecord_h_
#define _Preferences_PrefRecord_h_

#include "../Preferences.h"

namespace am {

class PrefRecord : public PreferencesPane {
public:
	typedef PrefRecord CLASSNAME;
	PrefRecord();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Upp::Vector<bool>& changed) override;
	
private:
	void InitInputMonitoringSection();
	void InitCountInSection();
	void InitPunchInOutSection();
	void InitRecordingBehaviorSection();
	void InitFileInfoSection();
	void InitBehaviorSection();
};

}

#endif