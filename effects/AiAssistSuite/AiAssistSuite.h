#ifndef _effects_aiassistsuite_aiassistsuite_h_
#define _effects_aiassistsuite_aiassistsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class AiAssistSuite : public PluginSDK::PluginProcessor {
public:
	typedef AiAssistSuite CLASSNAME;
	AiAssistSuite();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
