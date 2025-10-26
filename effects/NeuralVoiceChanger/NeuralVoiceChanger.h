#ifndef _effects_neuralvoicechanger_neuralvoicechanger_h_
#define _effects_neuralvoicechanger_neuralvoicechanger_h_

#include <PluginSDK/PluginSDK.h>

namespace Effects {

class NeuralVoiceChanger : public PluginSDK::PluginProcessor {
public:
	typedef NeuralVoiceChanger CLASSNAME;
	NeuralVoiceChanger();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Effects

#endif
