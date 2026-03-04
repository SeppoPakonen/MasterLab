#ifndef _PluginSDK_PluginTypes_h_
#define _PluginSDK_PluginTypes_h_

#include <Core/Core.h>

namespace PluginSDK {

struct AudioConfig : public Upp::Moveable<AudioConfig> {
	int sample_rate = 44100;
	int input_channels = 2;
	int output_channels = 2;
	int buffer_size = 512;
	
	AudioConfig() = default;
};

struct AudioBus : public Upp::Moveable<AudioBus> {
	float** channels = nullptr;
	int channel_count = 0;
	int frame_count = 0;

	bool IsValid() const;
	float* GetChannel(int index) const;
	
	AudioBus() = default;
};

struct TransportInfo : public Upp::Moveable<TransportInfo> {
	double bpm = 120.0;
	double position_beats = 0.0;
	bool playing = false;
	bool recording = false;
	
	TransportInfo() = default;
};

struct ProcessContext : public Upp::Moveable<ProcessContext> {
	int frames = 0;
	double sample_rate = 44100.0;
	AudioBus input;
	AudioBus output;
	AudioBus sidechain;
	TransportInfo transport;
	
	ProcessContext() = default;
};

struct ParameterDescriptor : public Upp::Moveable<ParameterDescriptor> {
	Upp::String id;
	Upp::String name;
	double min = 0.0;
	double max = 1.0;
	double default_value = 0.0;
	bool automatable = true;

	ParameterDescriptor() = default;
};

class ParameterSet {
public:
	int Add(const ParameterDescriptor& descriptor);
	bool SetValue(int index, double value);
	double GetValue(int index) const;
	bool SetValueById(const Upp::String& id, double value);
	double GetValueById(const Upp::String& id) const;
	const ParameterDescriptor* Find(const Upp::String& id) const;
	const Upp::Vector<ParameterDescriptor>& Descriptors() const;

private:
	Upp::Vector<ParameterDescriptor> descriptors;
	Upp::Vector<double> states;
};

struct GraphNode : public Upp::MoveableAndDeepCopyOption<GraphNode> {
	Upp::String id;
	Upp::String name;
	Upp::String type; // e.g., "plugin", "input", "output"

	void Jsonize(Upp::JsonIO& jio) {
		jio("id", id)("name", name)("type", type);
	}
};

struct GraphEdge : public Upp::MoveableAndDeepCopyOption<GraphEdge> {
	Upp::String id;
	Upp::String sourceId;
	Upp::String targetId;
	Upp::String portName;

	void Jsonize(Upp::JsonIO& jio) {
		jio("id", id)("sourceId", sourceId)("targetId", targetId)("portName", portName);
	}
};

struct GraphVisualization : public Upp::MoveableAndDeepCopyOption<GraphVisualization> {
	Upp::Vector<GraphNode> nodes;
	Upp::Vector<GraphEdge> edges;

	const Upp::Vector<GraphNode>& GetNodes() const { return nodes; }
	const Upp::Vector<GraphEdge>& GetEdges() const { return edges; }
	
	void Clear() { nodes.Clear(); edges.Clear(); }

	void Jsonize(Upp::JsonIO& jio) {
		jio("nodes", nodes)("edges", edges);
	}
};


} // namespace PluginSDK

#endif
