#ifndef _PluginSDK_PluginSDK_h_
#define _PluginSDK_PluginSDK_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>

namespace PluginSDK {

struct AudioConfig : public Upp::Moveable<AudioConfig> {
	int sample_rate = 44100;
	int input_channels = 2;
	int output_channels = 2;
	int buffer_size = 512;
	
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
	
	AudioBus() = default;
	AudioBus(const AudioBus& other) = default;
	AudioBus(AudioBus&& other) = default;
	AudioBus& operator=(const AudioBus& other) = default;
	AudioBus& operator=(AudioBus&& other) = default;
};

struct TransportInfo : public Upp::Moveable<TransportInfo> {
	double bpm = 120.0;
	double position_beats = 0.0;
	bool playing = false;
	bool recording = false;
	
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
	
	ModulationBus() = default;
	ModulationBus(ModulationBus&& other) = default;
	ModulationBus& operator=(ModulationBus&& other) = default;
};

struct NoteEvent : public Upp::Moveable<NoteEvent> {
	int note = 0;
	int velocity = 0;
	int channel = 0;
	double time = 0.0;
	
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
	
	ControlEvent() = default;
	ControlEvent(const ControlEvent& other) = default;
	ControlEvent(ControlEvent&& other) = default;
	ControlEvent& operator=(const ControlEvent& other) = default;
	ControlEvent& operator=(ControlEvent&& other) = default;
};

struct ProcessContext : public Upp::Moveable<ProcessContext> {
	int frames = 0;
	double sample_rate = 44100.0;
	AudioBus input;
	AudioBus output;
	AudioBus sidechain;
	TransportInfo transport;
	ModulationBus modulation;
	
	ProcessContext() = default;
	ProcessContext(const ProcessContext& other) = delete; // ModulationBus has Vector<float*>
	ProcessContext(ProcessContext&& other) = default;
	ProcessContext& operator=(const ProcessContext& other) = delete;
	ProcessContext& operator=(ProcessContext&& other) = default;
};

struct GraphNode : public Upp::Moveable<GraphNode> {
	Upp::String id;
	Upp::String label;
	Upp::String group;
	Upp::Point pos;
	Upp::Color color;
	
	GraphNode() = default;
	GraphNode(const GraphNode& other) = default;
	GraphNode(GraphNode&& other) = default;
	GraphNode& operator=(const GraphNode& other) = default;
	GraphNode& operator=(GraphNode&& other) = default;
};

struct GraphEdge : public Upp::Moveable<GraphEdge> {
	Upp::String from;
	Upp::String to;
	bool audio = true;
	bool control = false;
	
	GraphEdge() = default;
	GraphEdge(const GraphEdge& other) = default;
	GraphEdge(GraphEdge&& other) = default;
	GraphEdge& operator=(const GraphEdge& other) = default;
	GraphEdge& operator=(GraphEdge&& other) = default;
};

struct GraphVisualization : public Upp::Moveable<GraphVisualization> {
	Upp::Vector<GraphNode> nodes;
	Upp::Vector<GraphEdge> edges;
	
	void Clear();

	GraphVisualization() = default;
	GraphVisualization(const GraphVisualization& other) = delete;
	GraphVisualization(GraphVisualization&& other) = default;
	GraphVisualization& operator=(const GraphVisualization& other) = delete;
	GraphVisualization& operator=(GraphVisualization&& other) = default;
};

struct ParameterDescriptor : public Upp::Moveable<ParameterDescriptor> {
	Upp::String id;
	Upp::String name;
	double min = 0.0;
	double max = 1.0;
	double default_value = 0.0;
	bool automatable = true;

	ParameterDescriptor() = default;
	ParameterDescriptor(const ParameterDescriptor& other) = default;
	ParameterDescriptor& operator=(const ParameterDescriptor& other) = default;
	ParameterDescriptor(ParameterDescriptor&& other) = default;
	ParameterDescriptor& operator=(ParameterDescriptor&& other) = default;
};

struct ParameterState : public Upp::Moveable<ParameterState> {
	double value = 0.0;
	double smoothing_ms = 0.0;

