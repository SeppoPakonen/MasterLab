#include "ModularGuitarRig.h"

namespace Effects {

ModularGuitarRig::ModularGuitarRig() {
	// TODO: Register parameters and initialise routing map
}

void ModularGuitarRig::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void ModularGuitarRig::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void ModularGuitarRig::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

} // namespace Effects
