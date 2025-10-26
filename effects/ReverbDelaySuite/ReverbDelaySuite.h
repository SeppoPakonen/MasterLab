#ifndef _effects_reverbdelaysuite_reverbdelaysuite_h_
#define _effects_reverbdelaysuite_reverbdelaysuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class ReverbDelaySuite : public PluginSDK::PluginProcessor {
public:
	typedef ReverbDelaySuite CLASSNAME;
	ReverbDelaySuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
