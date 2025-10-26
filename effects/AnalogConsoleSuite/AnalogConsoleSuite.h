#ifndef _effects_analogconsolesuite_analogconsolesuite_h_
#define _effects_analogconsolesuite_analogconsolesuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class AnalogConsoleSuite : public PluginSDK::PluginProcessor {
public:
	typedef AnalogConsoleSuite CLASSNAME;
	AnalogConsoleSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
