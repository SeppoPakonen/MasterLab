#ifndef _effects_vocalalignmentengine_vocalalignmentengine_h_
#define _effects_vocalalignmentengine_vocalalignmentengine_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class VocalAlignmentEngine : public PluginSDK::PluginProcessor {
public:
	typedef VocalAlignmentEngine CLASSNAME;
	VocalAlignmentEngine();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
