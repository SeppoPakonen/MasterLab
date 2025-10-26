#include "VintageSampler.h"

namespace Instruments {

VintageSampler::VintageSampler() {
	// TODO: Register parameters and initialise routing map
}

void VintageSampler::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void VintageSampler::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void VintageSampler::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

void VintageSampler::NoteOn(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOn(evt);
	// TODO: Dispatch note-on to voice manager
}

void VintageSampler::NoteOff(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOff(evt);
	// TODO: Dispatch note-off to voice manager
}

void VintageSampler::AllNotesOff() {
	PluginSDK::InstrumentProcessor::AllNotesOff();
	// TODO: Reset envelopes/voices
}

} // namespace Instruments
