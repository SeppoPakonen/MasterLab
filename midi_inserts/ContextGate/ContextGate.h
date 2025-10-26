#ifndef _midi_inserts_contextgate_contextgate_h_
#define _midi_inserts_contextgate_contextgate_h_

#include <PluginSDK/PluginSDK.h>

namespace MidiInserts {

class ContextGate : public PluginSDK::MidiEffectProcessor {
public:
	typedef ContextGate CLASSNAME;
	ContextGate();

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
