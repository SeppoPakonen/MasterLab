#ifndef _effects_spatialsurroundsuite_spatialsurroundsuite_h_
#define _effects_spatialsurroundsuite_spatialsurroundsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class SpatialSurroundSuite : public PluginSDK::PluginProcessor {
public:
	typedef SpatialSurroundSuite CLASSNAME;
	SpatialSurroundSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
