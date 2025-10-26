#ifndef _effects_guitarinstrumentsuite_guitarinstrumentsuite_h_
#define _effects_guitarinstrumentsuite_guitarinstrumentsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class GuitarInstrumentSuite : public PluginSDK::PluginProcessor {
public:
	typedef GuitarInstrumentSuite CLASSNAME;
	GuitarInstrumentSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
