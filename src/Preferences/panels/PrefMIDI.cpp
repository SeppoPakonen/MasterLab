#include "PrefMIDI.h"

namespace am {

// Define member controls for PrefMIDI
struct PrefMIDI::Data {
	// Defaults section controls
	LabeledDropList* input_device = nullptr;
	LabeledDropList* output_device = nullptr;
	LabeledDropList* channel = nullptr;
	
	// Behavior section controls
	LabeledOption* echo = nullptr;
	LabeledOption* feedback = nullptr;
	LabeledOption* local_ctrl = nullptr;
	
	// Editor section controls
	LabeledDropList* quantize = nullptr;
	LabeledOption* snap = nullptr;
	
	// Realtime section controls
	LabeledOption* rt_quantize = nullptr;
	LabeledOption* midi_clock = nullptr;
	
	// Chase section controls
	LabeledOption* chase_start = nullptr;
	LabeledOption* chase_ctrls = nullptr;
	
	// Timing section controls
	LabeledSlider* latency = nullptr;
	LabeledSlider* out_latency = nullptr;
};

PrefMIDI::PrefMIDI() {
	data = new Data();
	
	// Initialize UI sections
	InitDefaultsSection();
	InitBehaviorSection();
	InitEditorSection();
	InitRealtimeSection();
	InitChaseSection();
	InitTimingSection();
}

void PrefMIDI::Init(PreferencesModel& model) {
	// Initialize the panel with model data
	// This method should set up the initial state based on the model
	// For PrefMIDI, we might set the initial values based on the model
}

void PrefMIDI::Load(const PreferencesModel& model) {
	// Load data from model to UI
	// This method should populate the UI controls with values from the model
	const MIDIPrefs& prefs = model.GetMIDI();
	
	// For now, we're using placeholder values since we need to properly connect controls
	// In a real implementation, we would set the values of the actual controls here
	if(data->input_device) {
		// Set input device value from model
	}
	if(data->output_device) {
		// Set output device value from model
	}
	if(data->channel) {
		// Set channel value from model
	}
	if(data->echo) {
		// Set echo value from model
	}
	if(data->feedback) {
		// Set feedback value from model
	}
	if(data->local_ctrl) {
		// Set local control value from model
	}
	if(data->quantize) {
		// Set quantize value from model
	}
	if(data->snap) {
		// Set snap value from model
	}
	if(data->rt_quantize) {
		// Set realtime quantize value from model
	}
	if(data->midi_clock) {
		// Set MIDI clock value from model
	}
	if(data->chase_start) {
		// Set chase start value from model
	}
	if(data->chase_ctrls) {
		// Set chase controllers value from model
	}
	if(data->latency) {
		// Set latency value from model
	}
	if(data->out_latency) {
		// Set output latency value from model
	}
}

void PrefMIDI::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	MIDIPrefs& prefs = model.GetMIDI();
	
	// Check if values have changed and update the model
	if(data->input_device) {
		// Get value from input_device and update the model
	}
	if(data->output_device) {
		// Get value from output_device and update the model
	}
	if(data->channel) {
		// Get value from channel and update the model
	}
	if(data->echo) {
		// Get value from echo and update the model
	}
	if(data->feedback) {
		// Get value from feedback and update the model
	}
	if(data->local_ctrl) {
		// Get value from local_ctrl and update the model
	}
	if(data->quantize) {
		// Get value from quantize and update the model
	}
	if(data->snap) {
		// Get value from snap and update the model
	}
	if(data->rt_quantize) {
		// Get value from rt_quantize and update the model
	}
	if(data->midi_clock) {
		// Get value from midi_clock and update the model
	}
	if(data->chase_start) {
		// Get value from chase_start and update the model
	}
	if(data->chase_ctrls) {
		// Get value from chase_ctrls and update the model
	}
	if(data->latency) {
		// Get value from latency and update the model
	}
	if(data->out_latency) {
		// Get value from out_latency and update the model
	}
	
	changed.Add(false); // Placeholder - in real implementation, would track actual changes
}

