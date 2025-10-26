#ifndef _effects_meteringanalysissuite_meteringanalysissuite_h_
#define _effects_meteringanalysissuite_meteringanalysissuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class MeteringAnalysisSuite : public PluginSDK::PluginProcessor {
public:
	typedef MeteringAnalysisSuite CLASSNAME;
	MeteringAnalysisSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
