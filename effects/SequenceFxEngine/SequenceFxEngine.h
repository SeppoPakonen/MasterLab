#ifndef _effects_sequencefxengine_sequencefxengine_h_
#define _effects_sequencefxengine_sequencefxengine_h_

#include <PluginSDK/PluginSDK.h>
#include <AudioCore/AudioCore.h>  // For DSP infrastructure
#include <DSP/DSP.h>              // For DSP processing components
#include <AudioUI/GraphVisualizationCtrl.h>  // For graph visualization

namespace Effects {

// Graph Node Definition for signal routing
struct GraphNode {
	String nodeId;
	String nodeType; // e.g., 'oscillator', 'filter', 'envelope', 'lfo', 'eq', 'compressor'
	Vector<String> inputs;   // input node IDs
	Vector<String> outputs;  // output node IDs
	ValueMap parameters;     // node parameters
	int order;               // processing order
};

// SequenceFxEngine Graph Visualization Extension
class SequenceFxEngineGraph : public PluginSDK::GraphVisualization {
public:
	SequenceFxEngineGraph();
	virtual ~SequenceFxEngineGraph();

	// Initialize the graph structure for this plugin
	void InitializeGraph();

	// Update graph based on current parameter state
	void UpdateGraph();

	// Get the visualization for UI components
	const UI::GraphVisualizationCtrl& GetVisualizationCtrl() const;

private:
	Vector<GraphNode> graph_nodes;
	VectorMap<String, int> node_lookup;  // Maps node IDs to indices
	UI::GraphVisualizationCtrl viz_ctrl;
};

// Parameter Definition for UI and automation
enum ParameterId {
	kParameter1 = 0,
	kParameter2,
	kParameter3,
	kParameter4,
	kParameter5,
	kParameter6,
	kParameter7,
	kParameter8,
	kParameterCount  // This will be customized per plugin
};

class SequenceFxEngine : public PluginSDK::PluginProcessor {
public:
	typedef SequenceFxEngine CLASSNAME;
	SequenceFxEngine();
	virtual ~SequenceFxEngine();

	void Prepare(const PluginSDK::AudioConfig& cfg) override;
	void Process(PluginSDK::ProcessContext& ctx) override;
	void Reset() override;

	// Graph Management Methods
	void InitializeGraph();
	void ProcessGraph(PluginSDK::ProcessContext& ctx);
	void UpdateParameter(int index, double value);

	// Parameter Access Methods
	int GetNumParameters() const override;
	double GetParameter(int index) const override;
	void SetParameter(int index, double value) override;
	String GetParameterName(int index) const override;
	String GetParameterText(int index) const override;

	// Graph Visualization Integration
	SequenceFxEngineGraph& GetGraph() { return graph; }
	const SequenceFxEngineGraph& GetGraph() const { return graph; }

	// MIDI Processing Methods (if applicable)
	void ProcessMidiEvents(const Upp::Vector<PluginSDK::MidiEvent>& events);
	void RouteMidiEvent(const PluginSDK::MidiEvent& evt);

private:
	PluginSDK::RoutingMap routing;
	Vector<GraphNode> graphNodes;      // Processing graph nodes
	Vector<double> parameters;         // Parameter values
	Vector<String> parameterNames;     // Parameter names for UI
	Vector<String> parameterTexts;     // Parameter value texts
	ValueMap graphMetadata;            // Graph metadata
	SequenceFxEngineGraph graph;           // Graph visualization interface

	// Internal processing methods
	void ProcessNode(const GraphNode& node, PluginSDK::ProcessContext& ctx);
	void UpdateGraphRouting();
	void UpdateVisualization();        // Update visualization when parameters change
};

} // namespace Effects

#endif
