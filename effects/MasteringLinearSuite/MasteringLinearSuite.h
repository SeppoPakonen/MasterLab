#ifndef _effects_masteringlinearsuite_masteringlinearsuite_h_
#define _effects_masteringlinearsuite_masteringlinearsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class MasteringLinearSuite : public PluginSDK::PluginProcessor {
public:
	typedef MasteringLinearSuite CLASSNAME;
	MasteringLinearSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
