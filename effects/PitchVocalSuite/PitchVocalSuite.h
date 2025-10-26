#ifndef _effects_pitchvocalsuite_pitchvocalsuite_h_
#define _effects_pitchvocalsuite_pitchvocalsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class PitchVocalSuite : public PluginSDK::PluginProcessor {
public:
	typedef PitchVocalSuite CLASSNAME;
	PitchVocalSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
