#include "VocalLiveUtilities.h"

namespace Effects {

VocalLiveUtilities::VocalLiveUtilities() {
	// TODO: Register parameters and initialise routing map
}

void VocalLiveUtilities::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void VocalLiveUtilities::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void VocalLiveUtilities::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

} // namespace Effects