	ParameterState() = default;
	ParameterState(const ParameterState& other) = default;
	ParameterState& operator=(const ParameterState& other) = default;
	ParameterState(ParameterState&& other) = default;
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
		Upp::String from;
		Upp::String to;
		bool active = true;
		
		Edge() = default;
		Edge(const Edge& other) = default;
		Edge(Edge&& other) = default;
		Edge& operator=(const Edge& other) = default;
		Edge& operator=(Edge&& other) = default;
	};

	void Add(const Upp::String& source, const Upp::String& destination);
	const Upp::Vector<Edge>& GetEdges() const;

private:
	Upp::Vector<Edge> edges;
};

class PluginProcessor {
public:
	virtual ~PluginProcessor() {}

	virtual void Prepare(const AudioConfig& config);
	virtual void Reset();
	virtual void Process(ProcessContext& ctx) = 0;

	virtual void SetParameter(const Upp::String& id, double value);
	virtual double GetParameter(const Upp::String& id) const;
	
	virtual Upp::String GetURI() const { return ""; }
	virtual Upp::String GetName() const { return "Plugin"; }

	ParameterSet& Parameters();
	const ParameterSet& Parameters() const;
	GraphVisualization& Graph();
	const GraphVisualization& Graph() const;

protected:
	ParameterSet parameter_set;
	AudioConfig current_config;
	GraphVisualization graph;
};

class PluginEditor : public Upp::Ctrl {
public:
	typedef PluginEditor CLASSNAME;
	PluginEditor() {}
	virtual ~PluginEditor() {}

	virtual void SetProcessor(PluginProcessor* p) { processor = p; }
	virtual void SyncToProcessor() {}
	virtual void SyncFromProcessor() {}

protected:
	PluginProcessor* processor = nullptr;
};

class PluginWindow : public Upp::TopWindow {
public:
	typedef PluginWindow CLASSNAME;
	PluginWindow() {
		Sizeable().Zoomable();
		SetRect(0, 0, 800, 600);
		AddFrame(menuBar);
	}

	void SetEditor(PluginEditor& e) {
		if(editor) editor->Remove();
		editor = &e;
		Add(e.SizePos());
	}
	
	void SetMenuBar(void (*menu)(Upp::Bar&)) {
		menuBar.Set(menu);
	}

private:
	PluginEditor* editor = nullptr;
	Upp::MenuBar menuBar;
};

class InstrumentProcessor : public PluginProcessor {
public:
	virtual void NoteOn(const NoteEvent&);
	virtual void NoteOff(const NoteEvent&);
	virtual void ControlChange(const ControlEvent&);
	virtual void AllNotesOff();
};

class MidiEffectProcessor {
public:
	virtual ~MidiEffectProcessor() {}
	
	virtual void Prepare(const AudioConfig& config);
	virtual void Reset();
	virtual void SetParameter(const Upp::String& id, double value);
	virtual double GetParameter(const Upp::String& id) const;
	
	ParameterSet& Parameters();
	const ParameterSet& Parameters() const;
	GraphVisualization& Graph();
	const GraphVisualization& Graph() const;

	virtual void Process(ProcessContext& ctx, Upp::Vector<NoteEvent>& in_notes, Upp::Vector<NoteEvent>& out_notes, 
	                     Upp::Vector<ControlEvent>& in_controls, Upp::Vector<ControlEvent>& out_controls) = 0;

protected:
	ParameterSet parameter_set;
	AudioConfig current_config;
	GraphVisualization graph;
};

class MidiInstrumentProcessor : public MidiEffectProcessor {
public:
	virtual void Prepare(const AudioConfig& cfg) override;
	virtual void Reset() override;
	virtual void Process(ProcessContext& ctx, Upp::Vector<NoteEvent>& in_notes, Upp::Vector<NoteEvent>& out_notes, 
	                     Upp::Vector<ControlEvent>& in_controls, Upp::Vector<ControlEvent>& out_controls) override;

protected:
	virtual void GeneratePattern(ProcessContext& ctx, Upp::Vector<NoteEvent>& out_notes, Upp::Vector<ControlEvent>& out_controls) = 0;
};

} // namespace PluginSDK

#endif
