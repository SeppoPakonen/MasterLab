#ifndef _instruments_orchestralsectionsuite_orchestralsectionsuite_h_
#define _instruments_orchestralsectionsuite_orchestralsectionsuite_h_

#include <PluginSDK/PluginSDK.h>

namespace Instruments {

class OrchestralSectionSuite : public PluginSDK::InstrumentProcessor {
public:
	typedef OrchestralSectionSuite CLASSNAME;
	OrchestralSectionSuite();

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
