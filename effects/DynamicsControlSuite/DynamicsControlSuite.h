#ifndef _effects_dynamicscontrolsuite_dynamicscontrolsuite_h_
#define _effects_dynamicscontrolsuite_dynamicscontrolsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class DynamicsControlSuite : public PluginSDK::PluginProcessor {
public:
	typedef DynamicsControlSuite CLASSNAME;
	DynamicsControlSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
