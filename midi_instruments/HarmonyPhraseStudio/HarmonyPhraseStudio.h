#ifndef _midi_instruments_harmonyphrasestudio_harmonyphrasestudio_h_
#define _midi_instruments_harmonyphrasestudio_harmonyphrasestudio_h_

#include <PluginSDK/PluginSDK.h>

namespace MidiInstruments {

class HarmonyPhraseStudio : public PluginSDK::MidiInstrumentProcessor {
public:
	typedef HarmonyPhraseStudio CLASSNAME;
	HarmonyPhraseStudio();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Reset() override;

protected:
	void GeneratePattern(PluginSDK::ProcessContext& ctx, Vector<PluginSDK::NoteEvent>& out_notes,
		Vector<PluginSDK::ControlEvent>& out_controls) override;

private:
	PluginSDK::RoutingMap routing;
};

} // namespace MidiInstruments

#endif
