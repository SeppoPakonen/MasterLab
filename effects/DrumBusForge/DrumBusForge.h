#ifndef _effects_drumbusforge_drumbusforge_h_
#define _effects_drumbusforge_drumbusforge_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class DrumBusForge : public PluginSDK::PluginProcessor {
public:
	typedef DrumBusForge CLASSNAME;
	DrumBusForge();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
