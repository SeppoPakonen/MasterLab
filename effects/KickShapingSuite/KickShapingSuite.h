#ifndef _effects_kickshapingsuite_kickshapingsuite_h_
#define _effects_kickshapingsuite_kickshapingsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class KickShapingSuite : public PluginSDK::PluginProcessor {
public:
	typedef KickShapingSuite CLASSNAME;
	KickShapingSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
