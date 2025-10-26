#ifndef _effects_loudnesscontrolsuite_loudnesscontrolsuite_h_
#define _effects_loudnesscontrolsuite_loudnesscontrolsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class LoudnessControlSuite : public PluginSDK::PluginProcessor {
public:
	typedef LoudnessControlSuite CLASSNAME;
	LoudnessControlSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
