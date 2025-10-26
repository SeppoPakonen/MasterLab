#include "HarmonicAmpSuite.h"

namespace Effects {

HarmonicAmpSuite::HarmonicAmpSuite() {
	// TODO: Register parameters and initialise routing map
}

void HarmonicAmpSuite::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void HarmonicAmpSuite::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void HarmonicAmpSuite::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

} // namespace Effects
