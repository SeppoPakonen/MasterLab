#ifndef _effects_timelessdualdelay_timelessdualdelay_h_
#define _effects_timelessdualdelay_timelessdualdelay_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class TimelessDualDelay : public PluginSDK::PluginProcessor {
public:
	typedef TimelessDualDelay CLASSNAME;
	TimelessDualDelay();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
