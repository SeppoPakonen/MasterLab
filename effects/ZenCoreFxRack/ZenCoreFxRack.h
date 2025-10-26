#ifndef _effects_zencorefxrack_zencorefxrack_h_
#define _effects_zencorefxrack_zencorefxrack_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class ZenCoreFxRack : public PluginSDK::PluginProcessor {
public:
	typedef ZenCoreFxRack CLASSNAME;
	ZenCoreFxRack();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
