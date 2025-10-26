#ifndef _effects_pitchtimesuite_pitchtimesuite_h_
#define _effects_pitchtimesuite_pitchtimesuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class PitchTimeSuite : public PluginSDK::PluginProcessor {
public:
	typedef PitchTimeSuite CLASSNAME;
	PitchTimeSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
