#ifndef _effects_guitarinstrumentplatforms_guitarinstrumentplatforms_h_
#define _effects_guitarinstrumentplatforms_guitarinstrumentplatforms_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class GuitarInstrumentPlatforms : public PluginSDK::PluginProcessor {
public:
	typedef GuitarInstrumentPlatforms CLASSNAME;
	GuitarInstrumentPlatforms();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
