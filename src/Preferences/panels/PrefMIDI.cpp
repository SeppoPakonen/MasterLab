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
	
	if(data->input_device) {
		// Set input device value from model - map appropriately
		data->input_device->SetData(0); // Placeholder
	}
	if(data->output_device) {
		// Set output device value from model - map appropriately
		data->output_device->SetData(0); // Placeholder
	}
	if(data->channel) {
		// Set channel value from model - assume mapping to indices 0-16 for "All" + channels 1-16
		data->channel->SetData(0); // Placeholder
	}
	if(data->echo) {
		// Set echo value from model
		data->echo->SetData(false); // Placeholder - should use actual model value
	}
	if(data->feedback) {
		// Set feedback value from model
		data->feedback->SetData(true); // Placeholder - should use actual model value
	}
	if(data->local_ctrl) {
		// Set local control value from model
		data->local_ctrl->SetData(true); // Placeholder - should use actual model value
	}
	if(data->quantize) {
		// Set quantize value from model - mapping to indices for grid options
		data->quantize->SetData(2); // Placeholder for "1/16" default
	}
	if(data->snap) {
		// Set snap value from model
		data->snap->SetData(true); // Placeholder - should use actual model value
	}
	if(data->rt_quantize) {
		// Set realtime quantize value from model
		data->rt_quantize->SetData(false); // Placeholder - should use actual model value
	}
	if(data->midi_clock) {
		// Set MIDI clock value from model
		data->midi_clock->SetData(false); // Placeholder - should use actual model value
	}
	if(data->chase_start) {
		// Set chase start value from model
		data->chase_start->SetData(true); // Placeholder - should use actual model value
	}
	if(data->chase_ctrls) {
		// Set chase controllers value from model
		data->chase_ctrls->SetData(true); // Placeholder - should use actual model value
	}
	if(data->latency) {
		// Set latency value from model - in ms range 0-100
		data->latency->SetData(10); // Placeholder
	}
	if(data->out_latency) {
		// Set output latency value from model - in ms range 0-100
		data->out_latency->SetData(10); // Placeholder
	}
}

void PrefMIDI::Store(PreferencesModel& model, Upp::Vector<bool>& changed) {
	// Store UI data to model
	// This method should save the values from UI controls back to the model
	// The 'changed' vector should indicate which values have changed
	MIDIPrefs& prefs = model.GetMIDI();
	
	// Get values from controls and update the model
	int input_dev_idx = 0;
	if(data->input_device) {
		input_dev_idx = data->input_device->GetData();
		// In a real implementation, map this index to actual device in the model
		changed.Add(false); // Placeholder
	}
	
	int output_dev_idx = 0;
	if(data->output_device) {
		output_dev_idx = data->output_device->GetData();
		changed.Add(false); // Placeholder
	}
	
	int channel_idx = 0;
	if(data->channel) {
		channel_idx = data->channel->GetData();
		changed.Add(false); // Placeholder
	}
	
	bool echo_val = false;
	if(data->echo) {
		echo_val = data->echo->GetData();
		changed.Add(echo_val != false); // Compare with default
	}
	
	bool feedback_val = true;
	if(data->feedback) {
		feedback_val = data->feedback->GetData();
		changed.Add(feedback_val != true); // Compare with default
	}
	
	bool local_ctrl_val = true;
	if(data->local_ctrl) {
		local_ctrl_val = data->local_ctrl->GetData();
		changed.Add(local_ctrl_val != true); // Compare with default
	}
	
	int quantize_idx = 2;
	if(data->quantize) {
		quantize_idx = data->quantize->GetData();
		changed.Add(quantize_idx != 2); // Compare with default "1/16"
	}
	
	bool snap_val = true;
	if(data->snap) {
		snap_val = data->snap->GetData();
		changed.Add(snap_val != true); // Compare with default
	}
	
	bool rt_quantize_val = false;
	if(data->rt_quantize) {
		rt_quantize_val = data->rt_quantize->GetData();
		changed.Add(rt_quantize_val != false); // Compare with default
	}
	
	bool midi_clock_val = false;
	if(data->midi_clock) {
		midi_clock_val = data->midi_clock->GetData();
		changed.Add(midi_clock_val != false); // Compare with default
	}
	
	bool chase_start_val = true;
	if(data->chase_start) {
		chase_start_val = data->chase_start->GetData();
		changed.Add(chase_start_val != true); // Compare with default
	}
	
	bool chase_ctrls_val = true;
	if(data->chase_ctrls) {
		chase_ctrls_val = data->chase_ctrls->GetData();
		changed.Add(chase_ctrls_val != true); // Compare with default
	}
	
	int latency_val = 10;
	if(data->latency) {
		latency_val = data->latency->GetData();
		changed.Add(latency_val != 10); // Compare with default 10ms
	}
	
	int out_latency_val = 10;
	if(data->out_latency) {
		out_latency_val = data->out_latency->GetData();
		changed.Add(out_latency_val != 10); // Compare with default 10ms
	}
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