#ifndef _PluginSDK_PluginSDK_h_
#define _PluginSDK_PluginSDK_h_

#include <Core/Core.h>

namespace PluginSDK {

// Simple POD-like structs that are trivially relocatable
struct AudioConfig : public Upp::Moveable<AudioConfig> {
	int sample_rate = 44100;
	int block_size = 0;
	int input_channels = 0;
	int output_channels = 0;
	int sidechain_channels = 0;
	
	// Add explicit constructors for U++ compatibility
	AudioConfig() = default;
	AudioConfig(const AudioConfig& other) = default;
	AudioConfig(AudioConfig&& other) = default;
	AudioConfig& operator=(const AudioConfig& other) = default;
	AudioConfig& operator=(AudioConfig&& other) = default;
};

struct AudioBus : public Upp::Moveable<AudioBus> {
	float** channels = nullptr;
	int channel_count = 0;
	int frame_count = 0;

	bool IsValid() const;
	float* GetChannel(int index) const;
	
	// Add explicit constructors for U++ compatibility
	AudioBus() = default;
	AudioBus(const AudioBus& other) = default;
	AudioBus(AudioBus&& other) = default;
	AudioBus& operator=(const AudioBus& other) = default;
	AudioBus& operator=(AudioBus&& other) = default;
};

struct TransportInfo : public Upp::Moveable<TransportInfo> {
	double tempo = 120.0;
	double position_beats = 0.0;
	bool playing = false;
	bool recording = false;
	
	// Add explicit constructors for U++ compatibility
	TransportInfo() = default;
	TransportInfo(const TransportInfo& other) = default;
	TransportInfo(TransportInfo&& other) = default;
	TransportInfo& operator=(const TransportInfo& other) = default;
	TransportInfo& operator=(TransportInfo&& other) = default;
};

struct ModulationBus : public Upp::Moveable<ModulationBus> {
	Upp::Vector<float*> lanes;
	int lane_length = 0;

	void Clear();
	
	// Add explicit constructors for U++ compatibility
	ModulationBus() = default;
	// Note: Cannot have copy constructor because Vector<float*> has deleted copy constructor
	ModulationBus(ModulationBus&& other) = default;
	ModulationBus& operator=(ModulationBus&& other) = default;
};

struct NoteEvent : public Upp::Moveable<NoteEvent> {
	int note = 0;
	int velocity = 0;
	int channel = 0;
	double time = 0.0;
	
	// Add explicit constructors for U++ compatibility
	NoteEvent() = default;
	NoteEvent(const NoteEvent& other) = default;
	NoteEvent(NoteEvent&& other) = default;
	NoteEvent& operator=(const NoteEvent& other) = default;
	NoteEvent& operator=(NoteEvent&& other) = default;
};

struct ControlEvent : public Upp::Moveable<ControlEvent> {
	int controller = 0;
	int value = 0;
	int channel = 0;
	double time = 0.0;
	
	// Add explicit constructors for U++ compatibility
	ControlEvent() = default;
	ControlEvent(const ControlEvent& other) = default;
	ControlEvent(ControlEvent&& other) = default;
	ControlEvent& operator=(const ControlEvent& other) = default;
	ControlEvent& operator=(ControlEvent&& other) = default;
};

struct ProcessContext : public Upp::Moveable<ProcessContext> {
	AudioBus input;
	AudioBus output;
	AudioBus sidechain;
	TransportInfo transport;
	ModulationBus* modulation = nullptr;
	int frames = 0;
	Upp::Vector<NoteEvent>* midi_input = nullptr;
	Upp::Vector<NoteEvent>* midi_output = nullptr;
	Upp::Vector<ControlEvent>* control_input = nullptr;
	Upp::Vector<ControlEvent>* control_output = nullptr;
	
	// Add explicit constructors for U++ compatibility
	ProcessContext() = default;
	// Note: Cannot have copy constructor because it contains pointers to Vector objects
	ProcessContext(ProcessContext&& other) = default;
	ProcessContext& operator=(ProcessContext&& other) = default;
};

struct ParameterDescriptor : public Upp::Moveable<ParameterDescriptor> {
	Upp::String id;
	Upp::String name;
	double min = 0.0;
	double max = 1.0;
	double default_value = 0.0;
	bool automatable = true;
	
	// Add explicit constructors for U++ compatibility
	ParameterDescriptor() = default;
	// Note: Cannot have copy constructor because Upp::String has deleted copy constructor
	ParameterDescriptor(ParameterDescriptor&& other) = default;
	ParameterDescriptor& operator=(ParameterDescriptor&& other) = default;
};

struct ParameterState : public Upp::Moveable<ParameterState> {
	double value = 0.0;
	double smoothing_ms = 0.0;
	
