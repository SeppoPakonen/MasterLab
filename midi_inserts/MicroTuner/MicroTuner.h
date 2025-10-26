#ifndef _midi_inserts_microtuner_microtuner_h_
#define _midi_inserts_microtuner_microtuner_h_

#include <PluginSDK/PluginSDK.h>

namespace MidiInserts {

class MicroTuner : public PluginSDK::MidiEffectProcessor {
public:
	typedef MicroTuner CLASSNAME;
	MicroTuner();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Reset() override;
	void Process(PluginSDK::ProcessContext& ctx, Vector<PluginSDK::NoteEvent>& in_notes,
		Vector<PluginSDK::NoteEvent>& out_notes, Vector<PluginSDK::ControlEvent>& in_controls,
		Vector<PluginSDK::ControlEvent>& out_controls) override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace MidiInserts

#endif
