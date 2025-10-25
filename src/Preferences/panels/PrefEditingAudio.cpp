#include "../Preferences.h"
namespace am {

PrefEditingAudio::PrefEditingAudio() {
	Title("Editing/Audio");
	
	// Initialize the controls for Editing/Audio preferences
	InitControls();
}

void PrefEditingAudio::InitControls() {
	// Create and add the controls to the layout
	Add(treat_muted_as_deleted.VSizePos().HSizePos());
	treat_muted_as_deleted.SetLabel("Treat Muted Audio Events like Deleted");
	
	Add(use_mouse_wheel_for_volume.VSizePos().HSizePos());
	use_mouse_wheel_for_volume.SetLabel("Use Mouse Wheel for Event Volume and Fades");
	
	Add(hitpoints_have_qpoints.VSizePos().HSizePos());
	hitpoints_have_qpoints.SetLabel("Hitpoints have Q-Points");
	
	Add(remove_regions_on_offline_processes.VSizePos().HSizePos());
	remove_regions_on_offline_processes.SetLabel("Remove Regions/Markers on all Offline Processes");
	
	Add(snap_to_zero_crossing.VSizePos().HSizePos());
	snap_to_zero_crossing.SetLabel("Snap to Zero Crossing");
	
	// Time stretch algorithm drop list
	time_stretch_algorithm.Add("MPEX 4");
	time_stretch_algorithm.Add("Realtime");
	time_stretch_algorithm.SetIndex(1); // Default to "Realtime"
	
	Add(time_stretch_algorithm.VSizePos().HSizePos());
	time_stretch_algorithm.SetLabel("Time Stretch Tool Algorithm");
	
	// Import audio behavior
	import_audio_behavior.Add("Open Options Dialog");
	import_audio_behavior.Add("Use Settings");
	import_audio_behavior.SetIndex(0); // Default to "Open Options Dialog"
	
	Add(import_audio_behavior.VSizePos().HSizePos());
	import_audio_behavior.SetLabel("On Import Audio Files");
	
	// Nested options based on import behavior
	Add(copy_to_working_dir.VSizePos().HSizePos());
	copy_to_working_dir.SetLabel("Copy Files to Working Directory");
	
	Add(convert_and_copy.VSizePos().HSizePos());
	convert_and_copy.SetLabel("Convert and Copy to Project If Needed");
	
	Add(split_multichannel_files.VSizePos().HSizePos());
	split_multichannel_files.SetLabel("Split multi-channel files");
	
	// Import version behavior
	import_version_behavior.Add("Open Options Dialog");
	import_version_behavior.Add("Assume New Versions");
	import_version_behavior.Add("Assume Skipping");
	import_version_behavior.SetIndex(0);
	
	Add(import_version_behavior.VSizePos().HSizePos());
	import_version_behavior.SetLabel("Import Behavior");
	
	// Set up event handlers to enable/disable dependent controls
	import_audio_behavior.WhenAction = [this]() {
		bool use_settings = import_audio_behavior.GetIndex() == 1;
		copy_to_working_dir.Enable(use_settings);
		convert_and_copy.Enable(use_settings);
		split_multichannel_files.Enable(use_settings);
	};
	
	// Initially disable the dependent controls
	copy_to_working_dir.Enable(false);
	convert_and_copy.Enable(false);
	split_multichannel_files.Enable(false);
}

void PrefEditingAudio::Init(PreferencesModel& model) {
	// The control initialization is already done in the constructor
	Load(model);
}

void PrefEditingAudio::Load(const PreferencesModel& model) {
	// Load values from the model into the controls
	const EditingPrefs& editing = model.GetEditing();
	
	// Load the audio-specific values from the model
	treat_muted_as_deleted = editing.treat_muted_as_deleted;
	use_mouse_wheel_for_volume = editing.use_mouse_wheel_for_volume;
	hitpoints_have_qpoints = editing.hitpoints_have_qpoints;
	remove_regions_on_offline_processes = editing.remove_regions_on_offline_processes;
	snap_to_zero_crossing = editing.snap_to_zero_crossing;
	
	// Set the time stretch algorithm
	if (editing.time_stretch_algorithm == "mplex_4") {
		time_stretch_algorithm.SetIndex(0);
	} else {
		time_stretch_algorithm.SetIndex(1); // Default to "Realtime"
	}
	
	// Set the import audio behavior
	if (editing.import_audio_behavior == "use_settings") {
		import_audio_behavior.SetIndex(1);
	} else {
		import_audio_behavior.SetIndex(0); // Default to "Open Options Dialog"
	}
	
	// Set the import version behavior
	if (editing.import_version_behavior == "assume_new") {
		import_version_behavior.SetIndex(1);
	} else if (editing.import_version_behavior == "assume_skipping") {
		import_version_behavior.SetIndex(2);
	} else {
		import_version_behavior.SetIndex(0); // Default to "Open Options Dialog"
	}
	
	// Set dependent controls based on import behavior
	bool use_settings = editing.import_audio_behavior == "use_settings";
	copy_to_working_dir.Enable(use_settings);
	convert_and_copy.Enable(use_settings);
	split_multichannel_files.Enable(use_settings);
	
	copy_to_working_dir = editing.copy_to_working_dir;
	convert_and_copy = editing.convert_and_copy;
	split_multichannel_files = editing.split_multichannel_files;
}

void PrefEditingAudio::Store(PreferencesModel& model, BitSet& changed) {
	// Store values from the controls to the model
	EditingPrefs& editing = model.GetEditing();
	
	// Store the audio-specific values to the model
	editing.treat_muted_as_deleted = treat_muted_as_deleted;
	editing.use_mouse_wheel_for_volume = use_mouse_wheel_for_volume;
	editing.hitpoints_have_qpoints = hitpoints_have_qpoints;
	editing.remove_regions_on_offline_processes = remove_regions_on_offline_processes;
	editing.snap_to_zero_crossing = snap_to_zero_crossing;
	
	// Store time stretch algorithm
	editing.time_stretch_algorithm = (time_stretch_algorithm.GetIndex() == 0) ? "mplex_4" : "realtime";
	
	// Store import audio behavior
	editing.import_audio_behavior = (import_audio_behavior.GetIndex() == 1) ? "use_settings" : "open_options";
	
	// Store import version behavior
	switch (import_version_behavior.GetIndex()) {
		case 1:
			editing.import_version_behavior = "assume_new";
			break;
		case 2:
			editing.import_version_behavior = "assume_skipping";
			break;
		default:
			editing.import_version_behavior = "open_options";
			break;
	}
	
	// Store dependent values
	editing.copy_to_working_dir = copy_to_working_dir;
	editing.convert_and_copy = convert_and_copy;
	editing.split_multichannel_files = split_multichannel_files;
	
	// The "changed" BitSet would be used to track which preferences were modified
	LOG("Storing Editing/Audio preferences");
}

// Register this panel with the registry
REGISTER_PREF_PANEL("Editing", "Audio", PrefEditingAudio)

}