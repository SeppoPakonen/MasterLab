#ifndef _effects_delayreverbsuite_delayreverbsuite_h_
#define _effects_delayreverbsuite_delayreverbsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class DelayReverbSuite : public PluginSDK::PluginProcessor {
public:
	typedef DelayReverbSuite CLASSNAME;
	DelayReverbSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
