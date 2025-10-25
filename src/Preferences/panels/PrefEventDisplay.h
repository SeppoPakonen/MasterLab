#ifndef _Preferences_PrefEventDisplay_h_
#define _Preferences_PrefEventDisplay_h_

#include "PrefUI.h"
using namespace Upp;

namespace am {

class PrefEventDisplayGeneral : public PreferencesPane {
public:
	typedef PrefEventDisplayGeneral CLASSNAME;
	PrefEventDisplayGeneral();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, BitSet& changed) override;

private:
	void InitControls();

	// Controls for Event Display/General preferences
	Option show_event_names;
	Option transparent_events;
	Option show_data_small_heights;
	Option colorize_event_background;
};

}

#endif