void PrefMIDI::InitDefaultsSection() {
	// Initialize MIDI defaults settings
	LabelBox* defaults_box = new LabelBox("MIDI Defaults");
	
	// Default input device
	data->input_device = &dynamic_cast<LabeledDropList&>(CreateLabeledDropList("Default Input Device", 
		{ "None", "MIDI Device 1", "MIDI Device 2", "All Devices" }, 0));
	defaults_box->Add(data->input_device->SizePos());
	
	// Default output device
	data->output_device = &dynamic_cast<LabeledDropList&>(CreateLabeledDropList("Default Output Device", 
		{ "None", "MIDI Device 1", "MIDI Device 2", "All Devices" }, 0));
	defaults_box->Add(data->output_device->SizePos());
	
	// Default MIDI channel
	data->channel = &dynamic_cast<LabeledDropList&>(CreateLabeledDropList("Default MIDI Channel", 
		{ "All Channels", "Channel 1", "Channel 2", "Channel 3", "Channel 4", 
		  "Channel 5", "Channel 6", "Channel 7", "Channel 8", "Channel 9", 
		  "Channel 10", "Channel 11", "Channel 12", "Channel 13", "Channel 14", 
		  "Channel 15", "Channel 16" }, 0));
	defaults_box->Add(data->channel->SizePos());
	
	Add(defaults_box->SizePos());
}

void PrefMIDI::InitBehaviorSection() {
	// Initialize behavior settings
	LabelBox* behavior_box = new LabelBox("MIDI Behavior");
	
	// MIDI echo
	data->echo = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Enable MIDI Echo", false));
	behavior_box->Add(data->echo->SizePos());
	
	// MIDI feedback
	data->feedback = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Enable MIDI Feedback", true));
	behavior_box->Add(data->feedback->SizePos());
	
	// Local control
	data->local_ctrl = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Local Control", true));
	behavior_box->Add(data->local_ctrl->SizePos());
	
	Add(behavior_box->SizePos());
}

void PrefMIDI::InitEditorSection() {
	// Initialize editor settings
	LabelBox* editor_box = new LabelBox("MIDI Editor");
	
	// Default quantize grid
	data->quantize = &dynamic_cast<LabeledDropList&>(CreateLabeledDropList("Default Quantize Grid", 
		{ "No Grid", "1/4", "1/8", "1/16", "1/32" }, 2));
	editor_box->Add(data->quantize->SizePos());
	
	// Snap to grid
	data->snap = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Snap to Grid", true));
	editor_box->Add(data->snap->SizePos());
	
	Add(editor_box->SizePos());
}

void PrefMIDI::InitRealtimeSection() {
	// Initialize real-time behavior settings
	LabelBox* realtime_box = new LabelBox("Realtime MIDI");
	
	// Realtime quantize
	data->rt_quantize = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Realtime Quantize", false));
	realtime_box->Add(data->rt_quantize->SizePos());
	
	// MIDI clock
	data->midi_clock = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Send MIDI Clock", false));
	realtime_box->Add(data->midi_clock->SizePos());
	
	Add(realtime_box->SizePos());
}

void PrefMIDI::InitChaseSection() {
	// Initialize chase settings
	LabelBox* chase_box = new LabelBox("MIDI Chase");
	
	// Chase MIDI messages on startup
	data->chase_start = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Chase MIDI Messages on Startup", true));
	chase_box->Add(data->chase_start->SizePos());
	
	// Chase MIDI controllers
	data->chase_ctrls = &dynamic_cast<LabeledOption&>(CreateLabeledOption("Chase MIDI Controllers", true));
	chase_box->Add(data->chase_ctrls->SizePos());
	
	Add(chase_box->SizePos());
}

void PrefMIDI::InitTimingSection() {
	// Initialize timing settings
	LabelBox* timing_box = new LabelBox("MIDI Timing");
	
	// MIDI input latency
	data->latency = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("MIDI Input Latency (ms)", 0, 100, 10));
	timing_box->Add(data->latency->SizePos());
	
	// MIDI output latency
	data->out_latency = &dynamic_cast<LabeledSlider&>(CreateLabeledSlider("MIDI Output Latency (ms)", 0, 100, 10));
	timing_box->Add(data->out_latency->SizePos());
	
	Add(timing_box->SizePos());
}

REGISTER_PREF_PANEL("MIDI", "General", PrefMIDI)

}