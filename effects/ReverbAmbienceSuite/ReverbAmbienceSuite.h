#ifndef _effects_reverbambiencesuite_reverbambiencesuite_h_
#define _effects_reverbambiencesuite_reverbambiencesuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class ReverbAmbienceSuite : public PluginSDK::PluginProcessor {
public:
	typedef ReverbAmbienceSuite CLASSNAME;
	ReverbAmbienceSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
