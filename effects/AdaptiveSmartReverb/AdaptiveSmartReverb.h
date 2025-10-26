#ifndef _effects_adaptivesmartreverb_adaptivesmartreverb_h_
#define _effects_adaptivesmartreverb_adaptivesmartreverb_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class AdaptiveSmartReverb : public PluginSDK::PluginProcessor {
public:
	typedef AdaptiveSmartReverb CLASSNAME;
	AdaptiveSmartReverb();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
