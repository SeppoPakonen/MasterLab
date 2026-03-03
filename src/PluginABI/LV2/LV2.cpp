#include "LV2.h"

namespace PluginABI {
namespace LV2 {

LV2ProcessorHost::LV2ProcessorHost(PluginProcessor& p, double sampleRate)
	: processor(p)
{
	AudioConfig config;
	config.sample_rate = (int)sampleRate;
	config.input_channels = 2; // Default to stereo for skeleton
	config.output_channels = 2;
	processor.Prepare(config);
}

void LV2ProcessorHost::ConnectPort(uint32_t port, void* data)
{
	switch(port) {
		case 0: inputL = (float*)data; break;
		case 1: inputR = (float*)data; break;
		case 2: outputL = (float*)data; break;
		case 3: outputR = (float*)data; break;
		// case 4: control_param_1 = (float*)data; break; etc.
	}
}

void LV2ProcessorHost::Process(uint32_t n_samples)
{
	context.frames = n_samples;
	
	// Map buffers to ProcessContext
	float* inputs[2] = { inputL, inputR };
	float* outputs[2] = { outputL, outputR };
	
	context.input.channels = inputs;
	context.input.channel_count = 2;
	context.input.frame_count = n_samples;
	
	context.output.channels = outputs;
	context.output.channel_count = 2;
	context.output.frame_count = n_samples;
	
	// Call the processor
	processor.Process(context);
}

} // namespace LV2
} // namespace PluginABI
