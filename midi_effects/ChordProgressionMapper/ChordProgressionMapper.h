#ifndef _midi_effects_chordprogressionmapper_chordprogressionmapper_h_
#define _midi_effects_chordprogressionmapper_chordprogressionmapper_h_

#include <PluginSDK/PluginSDK.h>

namespace MidiEffects {

class ChordProgressionMapper : public PluginSDK::MidiEffectProcessor {
public:
	typedef ChordProgressionMapper CLASSNAME;
	ChordProgressionMapper();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Reset() override;
	void Process(PluginSDK::ProcessContext& ctx, Vector<PluginSDK::NoteEvent>& in_notes,
		Vector<PluginSDK::NoteEvent>& out_notes, Vector<PluginSDK::ControlEvent>& in_controls,
		Vector<PluginSDK::ControlEvent>& out_controls) override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace MidiEffects

#endif
