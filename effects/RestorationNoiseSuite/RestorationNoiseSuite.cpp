#include "RestorationNoiseSuite.h"

namespace Effects {

RestorationNoiseSuite::RestorationNoiseSuite() {
	// TODO: Register parameters and initialise routing map
}

void RestorationNoiseSuite::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void RestorationNoiseSuite::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void RestorationNoiseSuite::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

} // namespace Effects
