#ifndef _instruments_granulartextureengine_granulartextureengine_h_
#define _instruments_granulartextureengine_granulartextureengine_h_

#include <PluginSDK/PluginSDK.h>

namespace Instruments {

class GranularTextureEngine : public PluginSDK::InstrumentProcessor {
public:
	typedef GranularTextureEngine CLASSNAME;
	GranularTextureEngine();

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
