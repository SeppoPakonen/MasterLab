#ifndef _effects_essentialmacrofx_essentialmacrofx_h_
#define _effects_essentialmacrofx_essentialmacrofx_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class EssentialMacroFx : public PluginSDK::PluginProcessor {
public:
	typedef EssentialMacroFx CLASSNAME;
	EssentialMacroFx();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
