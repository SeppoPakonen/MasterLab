#ifndef _effects_spectrallayersfx_spectrallayersfx_h_
#define _effects_spectrallayersfx_spectrallayersfx_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class SpectralLayersFx : public PluginSDK::PluginProcessor {
public:
	typedef SpectralLayersFx CLASSNAME;
	SpectralLayersFx();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
