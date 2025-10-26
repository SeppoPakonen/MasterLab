#include "ZenModelJUNO106.h"

namespace Instruments {

ZenModelJUNO106::ZenModelJUNO106() {
	InitialiseModelDefaults();
}

void ZenModelJUNO106::Prepare(const PluginSDK::AudioConfig& cfg) {
	ZenCoreWorkstation::Prepare(cfg);
	UpdateSampleRateScaling();
}

void ZenModelJUNO106::InitialiseModelDefaults() {
	SetParameterIfPresent("engine_mode", 0.0);
	SetParameterIfPresent("partialA_enable", 1.0);
	SetParameterIfPresent("partialB_enable", 0.0);
	SetParameterIfPresent("partialC_enable", 0.0);
	SetParameterIfPresent("partialD_enable", 0.0);
	SetParameterIfPresent("partialA_level", 0.95);
	SetParameterIfPresent("partialA_coarse", 0.0);
	SetParameterIfPresent("partialA_fine", 5.0);
	SetParameterIfPresent("partialA_cutoff", 0.52);
	SetParameterIfPresent("partialA_resonance", 0.12);
	SetParameterIfPresent("motionL1_rate", 0.22);
	SetParameterIfPresent("motionL1_depth", 0.28);
	SetParameterIfPresent("motionL1_probability", 1.0);
	SetParameterIfPresent("motionL2_rate", 0.4);
	SetParameterIfPresent("motionL2_depth", 0.2);
	SetParameterIfPresent("motionL2_probability", 0.6);
	SetParameterIfPresent("macroM1_amount", 0.45);
	SetParameterIfPresent("macroM2_amount", 0.35);
	SetParameterIfPresent("macroM3_amount", 0.4);
	SetParameterIfPresent("macroM4_amount", 0.15);
	SetParameterIfPresent("scene_morph", 0.0);
	SetParameterIfPresent("scene_blend", 0.5);
}

void ZenModelJUNO106::UpdateSampleRateScaling() {
	if(current_config.sample_rate >= 88200) {
		SetParameterIfPresent("motionL1_rate", 0.18);
		SetParameterIfPresent("motionL2_rate", 0.32);
	}
}

void ZenModelJUNO106::SetParameterIfPresent(const char* id, double value) {
	const PluginSDK::ParameterDescriptor* desc = Parameters().Find(id);
	if(!desc)
		return;
	Parameters().SetValueById(id, value);
}

} // namespace Instruments
