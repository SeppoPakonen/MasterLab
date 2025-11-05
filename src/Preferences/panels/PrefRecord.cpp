#include "PrefRecord.h"

namespace am {

// Define member controls for PrefRecord
struct PrefRecord::Data {
	// Input monitoring section controls
	LabeledOption* input_monitoring = nullptr;
	LabeledOption* software_monitoring = nullptr;
	
	// Count-in section controls
	LabeledOption* enable_count_in = nullptr;
	LabeledSlider* count_in_measures = nullptr;
	
	// Punch-in/out section controls
	LabeledOption* auto_punch_in = nullptr;
	LabeledOption* auto_punch_out = nullptr;
	LabeledOption* use_punch_points = nullptr;
	
	// Recording behavior section controls
	LabeledSlider* pre_record_seconds = nullptr;
	LabeledOption* create_images = nullptr;
	
	// File info section controls
	EditString* descriptor = nullptr;
	EditString* author = nullptr;
	EditString* reference = nullptr;
	
	// Behavior section controls
	LabeledOption* snap_parts = nullptr;
	LabeledOption* solo_record = nullptr;
};

PrefRecord::PrefRecord() {
	data = new Data();
	
	// Initialize UI sections
	InitInputMonitoringSection();
	InitCountInSection();
	InitPunchInOutSection();
	InitRecordingBehaviorSection();
	InitFileInfoSection();
	InitBehaviorSection();
}

void PrefRecord::Init(PreferencesModel& model) {
	// Initialize the panel with model data
}

void PrefRecord::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const RecordPrefs& prefs = model.GetRecord();
	
	if(data->input_monitoring) {
		data->input_monitoring->SetData(prefs.input_monitoring);
	}
	if(data->software_monitoring) {
		data->software_monitoring->SetData(prefs.software_monitoring);
	}
	if(data->enable_count_in) {
		data->enable_count_in->SetData(prefs.enable_count_in);
	}
	if(data->count_in_measures) {
		data->count_in_measures->SetData(prefs.count_in_measures);
	}
	if(data->auto_punch_in) {
		data->auto_punch_in->SetData(prefs.auto_punch_in);
	}
	if(data->auto_punch_out) {
		data->auto_punch_out->SetData(prefs.auto_punch_out);
	}
	if(data->use_punch_points) {
		data->use_punch_points->SetData(prefs.use_punch_points);
	}
	if(data->pre_record_seconds) {
		data->pre_record_seconds->SetData((int)(prefs.pre_record_seconds * 10)); // Convert to int for slider
	}
	if(data->create_images) {
		data->create_images->SetData(prefs.create_images_during_record);
	}
	if(data->descriptor) {
		data->descriptor->SetText(prefs.descriptor);
	}
	if(data->author) {
		data->author->SetText(prefs.author);
	}
	if(data->reference) {
		data->reference->SetText(prefs.reference);
	}
	if(data->snap_parts) {
		data->snap_parts->SetData(prefs.snap_parts_to_bars);
	}
	if(data->solo_record) {
		data->solo_record->SetData(prefs.solo_record_in_editors);
	}
}

void PrefRecord::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	RecordPrefs& prefs = model.GetRecord();
	
	// Check if values have changed and update the model
	if(data->input_monitoring) {
		bool new_val = data->input_monitoring->GetData();
		changed.Add(new_val != prefs.input_monitoring);
		prefs.input_monitoring = new_val;
	}
	if(data->software_monitoring) {
		bool new_val = data->software_monitoring->GetData();
		changed.Add(new_val != prefs.software_monitoring);
		prefs.software_monitoring = new_val;
	}
	if(data->enable_count_in) {
		bool new_val = data->enable_count_in->GetData();
		changed.Add(new_val != prefs.enable_count_in);
		prefs.enable_count_in = new_val;
	}
	if(data->count_in_measures) {
		int new_val = data->count_in_measures->GetData();
		changed.Add(new_val != prefs.count_in_measures);
		prefs.count_in_measures = new_val;
	}
	if(data->auto_punch_in) {
		bool new_val = data->auto_punch_in->GetData();
		changed.Add(new_val != prefs.auto_punch_in);
		prefs.auto_punch_in = new_val;
	}
	if(data->auto_punch_out) {
		bool new_val = data->auto_punch_out->GetData();
		changed.Add(new_val != prefs.auto_punch_out);
		prefs.auto_punch_out = new_val;
	}
	if(data->use_punch_points) {
		bool new_val = data->use_punch_points->GetData();
		changed.Add(new_val != prefs.use_punch_points);
		prefs.use_punch_points = new_val;
	}
	if(data->pre_record_seconds) {
		double new_val = data->pre_record_seconds->GetData() / 10.0; // Convert back from int
		changed.Add(abs(new_val - prefs.pre_record_seconds) > 0.01); // Compare with tolerance
		prefs.pre_record_seconds = new_val;
	}
	if(data->create_images) {
		bool new_val = data->create_images->GetData();
		changed.Add(new_val != prefs.create_images_during_record);
		prefs.create_images_during_record = new_val;
	}
	if(data->descriptor) {
		String new_val = data->descriptor->GetText();
		changed.Add(new_val != prefs.descriptor);
		prefs.descriptor = new_val;
	}
	if(data->author) {
		String new_val = data->author->GetText();
		changed.Add(new_val != prefs.author);
		prefs.author = new_val;
	}
	if(data->reference) {
		String new_val = data->reference->GetText();
		changed.Add(new_val != prefs.reference);
		prefs.reference = new_val;
	}
	if(data->snap_parts) {
		bool new_val = data->snap_parts->GetData();
		changed.Add(new_val != prefs.snap_parts_to_bars);
		prefs.snap_parts_to_bars = new_val;
	}
	if(data->solo_record) {
		bool new_val = data->solo_record->GetData();
		changed.Add(new_val != prefs.solo_record_in_editors);
		prefs.solo_record_in_editors = new_val;
	}
}

