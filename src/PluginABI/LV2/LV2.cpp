#include "LV2.h"
#include <string.h>

namespace PluginABI {
namespace LV2 {

// Global variables for the descriptor
static PluginProcessor* (*g_createProcessor)() = nullptr;
static Upp::String g_pluginURI;
static LV2_Descriptor g_descriptor;

LV2ProcessorHost::LV2ProcessorHost(PluginProcessor* p, double sampleRate)
	: processor(p)
{
	AudioConfig config;
	config.sample_rate = (int)sampleRate;
	config.input_channels = 2; // Default to stereo for skeleton
	config.output_channels = 2;
	if (processor) processor->Prepare(config);
}

LV2ProcessorHost::~LV2ProcessorHost()
{
	if (processor) delete processor;
}

void LV2ProcessorHost::ConnectPort(uint32_t port, void* data)
{
	switch(port) {
		case 0: inputL = (float*)data; break;
		case 1: inputR = (float*)data; break;
		case 2: outputL = (float*)data; break;
		case 3: outputR = (float*)data; break;
	}
}

void LV2ProcessorHost::Process(uint32_t n_samples)
{
	if (!processor) return;
	
	context.frames = n_samples;
	
	float* inputs[2] = { inputL, inputR };
	float* outputs[2] = { outputL, outputR };
	
	context.input.channels = inputs;
	context.input.channel_count = 2;
	context.input.frame_count = n_samples;
	
	context.output.channels = outputs;
	context.output.channel_count = 2;
	context.output.frame_count = n_samples;
	
	processor->Process(context);
}

// LV2 API Functions

static LV2_Handle instantiate(const LV2_Descriptor* descriptor,
                              double rate,
                              const char* bundle_path,
                              const LV2_Feature* const* features)
{
	if (!g_createProcessor) return nullptr;
	PluginProcessor* p = g_createProcessor();
	return (LV2_Handle)new LV2ProcessorHost(p, rate);
}

static void connect_port(LV2_Handle instance,
                         uint32_t port,
                         void* data)
{
	LV2ProcessorHost* host = (LV2ProcessorHost*)instance;
	host->ConnectPort(port, data);
}

static void activate(LV2_Handle instance) {}

static void run(LV2_Handle instance, uint32_t n_samples)
{
	LV2ProcessorHost* host = (LV2ProcessorHost*)instance;
	host->Process(n_samples);
}

static void deactivate(LV2_Handle instance) {}

static void cleanup(LV2_Handle instance)
{
	delete (LV2ProcessorHost*)instance;
}

static const void* extension_data(const char* uri)
{
	return nullptr;
}

void RegisterPlugin(PluginProcessor* (*createProcessor)())
{
	g_createProcessor = createProcessor;
	if (g_createProcessor) {
		PluginProcessor* p = g_createProcessor();
		g_pluginURI = p->GetURI();
		delete p;
	}
	
	g_descriptor.URI = g_pluginURI.Begin();
	g_descriptor.instantiate = instantiate;
	g_descriptor.connect_port = connect_port;
	g_descriptor.activate = activate;
	g_descriptor.run = run;
	g_descriptor.deactivate = deactivate;
	g_descriptor.cleanup = cleanup;
	g_descriptor.extension_data = extension_data;
}

const LV2_Descriptor* GetLV2Descriptor()
{
	return &g_descriptor;
}

} // namespace LV2
} // namespace PluginABI
