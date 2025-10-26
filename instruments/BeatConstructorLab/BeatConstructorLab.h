#ifndef _instruments_beatconstructorlab_beatconstructorlab_h_
#define _instruments_beatconstructorlab_beatconstructorlab_h_

#include <PluginSDK/PluginSDK.h>

namespace Instruments {

class BeatConstructorLab : public PluginSDK::InstrumentProcessor {
public:
	typedef BeatConstructorLab CLASSNAME;
	BeatConstructorLab();

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
