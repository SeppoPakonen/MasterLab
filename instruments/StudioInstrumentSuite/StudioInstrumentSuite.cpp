#include "StudioInstrumentSuite.h"

namespace Instruments {

StudioInstrumentSuite::StudioInstrumentSuite() {
	// TODO: Register parameters and initialise routing map
}

void StudioInstrumentSuite::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void StudioInstrumentSuite::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void StudioInstrumentSuite::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

void StudioInstrumentSuite::NoteOn(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOn(evt);
	// TODO: Dispatch note-on to voice manager
}

void StudioInstrumentSuite::NoteOff(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOff(evt);
	// TODO: Dispatch note-off to voice manager
}

void StudioInstrumentSuite::AllNotesOff() {
	PluginSDK::InstrumentProcessor::AllNotesOff();
	// TODO: Reset envelopes/voices
}

} // namespace Instruments
