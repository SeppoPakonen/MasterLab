#ifndef _effects_dynamicslevelsuite_dynamicslevelsuite_h_
#define _effects_dynamicslevelsuite_dynamicslevelsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class DynamicsLevelSuite : public PluginSDK::PluginProcessor {
public:
	typedef DynamicsLevelSuite CLASSNAME;
	DynamicsLevelSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
