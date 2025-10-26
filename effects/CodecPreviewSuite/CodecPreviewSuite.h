#ifndef _effects_codecpreviewsuite_codecpreviewsuite_h_
#define _effects_codecpreviewsuite_codecpreviewsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class CodecPreviewSuite : public PluginSDK::PluginProcessor {
public:
	typedef CodecPreviewSuite CLASSNAME;
	CodecPreviewSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
