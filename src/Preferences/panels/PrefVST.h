#ifndef _Preferences_PrefVST_h_
#define _Preferences_PrefVST_h_

#include "../Preferences.h"

namespace am {

class PrefVST : public PreferencesPane {
public:
	typedef PrefVST CLASSNAME;
	PrefVST();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, Vector<bool>& changed) override;
	
private:
	void InitScanningSection();
	void InitProcessingSection();
	void InitCompatibilitySection();
	void InitConnectionBehaviorSection();
	void InitPluginManagementSection();
	void InitPerformanceSection();
	void InitControlRoomSection();
};

}

#endif