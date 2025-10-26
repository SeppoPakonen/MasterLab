#ifndef _effects_toneboosteressentials_toneboosteressentials_h_
#define _effects_toneboosteressentials_toneboosteressentials_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class ToneboosterEssentials : public PluginSDK::PluginProcessor {
public:
	typedef ToneboosterEssentials CLASSNAME;
	ToneboosterEssentials();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
