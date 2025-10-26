#ifndef _effects_analogtapelab_analogtapelab_h_
#define _effects_analogtapelab_analogtapelab_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class AnalogTapeLab : public PluginSDK::PluginProcessor {
public:
	typedef AnalogTapeLab CLASSNAME;
	AnalogTapeLab();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
