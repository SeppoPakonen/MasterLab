#ifndef _effects_analysisutilitysuite_analysisutilitysuite_h_
#define _effects_analysisutilitysuite_analysisutilitysuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class AnalysisUtilitySuite : public PluginSDK::PluginProcessor {
public:
	typedef AnalysisUtilitySuite CLASSNAME;
	AnalysisUtilitySuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
