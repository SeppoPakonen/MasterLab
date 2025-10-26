#ifndef _effects_stemseparationsuite_stemseparationsuite_h_
#define _effects_stemseparationsuite_stemseparationsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class StemSeparationSuite : public PluginSDK::PluginProcessor {
public:
	typedef StemSeparationSuite CLASSNAME;
	StemSeparationSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
