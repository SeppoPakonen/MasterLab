#include "PrefVariAudio.h"

namespace am {

// Define member controls for PrefVariAudio
struct PrefVariAudio::Data {
	// Analysis section controls
	LabeledOption* auto_analyze = nullptr;
	LabeledSlider* analysis_granularity = nullptr;
	
	// Processing section controls
	LabeledOption* preserve_formants = nullptr;
	LabeledOption* adaptive_pitch = nullptr;
	
	// Display section controls
	LabeledOption* show_analysis = nullptr;
	LabeledOption* color_by_pitch = nullptr;
	
	// Warnings section controls
	LabeledOption* inhibit_sample_warn = nullptr;
	LabeledOption* inhibit_offline_warn = nullptr;
};

PrefVariAudio::PrefVariAudio() {
	data = new Data();
	
	// Initialize UI sections
	InitAnalysisSection();
	InitProcessingSection();
	InitDisplaySection();
	InitWarningsSection();
}

void PrefVariAudio::Init(PreferencesModel& model) {
	// Initialize the panel with model data
}

void PrefVariAudio::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const VariAudioPrefs& prefs = model.GetVariAudio();
	
	if(data->auto_analyze) {
		data->auto_analyze->SetData(prefs.auto_analyze_on_import);
	}
	if(data->analysis_granularity) {
		data->analysis_granularity->SetData(prefs.analysis_granularity);
	}
	if(data->preserve_formants) {
		data->preserve_formants->SetData(prefs.preserve_formants);
	}
	if(data->adaptive_pitch) {
		data->adaptive_pitch->SetData(prefs.adaptive_pitch_tracking);
	}
	if(data->show_analysis) {
		data->show_analysis->SetData(prefs.show_analysis_overlay);
	}
	if(data->color_by_pitch) {
		data->color_by_pitch->SetData(prefs.color_by_pitch_confidence);
	}
	if(data->inhibit_sample_warn) {
		data->inhibit_sample_warn->SetData(prefs.inhibit_warn_change_sample);
	}
	if(data->inhibit_offline_warn) {
		data->inhibit_offline_warn->SetData(prefs.inhibit_warn_offline_process);
	}
}

void PrefVariAudio::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	VariAudioPrefs& prefs = model.GetVariAudio();
	
	// Check if values have changed and update the model
	if(data->auto_analyze) {
		bool new_val = data->auto_analyze->GetData();
		changed.Add(new_val != prefs.auto_analyze_on_import);
		prefs.auto_analyze_on_import = new_val;
	}
	if(data->analysis_granularity) {
		int new_val = data->analysis_granularity->GetData();
		changed.Add(new_val != prefs.analysis_granularity);
		prefs.analysis_granularity = new_val;
	}
	if(data->preserve_formants) {
		bool new_val = data->preserve_formants->GetData();
		changed.Add(new_val != prefs.preserve_formants);
		prefs.preserve_formants = new_val;
	}
	if(data->adaptive_pitch) {
		bool new_val = data->adaptive_pitch->GetData();
		changed.Add(new_val != prefs.adaptive_pitch_tracking);
		prefs.adaptive_pitch_tracking = new_val;
	}
	if(data->show_analysis) {
		bool new_val = data->show_analysis->GetData();
		changed.Add(new_val != prefs.show_analysis_overlay);
		prefs.show_analysis_overlay = new_val;
	}
	if(data->color_by_pitch) {
		bool new_val = data->color_by_pitch->GetData();
		changed.Add(new_val != prefs.color_by_pitch_confidence);
		prefs.color_by_pitch_confidence = new_val;
	}
	if(data->inhibit_sample_warn) {
		bool new_val = data->inhibit_sample_warn->GetData();
		changed.Add(new_val != prefs.inhibit_warn_change_sample);
		prefs.inhibit_warn_change_sample = new_val;
	}
	if(data->inhibit_offline_warn) {
		bool new_val = data->inhibit_offline_warn->GetData();
		changed.Add(new_val != prefs.inhibit_warn_offline_process);
		prefs.inhibit_warn_offline_process = new_val;
	}
}

void PrefVariAudio::InitAnalysisSection() {
	// Initialize analysis settings
	LabelBox* analysis_box = new LabelBox("Analysis");
	
	data->auto_analyze = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Auto-analyze on Import", true));
	analysis_box->Add(data->auto_analyze->SizePos());
	
	data->analysis_granularity = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Analysis Granularity", 0, 100, 50));
	analysis_box->Add(data->analysis_granularity->SizePos());
	
	Add(analysis_box->SizePos());
}

void PrefVariAudio::InitProcessingSection() {
	// Initialize processing settings
	LabelBox* processing_box = new LabelBox("Processing");
	
	data->preserve_formants = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Preserve Formants", true));
	processing_box->Add(data->preserve_formants->SizePos());
	
	data->adaptive_pitch = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Adaptive Pitch Tracking", true));
	processing_box->Add(data->adaptive_pitch->SizePos());
	
	Add(processing_box->SizePos());
}

void PrefVariAudio::InitDisplaySection() {
	// Initialize display settings
	LabelBox* display_box = new LabelBox("Display");
	
	data->show_analysis = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Analysis Overlay", true));
	display_box->Add(data->show_analysis->SizePos());
	
	data->color_by_pitch = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Color by Pitch Confidence", true));
	display_box->Add(data->color_by_pitch->SizePos());
	
	Add(display_box->SizePos());
}

void PrefVariAudio::InitWarningsSection() {
	// Initialize warnings settings
	LabelBox* warnings_box = new LabelBox("Warnings");
	
	data->inhibit_sample_warn = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Inhibit Sample Change Warning", false));
	warnings_box->Add(data->inhibit_sample_warn->SizePos());
	
	data->inhibit_offline_warn = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Inhibit Offline Process Warning", false));
	warnings_box->Add(data->inhibit_offline_warn->SizePos());
	
	Add(warnings_box->SizePos());
}

REGISTER_PREF_PANEL("VariAudio", "General", PrefVariAudio)

}