#include "ZenCoreWorkstation.h"

namespace Instruments {

ZenCoreWorkstation::ZenCoreWorkstation() {
	// TODO: Register parameters and initialise routing map
}

void ZenCoreWorkstation::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void ZenCoreWorkstation::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void ZenCoreWorkstation::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

void ZenCoreWorkstation::NoteOn(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOn(evt);
	// TODO: Dispatch note-on to voice manager
}

void ZenCoreWorkstation::NoteOff(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOff(evt);
	// TODO: Dispatch note-off to voice manager
}

void ZenCoreWorkstation::AllNotesOff() {
	PluginSDK::InstrumentProcessor::AllNotesOff();
	// TODO: Reset envelopes/voices
}

} // namespace Instruments
