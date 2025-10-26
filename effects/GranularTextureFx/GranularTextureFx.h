#ifndef _effects_granulartexturefx_granulartexturefx_h_
#define _effects_granulartexturefx_granulartexturefx_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class GranularTextureFx : public PluginSDK::PluginProcessor {
public:
	typedef GranularTextureFx CLASSNAME;
	GranularTextureFx();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
