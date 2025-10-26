#ifndef _effects_filterdesignsuite_filterdesignsuite_h_
#define _effects_filterdesignsuite_filterdesignsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class FilterDesignSuite : public PluginSDK::PluginProcessor {
public:
	typedef FilterDesignSuite CLASSNAME;
	FilterDesignSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
