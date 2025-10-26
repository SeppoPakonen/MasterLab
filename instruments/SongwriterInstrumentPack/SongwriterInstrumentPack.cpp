#include "SongwriterInstrumentPack.h"

namespace Instruments {

SongwriterInstrumentPack::SongwriterInstrumentPack() {
	// TODO: Register parameters and initialise routing map
}

void SongwriterInstrumentPack::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void SongwriterInstrumentPack::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void SongwriterInstrumentPack::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

void SongwriterInstrumentPack::NoteOn(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOn(evt);
	// TODO: Dispatch note-on to voice manager
}

void SongwriterInstrumentPack::NoteOff(const PluginSDK::NoteEvent& evt) {
	PluginSDK::InstrumentProcessor::NoteOff(evt);
	// TODO: Dispatch note-off to voice manager
}

void SongwriterInstrumentPack::AllNotesOff() {
	PluginSDK::InstrumentProcessor::AllNotesOff();
	// TODO: Reset envelopes/voices
}

} // namespace Instruments
