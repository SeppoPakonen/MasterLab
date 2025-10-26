#ifndef _effects_sequencefxengine_sequencefxengine_h_
#define _effects_sequencefxengine_sequencefxengine_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class SequenceFxEngine : public PluginSDK::PluginProcessor {
public:
	typedef SequenceFxEngine CLASSNAME;
	SequenceFxEngine();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
