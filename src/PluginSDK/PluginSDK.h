#ifndef _PluginSDK_PluginSDK_h_
#define _PluginSDK_PluginSDK_h_

#include <Core/Core.h>

namespace PluginSDK {

struct AudioConfig {
	int sample_rate = 44100;
	int block_size = 0;
	int input_channels = 0;
	int output_channels = 0;
	int sidechain_channels = 0;
};

struct AudioBus {
	float** channels = nullptr;
	int channel_count = 0;
	int frame_count = 0;

	bool IsValid() const;
	float* GetChannel(int index) const;
};

struct TransportInfo {
	double tempo = 120.0;
	double position_beats = 0.0;
	bool playing = false;
	bool recording = false;
};

struct ModulationBus {
	Upp::Vector<float*> lanes;
	int lane_length = 0;

	void Clear();
};

struct NoteEvent {
	int note = 0;
	int velocity = 0;
	int channel = 0;
	double time = 0.0;
};

struct ControlEvent {
	int controller = 0;
	int value = 0;
	int channel = 0;
	double time = 0.0;
};

struct ProcessContext {
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
};

struct ParameterDescriptor {
	Upp::String id;
	Upp::String name;
	double min = 0.0;
	double max = 1.0;
	double default_value = 0.0;
	bool automatable = true;
};

struct ParameterState {
	double value = 0.0;
	double smoothing_ms = 0.0;
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
	struct Edge {
		Upp::String source;
		Upp::String destination;
		bool active = true;
	};

	void Add(const Upp::String& source, const Upp::String& destination);
	const Upp::Vector<Edge>& GetEdges() const;

private:
	Upp::Vector<Edge> edges;
};

struct GraphNode {
	Upp::String id;
	Upp::String label;
	Upp::String group;
};

struct GraphEdge {
	Upp::String from;
	Upp::String to;
	bool audio = false;
	bool control = false;
	bool active = true;
};

struct GraphVisualization {
	Upp::Vector<GraphNode> nodes;
	Upp::Vector<GraphEdge> edges;
	void Clear();
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
