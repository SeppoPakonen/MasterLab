#ifndef _midi_inserts_arpache5_arpache5_h_
#define _midi_inserts_arpache5_arpache5_h_

#include <PluginSDK/PluginSDK.h>

namespace MidiInserts {

class Arpache5 : public PluginSDK::MidiEffectProcessor {
public:
	typedef Arpache5 CLASSNAME;
	Arpache5();

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
