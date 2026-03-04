#ifndef _PluginABI_LV2_LV2_h_
#define _PluginABI_LV2_LV2_h_

#include <PluginSDK/PluginSDK.h>

#include <lv2/core/lv2.h>
#include <lv2/ui/ui.h>

namespace PluginABI {
namespace LV2 {

using namespace PluginSDK;

// Forward declarations
class LV2ProcessorHost;

// Map LV2 ports to PluginProcessor
class LV2ProcessorHost {
public:
	LV2ProcessorHost(PluginProcessor* processor, double sampleRate);
	~LV2ProcessorHost();
	
	void ConnectPort(uint32_t port, void* data);
	void Process(uint32_t n_samples);

private:
	PluginProcessor* processor;
	ProcessContext context;
	
	// Buffers for ports
	float* inputL = nullptr;
	float* inputR = nullptr;
	float* outputL = nullptr;
	float* outputR = nullptr;
};

// Global registration for the plugin
void RegisterPlugin(PluginProcessor* (*createProcessor)());
const LV2_Descriptor* GetLV2Descriptor();

} // namespace LV2
} // namespace PluginABI

// Macro to define the LV2 entry point
#define LV2_PLUGIN_MAIN(ProcessorClass) \
	LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t index) { \
		if (index != 0) return nullptr; \
		PluginABI::LV2::RegisterPlugin([]() -> PluginSDK::PluginProcessor* { return new ProcessorClass(); }); \
		return PluginABI::LV2::GetLV2Descriptor(); \
	}

#endif
