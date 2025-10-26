#ifndef _effects_vocalliveutilities_vocalliveutilities_h_
#define _effects_vocalliveutilities_vocalliveutilities_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class VocalLiveUtilities : public PluginSDK::PluginProcessor {
public:
	typedef VocalLiveUtilities CLASSNAME;
	VocalLiveUtilities();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
