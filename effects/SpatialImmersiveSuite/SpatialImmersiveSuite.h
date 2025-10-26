#ifndef _effects_spatialimmersivesuite_spatialimmersivesuite_h_
#define _effects_spatialimmersivesuite_spatialimmersivesuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class SpatialImmersiveSuite : public PluginSDK::PluginProcessor {
public:
	typedef SpatialImmersiveSuite CLASSNAME;
	SpatialImmersiveSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
