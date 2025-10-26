#include "ZenModelJX8P.h"

namespace Instruments {

ZenModelJX8P::ZenModelJX8P() {
	InitialiseModelDefaults();
}

void ZenModelJX8P::Prepare(const PluginSDK::AudioConfig& cfg) {
	ZenCoreWorkstation::Prepare(cfg);
	ApplyPerformanceCalibration();
}

void ZenModelJX8P::InitialiseModelDefaults() {
	SetParameterIfPresent("engine_mode", 0.0);
	SetParameterIfPresent("partialA_enable", 1.0);
	SetParameterIfPresent("partialB_enable", 1.0);
	SetParameterIfPresent("partialC_enable", 0.0);
	SetParameterIfPresent("partialD_enable", 0.0);
	SetParameterIfPresent("partialA_level", 0.85);
	SetParameterIfPresent("partialB_level", 0.72);
	SetParameterIfPresent("partialA_coarse", 0.0);
	SetParameterIfPresent("partialB_coarse", -12.0);
	SetParameterIfPresent("partialA_cutoff", 0.58);
	SetParameterIfPresent("partialB_cutoff", 0.46);
	SetParameterIfPresent("partialA_resonance", 0.18);
	SetParameterIfPresent("partialB_resonance", 0.22);
	SetParameterIfPresent("motionL1_rate", 0.18);
	SetParameterIfPresent("motionL1_depth", 0.35);
	SetParameterIfPresent("motionL1_probability", 0.9);
	SetParameterIfPresent("motionL2_rate", 0.32);
	SetParameterIfPresent("motionL2_depth", 0.15);
	SetParameterIfPresent("motionL2_probability", 0.75);
	SetParameterIfPresent("macroM1_amount", 0.5);
	SetParameterIfPresent("macroM2_amount", 0.4);
	SetParameterIfPresent("macroM3_amount", 0.35);
	SetParameterIfPresent("macroM4_amount", 0.25);
	SetParameterIfPresent("scene_morph", 0.1);
	SetParameterIfPresent("scene_blend", 0.6);
}

void ZenModelJX8P::ApplyPerformanceCalibration() {
	if(current_config.sample_rate > 48000) {
		SetParameterIfPresent("motionL1_rate", 0.14);
		SetParameterIfPresent("motionL2_rate", 0.26);
	}
}

void ZenModelJX8P::SetParameterIfPresent(const char* id, double value) {
	const PluginSDK::ParameterDescriptor* desc = Parameters().Find(id);
	if(!desc)
		return;
	Parameters().SetValueById(id, value);
}

} // namespace Instruments
