#include "CoreSynthCollection.h"

namespace Instruments {

CoreSynthCollection::CoreSynthCollection() {
	// TODO: Register parameters and initialise routing map
}

void CoreSynthCollection::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void CoreSynthCollection::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void CoreSynthCollection::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

void CoreSynthCollection::NoteOn(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOn(evt);
	// TODO: Dispatch note-on to voice manager
}

void CoreSynthCollection::NoteOff(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOff(evt);
	// TODO: Dispatch note-off to voice manager
}

void CoreSynthCollection::AllNotesOff() {
	PluginSDK::InstrumentProcessor::AllNotesOff();
	// TODO: Reset envelopes/voices
}

} // namespace Instruments