	// Add explicit constructors for U++ compatibility
	ParameterState() = default;
	ParameterState(const ParameterState& other) = default;
	ParameterState(ParameterState&& other) = default;
	ParameterState& operator=(const ParameterState& other) = default;
	ParameterState& operator=(ParameterState&& other) = default;
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
	Upp::Vector<ParameterState> states;
};

class RoutingMap {
public:
	struct Edge : public Upp::Moveable<Edge> {
		Upp::String source;
		Upp::String destination;
		bool active = true;
		
		// Add explicit constructors for U++ compatibility
		Edge() = default;
		// Note: Cannot have copy constructor because Upp::String has deleted copy constructor
		Edge(Edge&& other) = default;
		Edge& operator=(Edge&& other) = default;
	};

	void Add(const Upp::String& source, const Upp::String& destination);
	const Upp::Vector<Edge>& GetEdges() const;

private:
	Upp::Vector<Edge> edges;
};

struct GraphNode : public Upp::Moveable<GraphNode> {
	Upp::String id;
	Upp::String label;
	Upp::String group;
	
	// Add explicit constructors for U++ compatibility
	GraphNode() = default;
	// Note: Cannot have copy constructor because Upp::String has deleted copy constructor
	GraphNode(GraphNode&& other) = default;
	GraphNode& operator=(GraphNode&& other) = default;
};

struct GraphEdge : public Upp::Moveable<GraphEdge> {
	Upp::String from;
	Upp::String to;
	bool audio = false;
	bool control = false;
	bool active = true;
	
	// Add explicit constructors for U++ compatibility
	GraphEdge() = default;
	// Note: Cannot have copy constructor because Upp::String has deleted copy constructor
	GraphEdge(GraphEdge&& other) = default;
	GraphEdge& operator=(GraphEdge&& other) = default;
};

struct GraphVisualization : public Upp::Moveable<GraphVisualization> {
	Upp::Vector<GraphNode> nodes;
	Upp::Vector<GraphEdge> edges;
	void Clear();
	
	// Add explicit constructors for U++ compatibility
	GraphVisualization() = default;
	// Note: Cannot have copy constructor because Vector<GraphNode> and Vector<GraphEdge> have deleted copy constructors
	GraphVisualization(GraphVisualization&& other) = default;
	GraphVisualization& operator=(GraphVisualization&& other) = default;
};

class AnalyzerTap {
public:
	virtual ~AnalyzerTap() {}
	virtual void PublishAnalysis(const ProcessContext& ctx) = 0;
};

class PluginProcessor {
public:
	virtual ~PluginProcessor() {}

	virtual void Prepare(const AudioConfig& config);
	virtual void Reset();
	virtual void Process(ProcessContext& ctx) = 0;

	virtual void SetParameter(const Upp::String& id, double value);
	virtual double GetParameter(const Upp::String& id) const;

	ParameterSet& Parameters();
	const ParameterSet& Parameters() const;
	GraphVisualization& Graph();
	const GraphVisualization& Graph() const;

protected:
	ParameterSet parameter_set;
	AudioConfig current_config;
	GraphVisualization graph;
};

class InstrumentProcessor : public PluginProcessor {
public:
	void NoteOn(const NoteEvent& evt);
	void NoteOff(const NoteEvent& evt);
	void ControlChange(const ControlEvent& evt);
	void AllNotesOff();
};

class MidiEffectProcessor {
public:
	virtual ~MidiEffectProcessor() {}

	virtual void Prepare(const AudioConfig& cfg);
	virtual void Reset();
	virtual void Process(ProcessContext& ctx, Upp::Vector<NoteEvent>& in_notes, Upp::Vector<NoteEvent>& out_notes,
		Upp::Vector<ControlEvent>& in_controls, Upp::Vector<ControlEvent>& out_controls) = 0;

	void SetParameter(const Upp::String& id, double value);
	double GetParameter(const Upp::String& id) const;

	ParameterSet& Parameters();
	const ParameterSet& Parameters() const;
	GraphVisualization& Graph();
	const GraphVisualization& Graph() const;

protected:
	ParameterSet parameter_set;
	AudioConfig current_config;
	GraphVisualization graph;
};

class MidiInstrumentProcessor : public MidiEffectProcessor {
public:
	void Prepare(const AudioConfig& cfg) override;
	void Reset() override;
	void Process(ProcessContext& ctx, Upp::Vector<NoteEvent>& in_notes, Upp::Vector<NoteEvent>& out_notes,
		Upp::Vector<ControlEvent>& in_controls, Upp::Vector<ControlEvent>& out_controls) override;

protected:
	virtual void GeneratePattern(ProcessContext& ctx, Upp::Vector<NoteEvent>& out_notes, Upp::Vector<ControlEvent>& out_controls) = 0;
};

} // namespace PluginSDK

#endif