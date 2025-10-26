#include "VirtualAnalogStack.h"

namespace Instruments {

VirtualAnalogStack::VirtualAnalogStack() {
	// TODO: Register parameters and initialise routing map
}

void VirtualAnalogStack::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void VirtualAnalogStack::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void VirtualAnalogStack::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

void VirtualAnalogStack::NoteOn(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOn(evt);
	// TODO: Dispatch note-on to voice manager
}

void VirtualAnalogStack::NoteOff(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOff(evt);
	// TODO: Dispatch note-off to voice manager
}

void VirtualAnalogStack::AllNotesOff() {
	PluginSDK::InstrumentProcessor::AllNotesOff();
	// TODO: Reset envelopes/voices
}

} // namespace Instruments
