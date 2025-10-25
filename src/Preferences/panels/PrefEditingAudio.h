#ifndef _Preferences_PrefEditingAudio_h_
#define _Preferences_PrefEditingAudio_h_

#include "PrefUI.h"
using namespace Upp;

namespace am {

class PrefEditingAudio : public PreferencesPane {
public:
	typedef PrefEditingAudio CLASSNAME;
	PrefEditingAudio();
	virtual void Init(PreferencesModel& model) override;
	virtual void Load(const PreferencesModel& model) override;
	virtual void Store(PreferencesModel& model, BitSet& changed) override;

private:
	void InitControls();

	// Controls for Editing/Audio preferences
	Option treat_muted_as_deleted;
	Option use_mouse_wheel_for_volume;
	Option hitpoints_have_qpoints;
	Option remove_regions_on_offline_processes;
	Option snap_to_zero_crossing;
	DropList time_stretch_algorithm;
	DropList import_audio_behavior;
	Option copy_to_working_dir;
	Option convert_and_copy;
	Option split_multichannel_files;
	DropList import_version_behavior;
};

}

#endif