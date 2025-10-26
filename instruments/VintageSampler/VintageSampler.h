#ifndef _instruments_vintagesampler_vintagesampler_h_
#define _instruments_vintagesampler_vintagesampler_h_

#include <PluginSDK/PluginSDK.h>

namespace Instruments {

class VintageSampler : public PluginSDK::InstrumentProcessor {
public:
	typedef VintageSampler CLASSNAME;
	VintageSampler();

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
