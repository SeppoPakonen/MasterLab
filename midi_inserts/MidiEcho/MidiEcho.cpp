#include "MidiEcho.h"

namespace MidiInserts {

MidiEcho::MidiEcho() {
	// TODO: Register parameters and graph nodes for this MIDI insert
}

void MidiEcho::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::MidiEffectProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Initialise shared buffers, tempo-aware state, and parameter defaults
}

void MidiEcho::Reset() {
	PluginSDK::MidiEffectProcessor::Reset();
	// TODO: Clear stateful buffers and reset routing to defaults
}

void MidiEcho::Process(PluginSDK::ProcessContext& ctx, Vector<PluginSDK::NoteEvent>& in_notes,
	Vector<PluginSDK::NoteEvent>& out_notes, Vector<PluginSDK::ControlEvent>& in_controls,
	Vector<PluginSDK::ControlEvent>& out_controls) {
	(void)ctx;
	(void)in_notes;
	(void)in_controls;

	out_notes = in_notes;
	out_controls = in_controls;
	// TODO: Implement MIDI processing graph before writing to outputs
}

} // namespace MidiInserts
