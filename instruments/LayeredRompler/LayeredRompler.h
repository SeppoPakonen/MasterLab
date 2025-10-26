#ifndef _instruments_layeredrompler_layeredrompler_h_
#define _instruments_layeredrompler_layeredrompler_h_

#include <PluginSDK/PluginSDK.h>

namespace Instruments {

class LayeredRompler : public PluginSDK::InstrumentProcessor {
public:
	typedef LayeredRompler CLASSNAME;
	LayeredRompler();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;
	void NoteOn(const PluginSDK::NoteEvent& evt) override;
	void NoteOff(const PluginSDK::NoteEvent& evt) override;
	void AllNotesOff() override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace Instruments

#endif
