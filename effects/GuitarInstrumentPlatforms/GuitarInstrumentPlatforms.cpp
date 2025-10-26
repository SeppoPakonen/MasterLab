#include "GuitarInstrumentPlatforms.h"

namespace Effects {

GuitarInstrumentPlatforms::GuitarInstrumentPlatforms() {
	// TODO: Register parameters and initialise routing map
}

void GuitarInstrumentPlatforms::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void GuitarInstrumentPlatforms::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void GuitarInstrumentPlatforms::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

} // namespace Effects
