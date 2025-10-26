#include "PolyphonicPitchEditor.h"

namespace Effects {

PolyphonicPitchEditor::PolyphonicPitchEditor() {
	// TODO: Register parameters and initialise routing map
}

void PolyphonicPitchEditor::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void PolyphonicPitchEditor::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void PolyphonicPitchEditor::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

} // namespace Effects
