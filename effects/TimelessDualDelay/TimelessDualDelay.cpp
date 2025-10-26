#include "TimelessDualDelay.h"

namespace Effects {

TimelessDualDelay::TimelessDualDelay() {
	// TODO: Register parameters and initialise routing map
}

void TimelessDualDelay::Prepare(const PluginSDK::AudioConfig& cfg) {
	PluginSDK::PluginProcessor::Prepare(cfg);
	(void)cfg;
	// TODO: Allocate resources based on cfg
}

void TimelessDualDelay::Reset() {
	PluginSDK::PluginProcessor::Reset();
	// TODO: Reset internal state
}

void TimelessDualDelay::Process(PluginSDK::ProcessContext& ctx) {
	(void)ctx;
	// TODO: Implement processing graph described in AGENTS.md
}

} // namespace Effects
