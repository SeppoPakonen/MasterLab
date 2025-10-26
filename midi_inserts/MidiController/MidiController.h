#ifndef _midi_inserts_midicontroller_midicontroller_h_
#define _midi_inserts_midicontroller_midicontroller_h_

#include <PluginSDK/PluginSDK.h>

namespace MidiInserts {

class MidiController : public PluginSDK::MidiEffectProcessor {
public:
	typedef MidiController CLASSNAME;
	MidiController();

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
