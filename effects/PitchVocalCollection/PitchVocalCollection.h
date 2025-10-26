#ifndef _effects_pitchvocalcollection_pitchvocalcollection_h_
#define _effects_pitchvocalcollection_pitchvocalcollection_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class PitchVocalCollection : public PluginSDK::PluginProcessor {
public:
	typedef PitchVocalCollection CLASSNAME;
	PitchVocalCollection();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
