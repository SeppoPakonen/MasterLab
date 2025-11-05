#include "PrefMediaBay.h"

namespace am {

// Define member controls for PrefMediaBay
struct PrefMediaBay::Data {
	// Display section controls
	LabeledOption* show_preview = nullptr;
	LabeledOption* show_thumbnails = nullptr;
	LabeledOption* show_details = nullptr;
	
	// Search section controls
	LabeledOption* search_subfolders = nullptr;
	LabeledOption* search_metadata = nullptr;
	
	// Organization section controls
	LabeledOption* auto_tag_imported = nullptr;
	LabeledOption* auto_conform = nullptr;
	
	// Advanced section controls
	LabeledSlider* max_results = nullptr;
	LabeledOption* allow_edit = nullptr;
	LabeledOption* stop_scan = nullptr;
	LabeledOption* show_extensions = nullptr;
};

PrefMediaBay::PrefMediaBay() {
	data = new Data();
	
	// Initialize UI sections
	InitDisplaySection();
	InitSearchSection();
	InitOrganizationSection();
	InitAdvancedSection();
}

void PrefMediaBay::Init(PreferencesModel& model) {
	// Initialize the panel with model data
}

void PrefMediaBay::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const MediaBayPrefs& prefs = model.GetMediaBay();
	
	if(data->show_preview) {
		data->show_preview->SetData(prefs.show_preview);
	}
	if(data->show_thumbnails) {
		data->show_thumbnails->SetData(prefs.show_thumbnails);
	}
	if(data->show_details) {
		data->show_details->SetData(prefs.show_details);
	}
	if(data->search_subfolders) {
		data->search_subfolders->SetData(prefs.search_in_subfolders);
	}
	if(data->search_metadata) {
		data->search_metadata->SetData(prefs.search_metadata);
	}
	if(data->auto_tag_imported) {
		data->auto_tag_imported->SetData(prefs.auto_tag_imported_files);
	}
	if(data->auto_conform) {
		data->auto_conform->SetData(prefs.auto_conform_audio_files);
	}
	if(data->max_results) {
		data->max_results->SetData(prefs.max_results);
	}
	if(data->allow_edit) {
		data->allow_edit->SetData(prefs.allow_edit);
	}
	if(data->stop_scan) {
		data->stop_scan->SetData(prefs.stop_scan_on_close);
	}
	if(data->show_extensions) {
		data->show_extensions->SetData(prefs.show_extensions);
	}
}

void PrefMediaBay::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	MediaBayPrefs& prefs = model.GetMediaBay();
	
	// Check if values have changed and update the model
	if(data->show_preview) {
		bool new_val = data->show_preview->GetData();
		changed.Add(new_val != prefs.show_preview);
		prefs.show_preview = new_val;
	}
	if(data->show_thumbnails) {
		bool new_val = data->show_thumbnails->GetData();
		changed.Add(new_val != prefs.show_thumbnails);
		prefs.show_thumbnails = new_val;
	}
	if(data->show_details) {
		bool new_val = data->show_details->GetData();
		changed.Add(new_val != prefs.show_details);
		prefs.show_details = new_val;
	}
	if(data->search_subfolders) {
		bool new_val = data->search_subfolders->GetData();
		changed.Add(new_val != prefs.search_in_subfolders);
		prefs.search_in_subfolders = new_val;
	}
	if(data->search_metadata) {
		bool new_val = data->search_metadata->GetData();
		changed.Add(new_val != prefs.search_metadata);
		prefs.search_metadata = new_val;
	}
	if(data->auto_tag_imported) {
		bool new_val = data->auto_tag_imported->GetData();
		changed.Add(new_val != prefs.auto_tag_imported_files);
		prefs.auto_tag_imported_files = new_val;
	}
	if(data->auto_conform) {
		bool new_val = data->auto_conform->GetData();
		changed.Add(new_val != prefs.auto_conform_audio_files);
		prefs.auto_conform_audio_files = new_val;
	}
	if(data->max_results) {
		int new_val = data->max_results->GetData();
		changed.Add(new_val != prefs.max_results);
		prefs.max_results = new_val;
	}
	if(data->allow_edit) {
		bool new_val = data->allow_edit->GetData();
		changed.Add(new_val != prefs.allow_edit);
		prefs.allow_edit = new_val;
	}
	if(data->stop_scan) {
		bool new_val = data->stop_scan->GetData();
		changed.Add(new_val != prefs.stop_scan_on_close);
		prefs.stop_scan_on_close = new_val;
	}
	if(data->show_extensions) {
		bool new_val = data->show_extensions->GetData();
		changed.Add(new_val != prefs.show_extensions);
		prefs.show_extensions = new_val;
	}
}

void PrefMediaBay::InitDisplaySection() {
	// Initialize display settings
	LabelBox* display_box = new LabelBox("Display");
	
	data->show_preview = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Preview", true));
	display_box->Add(data->show_preview->SizePos());
	
	data->show_thumbnails = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Thumbnails", true));
	display_box->Add(data->show_thumbnails->SizePos());
	
	data->show_details = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Details", true));
	display_box->Add(data->show_details->SizePos());
	
	Add(display_box->SizePos());
}

void PrefMediaBay::InitSearchSection() {
	// Initialize search settings
	LabelBox* search_box = new LabelBox("Search");
	
	data->search_subfolders = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Search in Subfolders", true));
	search_box->Add(data->search_subfolders->SizePos());
	
	data->search_metadata = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Search Metadata", true));
	search_box->Add(data->search_metadata->SizePos());
	
	Add(search_box->SizePos());
}

void PrefMediaBay::InitOrganizationSection() {
	// Initialize organization settings
	LabelBox* organization_box = new LabelBox("Organization");
	
	data->auto_tag_imported = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Auto-tag Imported Files", true));
	organization_box->Add(data->auto_tag_imported->SizePos());
	
	data->auto_conform = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Auto-conform Audio Files", true));
	organization_box->Add(data->auto_conform->SizePos());
	
	Add(organization_box->SizePos());
}

void PrefMediaBay::InitAdvancedSection() {
	// Initialize advanced settings
	LabelBox* advanced_box = new LabelBox("Advanced");
	
	data->max_results = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("Max Results", 1000, 1000000, 100000));
	advanced_box->Add(data->max_results->SizePos());
	
	data->allow_edit = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Allow Edit", false));
	advanced_box->Add(data->allow_edit->SizePos());
	
	data->stop_scan = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Stop Scan on Close", true));
	advanced_box->Add(data->stop_scan->SizePos());
	
	data->show_extensions = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Extensions", false));
	advanced_box->Add(data->show_extensions->SizePos());
	
	Add(advanced_box->SizePos());
}

REGISTER_PREF_PANEL("Media Bay", "General", PrefMediaBay)

}