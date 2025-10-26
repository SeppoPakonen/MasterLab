#ifndef _effects_voicemixsuite_voicemixsuite_h_
#define _effects_voicemixsuite_voicemixsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class VoiceMixSuite : public PluginSDK::PluginProcessor {
public:
	typedef VoiceMixSuite CLASSNAME;
	VoiceMixSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
