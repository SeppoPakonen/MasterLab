#ifndef _Preferences_PrefMIDI_h_
#define _Preferences_PrefMIDI_h_

#include "PrefUI.h"
using namespace Upp;

namespace am {

class PrefMIDIGeneral : public PreferencesPane {
public:
	typedef PrefMIDIGeneral CLASSNAME;
	PrefMIDIGeneral();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, BitSet& changed) override;

private:
	void InitControls();

	// Controls for MIDI/General preferences
	Option midi_thru_active;
	Option reset_on_stop;
	IntSpin length_adjust_ticks;
	Option insert_reset_after_record;
	Option audition_through_inserts;
	IntSpin max_feedback_ms;
};

}

#endif