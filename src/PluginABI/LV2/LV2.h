#ifndef _PluginABI_LV2_LV2_h_
#define _PluginABI_LV2_LV2_h_

#include <PluginSDK/PluginSDK.h>

#include <lv2/core/lv2.h>
#include <lv2/ui/ui.h>

namespace PluginABI {
namespace LV2 {

using namespace PluginSDK;

// Map LV2 ports to PluginProcessor
class LV2ProcessorHost {
public:
	LV2ProcessorHost(PluginProcessor& processor, double sampleRate);
	
	void ConnectPort(uint32_t port, void* data);
	void Process(uint32_t n_samples);

private:
	PluginProcessor& processor;
	ProcessContext context;
	
	// Buffers for ports
	float* inputL = nullptr;
	float* inputR = nullptr;
	float* outputL = nullptr;
	float* outputR = nullptr;
	
	// Parameters/Control ports would be mapped here too
};

} // namespace LV2
} // namespace PluginABI

#endif
