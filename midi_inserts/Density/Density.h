#ifndef _midi_inserts_density_density_h_
#define _midi_inserts_density_density_h_

#include <PluginSDK/PluginSDK.h>

namespace MidiInserts {

class Density : public PluginSDK::MidiEffectProcessor {
public:
	typedef Density CLASSNAME;
	Density();

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
