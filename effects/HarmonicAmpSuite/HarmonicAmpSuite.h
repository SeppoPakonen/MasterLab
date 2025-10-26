#ifndef _effects_harmonicampsuite_harmonicampsuite_h_
#define _effects_harmonicampsuite_harmonicampsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class HarmonicAmpSuite : public PluginSDK::PluginProcessor {
public:
	typedef HarmonicAmpSuite CLASSNAME;
	HarmonicAmpSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