void PrefRecord::InitInputMonitoringSection() {
	// Initialize input monitoring settings
	LabelBox* input_monitoring_box = new LabelBox("Input Monitoring");
	
	data->input_monitoring = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Input Monitoring", true));
	input_monitoring_box->Add(data->input_monitoring->SizePos());
	
	data->software_monitoring = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Software Monitoring", false));
	input_monitoring_box->Add(data->software_monitoring->SizePos());
	
	Add(input_monitoring_box->SizePos());
}

void PrefRecord::InitCountInSection() {
	// Initialize count-in settings
	LabelBox* count_in_box = new LabelBox("Count-in");
	
	data->enable_count_in = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Enable Count-in", true));
	count_in_box->Add(data->enable_count_in->SizePos());
	
	data->count_in_measures = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Count-in Measures", 1, 8, 2));
	count_in_box->Add(data->count_in_measures->SizePos());
	
	Add(count_in_box->SizePos());
}

void PrefRecord::InitPunchInOutSection() {
	// Initialize punch-in/out settings
	LabelBox* punch_box = new LabelBox("Punch-in/out");
	
	data->auto_punch_in = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Auto Punch-in", false));
	punch_box->Add(data->auto_punch_in->SizePos());
	
	data->auto_punch_out = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Auto Punch-out", false));
	punch_box->Add(data->auto_punch_out->SizePos());
	
	data->use_punch_points = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Use Punch Points", true));
	punch_box->Add(data->use_punch_points->SizePos());
	
	Add(punch_box->SizePos());
}

void PrefRecord::InitRecordingBehaviorSection() {
	// Initialize recording behavior settings
	LabelBox* behavior_box = new LabelBox("Recording Behavior");
	
	data->pre_record_seconds = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Pre-record Seconds (x10)", 0, 100, 10)); // x10 to make integer-friendly
	behavior_box->Add(data->pre_record_seconds->SizePos());
	
	data->create_images = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Create Images During Record", true));
	behavior_box->Add(data->create_images->SizePos());
	
	Add(behavior_box->SizePos());
}

void PrefRecord::InitFileInfoSection() {
	// Initialize file info settings
	LabelBox* file_info_box = new LabelBox("File Info");
	
	data->descriptor = new EditString();
	data->descriptor->SetLabel("Descriptor");
	file_info_box->Add(data->descriptor->SizePos());
	
	data->author = new EditString();
	data->author->SetLabel("Author");
	file_info_box->Add(data->author->SizePos());
	
	data->reference = new EditString();
	data->reference->SetLabel("Reference");
	file_info_box->Add(data->reference->SizePos());
	
	Add(file_info_box->SizePos());
}

void PrefRecord::InitBehaviorSection() {
	// Initialize behavior settings
	LabelBox* behavior_box = new LabelBox("Behavior");
	
	data->snap_parts = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Snap Parts to Bars", true));
	behavior_box->Add(data->snap_parts->SizePos());
	
	data->solo_record = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Solo Record in Editors", true));
	behavior_box->Add(data->solo_record->SizePos());
	
	Add(behavior_box->SizePos());
}

REGISTER_PREF_PANEL("Record", "General", PrefRecord)

}