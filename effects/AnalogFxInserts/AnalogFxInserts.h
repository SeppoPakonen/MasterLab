#ifndef _effects_analogfxinserts_analogfxinserts_h_
#define _effects_analogfxinserts_analogfxinserts_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class AnalogFxInserts : public PluginSDK::PluginProcessor {
public:
	typedef AnalogFxInserts CLASSNAME;
	AnalogFxInserts();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
