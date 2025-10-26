#include "MomentumLoopStation.h"

namespace Instruments {

MomentumLoopStation::MomentumLoopStation() {
	// TODO: Register parameters and initialise routing map
}

void MomentumLoopStation::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void MomentumLoopStation::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void MomentumLoopStation::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

void MomentumLoopStation::NoteOn(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOn(evt);
	// TODO: Dispatch note-on to voice manager
}

void MomentumLoopStation::NoteOff(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOff(evt);
	// TODO: Dispatch note-off to voice manager
}

void MomentumLoopStation::AllNotesOff() {
	PluginSDK::InstrumentProcessor::AllNotesOff();
	// TODO: Reset envelopes/voices
}

} // namespace Instruments
