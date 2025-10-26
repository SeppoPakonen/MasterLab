#ifndef _effects_modularguitarrig_modularguitarrig_h_
#define _effects_modularguitarrig_modularguitarrig_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class ModularGuitarRig : public PluginSDK::PluginProcessor {
public:
	typedef ModularGuitarRig CLASSNAME;
	ModularGuitarRig();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
