#ifndef _instruments_momentumloopstation_momentumloopstation_h_
#define _instruments_momentumloopstation_momentumloopstation_h_

#include <PluginSDK/PluginSDK.h>

namespace Instruments {

class MomentumLoopStation : public PluginSDK::InstrumentProcessor {
public:
	typedef MomentumLoopStation CLASSNAME;
	MomentumLoopStation();

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
