#include "PrefVST.h"

namespace am {

// Define member controls for PrefVST
struct PrefVST::Data {
	// Scanning section controls
	LabeledOption* scan_on_startup = nullptr;
	LabeledOption* scan_periodically = nullptr;
	
	// Processing section controls
	LabeledOption* separate_thread = nullptr;
	LabeledSlider* buffer_size = nullptr;
	
	// Compatibility section controls
	LabeledOption* enable_bridge = nullptr;
	LabeledOption* compatibility_mode = nullptr;
	
	// Connection behavior section controls
	LabeledOption* connect_sends_auto = nullptr;
	LabeledOption* instr_use_auto = nullptr;
	LabeledOption* mute_pre_send = nullptr;
	
	// Plugin management section controls
	LabeledOption* warn_before_remove = nullptr;
	LabeledOption* open_after_load = nullptr;
	
	// Performance section controls
	LabeledSlider* peak_hold = nullptr;
	LabeledSlider* slow_fallback = nullptr;
	
	// Control room section controls
	LabeledOption* show_volume = nullptr;
	LabeledOption* disable_talkback = nullptr;
};

PrefVST::PrefVST() {
	data = new Data();
	
	// Initialize UI sections
	InitScanningSection();
	InitProcessingSection();
	InitCompatibilitySection();
	InitConnectionBehaviorSection();
	InitPluginManagementSection();
	InitPerformanceSection();
	InitControlRoomSection();
}

void PrefVST::Init(PreferencesModel& model) {
	// Initialize the panel with model data
}

void PrefVST::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const VSTPrefs& prefs = model.GetVST();
	
	if(data->scan_on_startup) {
		data->scan_on_startup->SetData(prefs.scan_vst_on_startup);
	}
	if(data->scan_periodically) {
		data->scan_periodically->SetData(prefs.scan_vst_periodically);
	}
	if(data->separate_thread) {
		data->separate_thread->SetData(prefs.process_vst_in_separate_thread);
	}
	if(data->buffer_size) {
		data->buffer_size->SetData(prefs.vst_buffer_size);
	}
	if(data->enable_bridge) {
		data->enable_bridge->SetData(prefs.enable_vst_bridge);
	}
	if(data->compatibility_mode) {
		data->compatibility_mode->SetData(prefs.use_vst_compatibility_mode);
	}
	if(data->connect_sends_auto) {
		data->connect_sends_auto->SetData(prefs.connect_sends_auto);
	}
	if(data->instr_use_auto) {
		data->instr_use_auto->SetData(prefs.instr_use_automation_rw_all);
	}
	if(data->mute_pre_send) {
		data->mute_pre_send->SetData(prefs.mute_pre_send_on_mute);
	}
	if(data->warn_before_remove) {
		data->warn_before_remove->SetData(prefs.warn_before_remove_modified);
	}
	if(data->open_after_load) {
		data->open_after_load->SetData(prefs.open_editor_after_load);
	}
	if(data->peak_hold) {
		data->peak_hold->SetData(prefs.peak_hold_ms);
	}
	if(data->slow_fallback) {
		data->slow_fallback->SetData(prefs.slow_fallback_dbps);
	}
	if(data->show_volume) {
		data->show_volume->SetData(prefs.show_volume_in_transport);
	}
	if(data->disable_talkback) {
		data->disable_talkback->SetData(prefs.disable_talkback);
	}
}

void PrefVST::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	VSTPrefs& prefs = model.GetVST();
	
	// Check if values have changed and update the model
	if(data->scan_on_startup) {
		bool new_val = data->scan_on_startup->GetData();
		changed.Add(new_val != prefs.scan_vst_on_startup);
		prefs.scan_vst_on_startup = new_val;
	}
	if(data->scan_periodically) {
		bool new_val = data->scan_periodically->GetData();
		changed.Add(new_val != prefs.scan_vst_periodically);
		prefs.scan_vst_periodically = new_val;
	}
	if(data->separate_thread) {
		bool new_val = data->separate_thread->GetData();
		changed.Add(new_val != prefs.process_vst_in_separate_thread);
		prefs.process_vst_in_separate_thread = new_val;
	}
	if(data->buffer_size) {
		int new_val = data->buffer_size->GetData();
		changed.Add(new_val != prefs.vst_buffer_size);
		prefs.vst_buffer_size = new_val;
	}
	if(data->enable_bridge) {
		bool new_val = data->enable_bridge->GetData();
		changed.Add(new_val != prefs.enable_vst_bridge);
		prefs.enable_vst_bridge = new_val;
	}
	if(data->compatibility_mode) {
		bool new_val = data->compatibility_mode->GetData();
		changed.Add(new_val != prefs.use_vst_compatibility_mode);
		prefs.use_vst_compatibility_mode = new_val;
	}
	if(data->connect_sends_auto) {
		bool new_val = data->connect_sends_auto->GetData();
		changed.Add(new_val != prefs.connect_sends_auto);
		prefs.connect_sends_auto = new_val;
	}
	if(data->instr_use_auto) {
		bool new_val = data->instr_use_auto->GetData();
		changed.Add(new_val != prefs.instr_use_automation_rw_all);
		prefs.instr_use_automation_rw_all = new_val;
	}
	if(data->mute_pre_send) {
		bool new_val = data->mute_pre_send->GetData();
		changed.Add(new_val != prefs.mute_pre_send_on_mute);
		prefs.mute_pre_send_on_mute = new_val;
	}
	if(data->warn_before_remove) {
		bool new_val = data->warn_before_remove->GetData();
		changed.Add(new_val != prefs.warn_before_remove_modified);
		prefs.warn_before_remove_modified = new_val;
	}
	if(data->open_after_load) {
		bool new_val = data->open_after_load->GetData();
		changed.Add(new_val != prefs.open_editor_after_load);
		prefs.open_editor_after_load = new_val;
	}
	if(data->peak_hold) {
		int new_val = data->peak_hold->GetData();
		changed.Add(new_val != prefs.peak_hold_ms);
		prefs.peak_hold_ms = new_val;
	}
	if(data->slow_fallback) {
		int new_val = data->slow_fallback->GetData();
		changed.Add(new_val != prefs.slow_fallback_dbps);
		prefs.slow_fallback_dbps = new_val;
	}
	if(data->show_volume) {
		bool new_val = data->show_volume->GetData();
		changed.Add(new_val != prefs.show_volume_in_transport);
		prefs.show_volume_in_transport = new_val;
	}
	if(data->disable_talkback) {
		bool new_val = data->disable_talkback->GetData();
		changed.Add(new_val != prefs.disable_talkback);
		prefs.disable_talkback = new_val;
	}
}

