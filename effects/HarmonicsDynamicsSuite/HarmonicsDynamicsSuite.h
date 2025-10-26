#ifndef _effects_harmonicsdynamicssuite_harmonicsdynamicssuite_h_
#define _effects_harmonicsdynamicssuite_harmonicsdynamicssuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class HarmonicsDynamicsSuite : public PluginSDK::PluginProcessor {
public:
	typedef HarmonicsDynamicsSuite CLASSNAME;
	HarmonicsDynamicsSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
