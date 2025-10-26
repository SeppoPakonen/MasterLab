#ifndef _effects_transienteqdesigner_transienteqdesigner_h_
#define _effects_transienteqdesigner_transienteqdesigner_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class TransientEqDesigner : public PluginSDK::PluginProcessor {
public:
	typedef TransientEqDesigner CLASSNAME;
	TransientEqDesigner();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
