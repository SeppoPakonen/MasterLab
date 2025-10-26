#ifndef _effects_vocaldesignrack_vocaldesignrack_h_
#define _effects_vocaldesignrack_vocaldesignrack_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class VocalDesignRack : public PluginSDK::PluginProcessor {
public:
	typedef VocalDesignRack CLASSNAME;
	VocalDesignRack();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
