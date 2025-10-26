#ifndef _effects_clipperlimiterlab_clipperlimiterlab_h_
#define _effects_clipperlimiterlab_clipperlimiterlab_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class ClipperLimiterLab : public PluginSDK::PluginProcessor {
public:
	typedef ClipperLimiterLab CLASSNAME;
	ClipperLimiterLab();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
