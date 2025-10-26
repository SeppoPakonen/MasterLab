#ifndef _effects_modcreativesuite_modcreativesuite_h_
#define _effects_modcreativesuite_modcreativesuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class ModCreativeSuite : public PluginSDK::PluginProcessor {
public:
	typedef ModCreativeSuite CLASSNAME;
	ModCreativeSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
