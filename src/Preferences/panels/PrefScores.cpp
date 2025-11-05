#include "PrefScores.h"

namespace am {

// Define member controls for PrefScores
struct PrefScores::Data {
	// Display section controls
	LabeledOption* show_page_view = nullptr;
	LabeledOption* show_scroll_view = nullptr;
	LabeledOption* show_keyboard_view = nullptr;
	
	// Notation section controls
	LabeledOption* auto_beam_notes = nullptr;
	LabeledOption* show_accidentals = nullptr;
	LabeledOption* use_standard_notation = nullptr;
	
	// Playback section controls
	LabeledOption* play_notes_as_edit = nullptr;
	LabeledOption* highlight_played_notes = nullptr;
};

PrefScores::PrefScores() {
	data = new Data();
	
	// Initialize UI sections
	InitDisplaySection();
	InitNotationSection();
	InitPlaybackSection();
}

void PrefScores::Init(PreferencesModel& model) {
	// Initialize the panel with model data
}

void PrefScores::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const ScoresPrefs& prefs = model.GetScores();
	
	if(data->show_page_view) {
		data->show_page_view->SetData(prefs.show_page_view);
	}
	if(data->show_scroll_view) {
		data->show_scroll_view->SetData(prefs.show_scroll_view);
	}
	if(data->show_keyboard_view) {
		data->show_keyboard_view->SetData(prefs.show_keyboard_view);
	}
	if(data->auto_beam_notes) {
		data->auto_beam_notes->SetData(prefs.auto_beam_notes);
	}
	if(data->show_accidentals) {
		data->show_accidentals->SetData(prefs.show_accidentals);
	}
	if(data->use_standard_notation) {
		data->use_standard_notation->SetData(prefs.use_standard_notation);
	}
	if(data->play_notes_as_edit) {
		data->play_notes_as_edit->SetData(prefs.play_notes_as_you_edit);
	}
	if(data->highlight_played_notes) {
		data->highlight_played_notes->SetData(prefs.highlight_played_notes);
	}
}

void PrefScores::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	ScoresPrefs& prefs = model.GetScores();
	
	// Check if values have changed and update the model
	if(data->show_page_view) {
		bool new_val = data->show_page_view->GetData();
		changed.Add(new_val != prefs.show_page_view);
		prefs.show_page_view = new_val;
	}
	if(data->show_scroll_view) {
		bool new_val = data->show_scroll_view->GetData();
		changed.Add(new_val != prefs.show_scroll_view);
		prefs.show_scroll_view = new_val;
	}
	if(data->show_keyboard_view) {
		bool new_val = data->show_keyboard_view->GetData();
		changed.Add(new_val != prefs.show_keyboard_view);
		prefs.show_keyboard_view = new_val;
	}
	if(data->auto_beam_notes) {
		bool new_val = data->auto_beam_notes->GetData();
		changed.Add(new_val != prefs.auto_beam_notes);
		prefs.auto_beam_notes = new_val;
	}
	if(data->show_accidentals) {
		bool new_val = data->show_accidentals->GetData();
		changed.Add(new_val != prefs.show_accidentals);
		prefs.show_accidentals = new_val;
	}
	if(data->use_standard_notation) {
		bool new_val = data->use_standard_notation->GetData();
		changed.Add(new_val != prefs.use_standard_notation);
		prefs.use_standard_notation = new_val;
	}
	if(data->play_notes_as_edit) {
		bool new_val = data->play_notes_as_edit->GetData();
		changed.Add(new_val != prefs.play_notes_as_you_edit);
		prefs.play_notes_as_you_edit = new_val;
	}
	if(data->highlight_played_notes) {
		bool new_val = data->highlight_played_notes->GetData();
		changed.Add(new_val != prefs.highlight_played_notes);
		prefs.highlight_played_notes = new_val;
	}
}

void PrefScores::InitDisplaySection() {
	// Initialize display settings
	LabelBox* display_box = new LabelBox("Display");
	
	data->show_page_view = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Page View", true));
	display_box->Add(data->show_page_view->SizePos());
	
	data->show_scroll_view = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Scroll View", false));
	display_box->Add(data->show_scroll_view->SizePos());
	
	data->show_keyboard_view = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Keyboard View", false));
	display_box->Add(data->show_keyboard_view->SizePos());
	
	Add(display_box->SizePos());
}

void PrefScores::InitNotationSection() {
	// Initialize notation settings
	LabelBox* notation_box = new LabelBox("Notation");
	
	data->auto_beam_notes = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Auto-beam Notes", true));
	notation_box->Add(data->auto_beam_notes->SizePos());
	
	data->show_accidentals = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Show Accidentals", true));
	notation_box->Add(data->show_accidentals->SizePos());
	
	data->use_standard_notation = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Use Standard Notation", true));
	notation_box->Add(data->use_standard_notation->SizePos());
	
	Add(notation_box->SizePos());
}

void PrefScores::InitPlaybackSection() {
	// Initialize playback settings
	LabelBox* playback_box = new LabelBox("Playback");
	
	data->play_notes_as_edit = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Play Notes as You Edit", false));
	playback_box->Add(data->play_notes_as_edit->SizePos());
	
	data->highlight_played_notes = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Highlight Played Notes", true));
	playback_box->Add(data->highlight_played_notes->SizePos());
	
	Add(playback_box->SizePos());
}

REGISTER_PREF_PANEL("Scores", "General", PrefScores)

}