void PrefVST::InitScanningSection() {
	// Initialize scanning settings
	LabelBox* scanning_box = new LabelBox("Scanning");
	
	data->scan_on_startup = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Scan VST on Startup", true));
	scanning_box->Add(data->scan_on_startup->SizePos());
	
	data->scan_periodically = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Scan VST Periodically", false));
	scanning_box->Add(data->scan_periodically->SizePos());
	
	Add(scanning_box->SizePos());
}

void PrefVST::InitProcessingSection() {
	// Initialize processing settings
	LabelBox* processing_box = new LabelBox("Processing");
	
	data->separate_thread = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Process VST in Separate Thread", true));
	processing_box->Add(data->separate_thread->SizePos());
	
	data->buffer_size = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("VST Buffer Size (samples)", 64, 2048, 512));
	processing_box->Add(data->buffer_size->SizePos());
	
	Add(processing_box->SizePos());
}

void PrefVST::InitCompatibilitySection() {
	// Initialize compatibility settings
	LabelBox* compatibility_box = new LabelBox("Compatibility");
	
	data->enable_bridge = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Enable VST Bridge", false));
	compatibility_box->Add(data->enable_bridge->SizePos());
	
	data->compatibility_mode = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Use VST Compatibility Mode", false));
	compatibility_box->Add(data->compatibility_mode->SizePos());
	
	Add(compatibility_box->SizePos());
}

void PrefVST::InitConnectionBehaviorSection() {
	// Initialize connection behavior settings
	LabelBox* connection_box = new LabelBox("Connection Behavior");
	
	data->connect_sends_auto = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Connect Sends Auto", true));
	connection_box->Add(data->connect_sends_auto->SizePos());
	
	data->instr_use_auto = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Instrument Use Automation RW All", true));
	connection_box->Add(data->instr_use_auto->SizePos());
	
	data->mute_pre_send = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Mute Pre Send on Mute", true));
	connection_box->Add(data->mute_pre_send->SizePos());
	
	Add(connection_box->SizePos());
}

void PrefVST::InitPluginManagementSection() {
	// Initialize plugin management settings
	LabelBox* plugin_mgmt_box = new LabelBox("Plugin Management");
	
	data->warn_before_remove = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Warn Before Remove Modified", true));
	plugin_mgmt_box->Add(data->warn_before_remove->SizePos());
	
	data->open_after_load = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Open Editor After Load", true));
	plugin_mgmt_box->Add(data->open_after_load->SizePos());
	
	Add(plugin_mgmt_box->SizePos());
}

void PrefVST::InitPerformanceSection() {
	// Initialize performance settings
	LabelBox* performance_box = new LabelBox("Performance");
	
	data->peak_hold = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Peak Hold (ms)", 1000, 30000, 5000));
	performance_box->Add(data->peak_hold->SizePos());
	
	data->slow_fallback = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Slow Fallback DBPS", 1, 1000, 10));
	performance_box->Add(data->slow_fallback->SizePos());
	
	Add(performance_box->SizePos());
}

void PrefVST::InitControlRoomSection() {
	// Initialize control room settings
	LabelBox* control_room_box = new LabelBox("Control Room");
	
	data->show_volume = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Volume in Transport", true));
	control_room_box->Add(data->show_volume->SizePos());
	
	data->disable_talkback = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Disable Talkback", false));
	control_room_box->Add(data->disable_talkback->SizePos());
	
	Add(control_room_box->SizePos());
}

REGISTER_PREF_PANEL("VST", "General", PrefVST)

}