#ifndef _instruments_songwriterinstrumentpack_songwriterinstrumentpack_h_
#define _instruments_songwriterinstrumentpack_songwriterinstrumentpack_h_

#include <PluginSDK/PluginSDK.h>

namespace Instruments {

class SongwriterInstrumentPack : public PluginSDK::InstrumentProcessor {
public:
	typedef SongwriterInstrumentPack CLASSNAME;
	SongwriterInstrumentPack();

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
