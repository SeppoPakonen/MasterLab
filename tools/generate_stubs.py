#!/usr/bin/env python3
import re
from pathlib import Path

REPO = Path(__file__).resolve().parents[1]
EFFECTS_MD = REPO / "EFFECTS.md"
INSTRUMENTS_MD = REPO / "INSTRUMENTS.md"

EFFECTS_SECTIONS = {
	"Antares Pitch & Vocal Suite (Antares)": "PitchVocalSuite",
	"Arturia Analog FX Inserts (Arturia)": "AnalogFxInserts",
	"KRISTAL ToneBooster Essentials (KRISTAL)": "ToneboosterEssentials",
	"Steinberg Dynamics & Level (Steinberg)": "DynamicsLevelSuite",
	"Steinberg Harmonic & Amp (Steinberg)": "HarmonicAmpSuite",
	"Steinberg Delay & Reverb (Steinberg)": "DelayReverbSuite",
	"Steinberg Modulation & Spatial (Steinberg)": "ModSpatialSuite",
	"Steinberg Filter & Sound Design (Steinberg)": "FilterDesignSuite",
	"Steinberg Pitch & Time (Steinberg)": "PitchTimeSuite",
	"Steinberg Analysis & Utility (Steinberg)": "AnalysisUtilitySuite",
	"Steinberg Restoration & Noise (Steinberg)": "RestorationNoiseSuite",
	"Waves Signature Series (Waves)": "SignatureChainSuite",
	"Waves Analog Channel & Console (Waves)": "AnalogConsoleSuite",
	"Waves Dynamics & Control (Waves)": "DynamicsControlSuite",
	"Waves Mastering & Linear Phase (Waves)": "MasteringLinearSuite",
	"Waves Reverb & Delay (Waves)": "ReverbDelaySuite",
	"Waves Modulation & Creative FX (Waves)": "ModCreativeSuite",
	"Waves Pitch & Vocal (Waves)": "PitchVocalCollection",
	"Waves Spatial & Surround (Waves)": "SpatialSurroundSuite",
	"Waves Guitar & Instrument (Waves)": "GuitarInstrumentSuite",
	"Waves Restoration & Noise (Waves)": "RestorationNoiseCollection",
	"Waves Metering & Analysis (Waves)": "MeteringAnalysisSuite",
	"Roland Zenology FX (Roland)": "ZenCoreFxRack",
	"APU Loudness Suite (APU)": "LoudnessControlSuite",
	"Cymatics Vocal Design (Cymatics)": "VocalDesignRack",
	"iZotope Voice & Mix Suite (iZotope)": "VoiceMixSuite",
	"Replay Neural Voice (Replay)": "NeuralVoiceChanger",
	"Synchro Arts Alignment (Synchro Arts)": "VocalAlignmentEngine",
	"Steinberg SpectraLayers FX (Steinberg)": "SpectralLayersFx",
	"KSHMR Essentials (Dharma Worldwide)": "EssentialMacroFx",
	"Celemony Melodyne (Celemony)": "PolyphonicPitchEditor",
	"Crave DSP Transient Control (Crave DSP)": "TransientEqDesigner",
	"FabFilter Timeless (FabFilter)": "TimelessDualDelay",
	"Sonible SmartReverb (Sonible)": "AdaptiveSmartReverb",
	"Sugar Bytes Effectrix (Sugar Bytes)": "SequenceFxEngine",
	"W.A. Production Kick Suite (W.A. Production)": "KickShapingSuite",
	"Native Instruments Guitar Rig (Native Instruments)": "ModularGuitarRig",
	"Waves AI Assistance & Collaboration (Waves)": "AiAssistSuite",
	"Waves Vocal & Live Utilities (Waves)": "VocalLiveUtilities",
	"Waves Harmonics & Dynamics (Waves)": "HarmonicsDynamicsSuite",
	"Waves Reverb & Ambience (Waves)": "ReverbAmbienceSuite",
	"Waves Spatial & Immersive (Waves)": "SpatialImmersiveSuite",
	"Waves Guitar & Instrument Platforms (Waves)": "GuitarInstrumentPlatforms"
}

INSTRUMENT_SECTIONS = {
	"Roland Zenology Workstation (Roland)": "ZenCoreWorkstation",
	"Roland JX-8P Model Expansion (Roland)": "ZenModelJX8P",
	"Roland JUNO-106 Model Expansion (Roland)": "ZenModelJUNO106",
	"Big Fish Audio Momentum (Big Fish Audio)": "MomentumLoopStation",
	"reFX Nexus Workstation (reFX)": "LayeredRompler",
	"Toontrack Songwriting Instruments (Toontrack)": "SongwriterInstrumentPack",
	"LennarDigital Sylenth1 (LennarDigital)": "VirtualAnalogStack",
	"TAL Sampler (Togu Audio Line)": "VintageSampler",
	"Native Instruments Core Synths (Native Instruments)": "CoreSynthCollection",
	"Waves Instrument Suite (Waves)": "StudioInstrumentSuite"
}


def parse_sections(path):
	sections = {}
	current = None
	table_buffer = []

	def flush_table():
		nonlocal table_buffer, current
		if not current or not table_buffer:
			table_buffer = []
			return
		table = parse_table(table_buffer)
		if table:
			current.setdefault("tables", []).append(table)
		table_buffer = []

	with path.open("r", encoding="utf-8") as fh:
		for raw_line in fh:
			line = raw_line.rstrip("\n")
			if line.startswith("## "):
				flush_table()
				title = line[3:].strip()
				current = {"title": title, "description": [], "tables": []}
				sections[title] = current
				continue
			if line.startswith("### "):
				flush_table()
				title = line[4:].strip()
				current = {"title": title, "description": [], "tables": []}
				sections[title] = current
				continue
			if current is None:
				continue
			if line.startswith("|"):
				table_buffer.append(line)
				continue
			if table_buffer:
				flush_table()
			stripped = line.strip()
			if stripped:
				current["description"].append(stripped)
	flush_table()
	return sections


def parse_table(lines):
	if len(lines) < 3:
		return []
	header = [col.strip() for col in lines[0].strip("|").split("|")]
	rows = []
	for line in lines[2:]:
		if not line.startswith("|"):
			continue
		cells = [cell.strip() for cell in line.strip("|").split("|")]
		if len(cells) != len(header):
			continue
		row = {}
		for key, value in zip(header, cells):
			row[key] = value.replace("<br>", "\n")
		rows.append(row)
	return rows


def vendor_and_name(title):
	vendor = None
	match = re.search(r"\(([^)]+)\)", title)
	if match:
		vendor = match.group(1).strip()
	base = title.split("(")[0].strip()
	if vendor and base.lower().startswith(vendor.lower()):
		base = base[len(vendor):].strip(" -")
	return vendor, base if base else title


def camel_to_header(name):
	parts = re.findall(r"[A-Z][a-z0-9]*|[0-9]+", name)
	return " ".join(parts) if parts else name


def write_stub(directory, class_name, display_name, data, is_effect):
	directory.mkdir(parents=True, exist_ok=True)
	agent_path = directory / "AGENTS.md"
	header_path = directory / f"{class_name}.h"
	source_path = directory / f"{class_name}.cpp"
	upp_path = directory / f"{class_name}.upp"

	vendor, base_display = vendor_and_name(data["title"])
	if display_name is None:
		display_name = camel_to_header(class_name)
	title = f"# {display_name} {'Effect' if is_effect else 'Instrument'} Stub"

	lines = [title, ""]
	lines.append("## Reference")
	lines.append(f"- Inspired by: {base_display}")
	lines.append(f"- Vendor: {vendor or 'Independent'}")
	src_column = "Referenced plug-ins" if any("Referenced plug-ins" in row for table in data["tables"] for row in table) else "Referenced instruments"
	referenced = []
	for table in data["tables"]:
		for row in table:
			if src_column in row:
				referenced.append(row[src_column])
	if referenced:
		lines.append(f"- Source catalog: {', '.join(referenced)}")

	if data["description"]:
		lines.append("")
		lines.append("## Summary")
		lines.append("\n".join(data["description"]))

	lines.append("")
	lines.append("## Implementation Plan")

	# Add graph metadata and parameter scaffolding information
	graph_metadata = []
	parameter_scaffolding = []
	
	for table in data["tables"]:
		for row in table:
			group_name = row.get("Group") or camel_to_header(class_name)
			lines.append(f"### {group_name}")
			lines.append(f"- Category: {row.get('Category', 'n/a')}")
			sidechain = row.get("Sidechain") or row.get("Side chain") or "n/a"
			lines.append(f"- Sidechain: {sidechain}")
			blueprint = row.get("Generic blueprint") or row.get("Goal") or ""
			if blueprint:
				lines.append(f"- Processing blueprint: {blueprint}")
			key_features = [item.strip() for item in (row.get("Key features") or "").split("\n") if item.strip()]
			if key_features:
				lines.append("- Key features:")
				for feat in key_features:
					lines.append(f"  - {feat}")
			core_classes = [item.strip() for item in (row.get("Core classes") or "").split("\n") if item.strip()]
			if core_classes:
				lines.append("- Core building blocks:")
				for cls in core_classes:
					lines.append(f"  - {cls}")
			signal = row.get("Signal flow") or row.get("Voice graph") or ""
			if signal:
				lines.append(f"- Signal/voice flow: {signal}")
			
			# Extract graph metadata and parameter information
			if signal:
				graph_metadata.append(signal)  # Capture signal flow information
			if key_features:
				parameter_scaffolding.extend(key_features)  # Use key features as parameter info

			lines.append("- TODO:")
			lines.append("  - Wire PluginSDK parameter/route scaffolding to match the modules above")
			lines.append("  - Flesh out processing graph and automation surfaces per EFFECTS/INSTRUMENTS blueprint")
			lines.append("")

	agent_path.write_text("\n".join(lines).rstrip() + "\n", encoding="utf-8")

	# Enhanced namespace determination for different plugin types
	if "MIDI" in str(data["title"]).upper():
		namespace = "MidiEffects" if is_effect else "MidiInstruments"
	elif is_effect:
		namespace = "Effects"
	else:
		namespace = "Instruments"
		
	base_class = "PluginSDK::PluginProcessor" if is_effect else "PluginSDK::InstrumentProcessor"

	header_guard = f"_{'midieffects' if 'MIDI' in str(data['title']).upper() else 'effects' if is_effect else 'instruments'}_{class_name.lower()}_{class_name.lower()}_h_"
	
	# Enhanced header with comprehensive graph and parameter definitions
	header_lines = [
		f"#ifndef {header_guard}",
		f"#define {header_guard}",
		"",
		"#include <PluginSDK/PluginSDK.h>",
		"#include <AudioCore/AudioCore.h>  // For DSP infrastructure",
		"#include <DSP/DSP.h>              // For DSP processing components",
		"#include <AudioUI/GraphVisualizationCtrl.h>  // For graph visualization",
		"",
		f"namespace {namespace} {{",
		"",
		"// Graph Node Definition for signal routing",
		"struct GraphNode {",
		"\tString nodeId;",
		"\tString nodeType; // e.g., 'oscillator', 'filter', 'envelope', 'lfo', 'eq', 'compressor'",",
		"\tVector<String> inputs;   // input node IDs",
		"\tVector<String> outputs;  // output node IDs",
		"\tValueMap parameters;     // node parameters",
		"\tint order;               // processing order",
		"};",
		"",
		f"// {class_name} Graph Visualization Extension",
		f"class {class_name}Graph : public PluginSDK::GraphVisualization {{",
		"public:",
		f"\t{class_name}Graph();",
		"\tvirtual ~{class_name}Graph();",
		"",
		"\t// Initialize the graph structure for this plugin",
		"\tvoid InitializeGraph();",
		"",
		"\t// Update graph based on current parameter state",
		"\tvoid UpdateGraph();",
		"",
		"\t// Get the visualization for UI components",
		"\tconst UI::GraphVisualizationCtrl& GetVisualizationCtrl() const;",
		"",
		"private:",
		"\tVector<GraphNode> graph_nodes;",
		"\tVectorMap<String, int> node_lookup;  // Maps node IDs to indices",
		"\tUI::GraphVisualizationCtrl viz_ctrl;",
		"};",
		"",
		"// Parameter Definition for UI and automation",
		"enum ParameterId {",
		"\tkParameter1 = 0,",
		"\tkParameter2,",
		"\tkParameter3,",
		"\tkParameter4,",
		"\tkParameter5,",
		"\tkParameter6,",
		"\tkParameter7,",
		"\tkParameter8,",
		"\tkParameterCount  // This will be customized per plugin",
		"};",
		"",
		f"class {class_name} : public {base_class} {{",
		"public:",
		f"\ttypedef {class_name} CLASSNAME;",
		f"\t{class_name}();",
		"\tvirtual ~{class_name}();",
		"",
		"\tvoid Prepare(const PluginSDK::AudioConfig& cfg) override;",
		"\tvoid Process(PluginSDK::ProcessContext& ctx) override;",
		"\tvoid Reset() override;",
		"",
		"\t// Graph Management Methods",
		"\tvoid InitializeGraph();",
		"\tvoid ProcessGraph(PluginSDK::ProcessContext& ctx);",
		"\tvoid UpdateParameter(int index, double value);",
		"",
		"\t// Parameter Access Methods",
		"\tint GetNumParameters() const override;",
		"\tdouble GetParameter(int index) const override;",
		"\tvoid SetParameter(int index, double value) override;",
		"\tString GetParameterName(int index) const override;",
		"\tString GetParameterText(int index) const override;",
		"",
		"\t// Graph Visualization Integration",
		"\t{class_name}Graph& GetGraph() { return graph; }",
		"\tconst {class_name}Graph& GetGraph() const { return graph; }",
		"",
		"\t// MIDI Processing Methods (if applicable)",
		"\tvoid ProcessMidiEvents(const Upp::Vector<PluginSDK::MidiEvent>& events);",
		"\tvoid RouteMidiEvent(const PluginSDK::MidiEvent& evt);",
	]

	if not is_effect:
		header_lines.extend([
			"\tvoid NoteOn(const PluginSDK::NoteEvent& evt) override;",
			"\tvoid NoteOff(const PluginSDK::NoteEvent& evt) override;",
			"\tvoid AllNotesOff() override;",
			"\tvoid PolyPressure(const PluginSDK::NoteEvent& evt) override;",  # For MIDI Polyphonic Expression support
		])

	header_lines.extend([
		"",
		"private:",
		"\tPluginSDK::RoutingMap routing;",
		"\tVector<GraphNode> graphNodes;      // Processing graph nodes",
		"\tVector<double> parameters;         // Parameter values",
		"\tVector<String> parameterNames;     // Parameter names for UI",
		"\tVector<String> parameterTexts;     // Parameter value texts",
		"\tValueMap graphMetadata;            // Graph metadata",
		"\t{class_name}Graph graph;           // Graph visualization interface",
		"",
		"\t// Internal processing methods",
		"\tvoid ProcessNode(const GraphNode& node, PluginSDK::ProcessContext& ctx);",
		"\tvoid UpdateGraphRouting();",
		"\tvoid UpdateVisualization();        // Update visualization when parameters change",
		"};",
		"",
		f"}} // namespace {namespace}",
		"",
		"#endif",
	])

	header_path.write_text("\n".join(header_lines) + "\n", encoding="utf-8")

	# Enhanced source file with comprehensive graph and parameter implementation
	source_lines = [
		f"#include \"{class_name}.h\"",
		"",
		f"namespace {namespace} {{",
		"",
		"#region {class_name}Graph Implementation",
		"",
		f"{class_name}Graph::{class_name}Graph() {{",
		"\t// Initialize the graph visualization for this plugin",
		"\tInitializeGraph();",
		"}",
		"",
		f"{class_name}Graph::~{class_name}Graph() {{",
		"\t// Cleanup resources",
		"}",
		"",
		f"void {class_name}Graph::InitializeGraph() {{",
		"\t// Define the processing graph based on plugin architecture",
		"\t// This is highly plugin-specific and should be customized",
		"",
		"\t// Clear any existing nodes",
		"\tgraph_nodes.Clear();",
		"\tnode_lookup.Clear();",
		"",
		"\t// Example graph for a typical effect plugin:",
		"\t// Input -> Processing -> Output",
		"",
		"\tGraphNode input_node;",
		'\tinput_node.nodeId = "input";',
		'\tinput_node.nodeType = "input";',
		"\tinput_node.order = 0;",
		'\tgraph_nodes.Add(input_node);',
		'\tnode_lookup.GetAdd("input") = graph_nodes.GetCount() - 1;',
		"",
		"\tGraphNode output_node;",
		'\toutput_node.nodeId = "output";',
		'\toutput_node.nodeType = "output";',
		"\toutput_node.order = 1000;",
		'\tgraph_nodes.Add(output_node);',
		'\tnode_lookup.GetAdd("output") = graph_nodes.GetCount() - 1;',
		"",
		"\t// Add processing nodes based on the plugin type",
		"\t// This would be customized for each specific plugin",
		"}",
		"",
		f"void {class_name}Graph::UpdateGraph() {{",
		"\t// Update graph based on current parameter state",
		"\t// This allows visualization to react to parameter changes",
		"}",
		"",
		f"const UI::GraphVisualizationCtrl& {class_name}Graph::GetVisualizationCtrl() const {{",
		"\treturn viz_ctrl;",
		"}",
		"",
		"#endregion",
		"",
		"#region {class_name} Implementation",
		"",
		f"{class_name}::{class_name}() {{",
		"\t// Initialize parameter container",
		"\tparameters.SetCount(kParameterCount);",
		"\tparameterNames.SetCount(kParameterCount);",
		"\tparameterTexts.SetCount(kParameterCount);",
		"",
		"\t// Initialize default parameter values (these should be customized per plugin)",
		"\tparameters.Fill(0.5);  // Default mid-point for all parameters",
		"",
		"\t// Initialize parameter names (customize per plugin)",
		'\tparameterNames[kParameter1] = "Parameter 1";',
		'\tparameterNames[kParameter2] = "Parameter 2";',
		'\tparameterNames[kParameter3] = "Parameter 3";',
		'\tparameterNames[kParameter4] = "Parameter 4";',
		'\tparameterNames[kParameter5] = "Parameter 5";',
		'\tparameterNames[kParameter6] = "Parameter 6";',
		'\tparameterNames[kParameter7] = "Parameter 7";',
		'\tparameterNames[kParameter8] = "Parameter 8";',
		"",
		"\t// Initialize graph structure",
		"\tInitializeGraph();",
		"}",
		"",
		f"{class_name}::~{class_name}() {{",
		"\t// Cleanup resources",
		"}",
		"",
		f"void {class_name}::Prepare(const PluginSDK::AudioConfig& cfg) {{",
		"\tPluginSDK::PluginProcessor::Prepare(cfg);",
		"\t(void)cfg;",
		"\t// TODO: Allocate resources based on cfg",
		"\tUpdateGraphRouting();",
		"}",
		"",
		f"void {class_name}::Reset() {{",
		"\tPluginSDK::PluginProcessor::Reset();",
		"\t// Reset internal state",
		"\tInitializeGraph();",
		"}",
		"",
		f"void {class_name}::Process(PluginSDK::ProcessContext& ctx) {{",
		"\t// Process through the graph",
		"\tProcessGraph(ctx);",
		"",
		"\t// Update visualization if there are changes to visualize",
		"\tUpdateVisualization();",
		"}",
		"",
		"// Graph Management Methods",
		f"void {class_name}::InitializeGraph() {{",
		"\t// Initialize plugin-specific graph structure",
		"\tgraphNodes.Clear();",
		"",
		"\t// Create default processing graph nodes based on plugin architecture",
		"\tGraphNode inputNode;",
		'\tinputNode.nodeId = "input";',
		'\tinputNode.nodeType = "input";',
		'\tinputNode.order = 0;',
		'\tgraphNodes.Add(inputNode);',
		"",
		"\tGraphNode outputNode;",
		'\toutputNode.nodeId = "output";',
		'\toutputNode.nodeType = "output";',
		'\toutputNode.order = 1000;',
		'\tgraphNodes.Add(outputNode);',
		"",
		"\t// Add plugin-specific processing nodes here",
		"\t// This should be customized per plugin implementation",
		"}",
		"",
		f"void {class_name}::ProcessGraph(PluginSDK::ProcessContext& ctx) {{",
		"\t// Process the signal through the graph",
		"\t// Sort nodes by processing order",
		"\t// In a real implementation, this would use topological sort based on connections",
		"",
		"\t// Process each node in order",
		"\tfor (const auto& node : graphNodes) {",
		"\t\tProcessNode(node, ctx);",
		"\t}", 
		"}",
		"",
		f"void {class_name}::ProcessNode(const GraphNode& node, PluginSDK::ProcessContext& ctx) {{",
		"\t// Process the specific node based on its type",
		'\tif (node.nodeType == "input") {',
		"\t\t// Input node - read from context",
		"\t} else if (node.nodeType == " 'output") {',
		"\t\t// Output node - write to context",
		"\t} else {",
		"\t\t// Processing node - apply effect/instrument logic",
		"\t\t// This will be customized per plugin implementation",
		"\t}",
		"}",
		"",
		f"void {class_name}::UpdateGraphRouting() {{",
		"\t// Update routing based on current graph configuration",
		"\t// This connects the graph nodes according to their inputs/outputs",
		"}",
		"",
		"// Parameter Access Methods",
		f"int {class_name}::GetNumParameters() const {{",
		"\treturn kParameterCount;",
		"}",
		"",
		f"double {class_name}::GetParameter(int index) const {{",
		"\tif (index >= 0 && index < parameters.GetCount()) {",
		"\t\treturn parameters[index];",
		"\t}",
		"\treturn 0.0;",
		"}",
		"",
		f"void {class_name}::SetParameter(int index, double value) {{",
		"\tif (index >= 0 && index < parameters.GetCount()) {",
		"\t\tparameters[index] = Clamp(value, 0.0, 1.0);  // Clamp between 0 and 1",
		"\t\tUpdateParameter(index, value);  // Update internal state",
		"\t}",
		"}",
		"",
		f"void {class_name}::UpdateParameter(int index, double value) {{",
		"\t// Update internal state based on parameter change",
		"\t// This will be customized per plugin implementation",
		"",
		"\tswitch(index) {",
		"\t\tcase kParameter1:",
		"\t\t\t// Process parameter 1 change",
		"\t\t\tbreak;",
		"\t\tcase kParameter2:",
		"\t\t\t// Process parameter 2 change",
		"\t\t\tbreak;",
		"\t\t// Add cases for other parameters",
		"\t\tdefault:",
		"\t\t\tbreak;",
		"\t}",
		"}",
		"",
		f"String {class_name}::GetParameterName(int index) const {{",
		"\tif (index >= 0 && index < parameterNames.GetCount()) {",
		"\t\treturn parameterNames[index];",
		"\t}",
		"\treturn \"\";",
		"}",
		"",
		f"String {class_name}::GetParameterText(int index) const {{",
		"\tif (index >= 0 && index < parameterTexts.GetCount()) {",
		"\t\treturn parameterTexts[index];",
		"\t}",
		"\treturn \"\";",
		"}",
		"",
		f"void {class_name}::UpdateVisualization() {{",
		"\t// Update the visualization to reflect current state",
		"\t// This sends current graph state to the UI visualization",
		"}",
		""
	]

	if not is_effect:
		source_lines.extend([
			f"void {class_name}::NoteOn(const PluginSDK::NoteEvent& evt) {{",
			"\tPluginSDK::InstrumentProcessor::NoteOn(evt);",
			"\t// Dispatch note-on to voice manager",
			"}",
			"",
			f"void {class_name}::NoteOff(const PluginSDK::NoteEvent& evt) {{",
			"\tPluginSDK::InstrumentProcessor::NoteOff(evt);",
			"\t// Dispatch note-off to voice manager",
			"}",
			"",
			f"void {class_name}::AllNotesOff() {{",
			"\tPluginSDK::InstrumentProcessor::AllNotesOff();",
			"\t// Reset all envelopes/voices",
			"}",
			"",
			f"void {class_name}::PolyPressure(const PluginSDK::NoteEvent& evt) {{",
			"\t// Handle MIDI polyphonic pressure (MPE) events",
			"\t// This is required for MPE-compatible instruments",
			"}",
			"",
		])

	# Add MIDI processing methods
	source_lines.extend([
		f"void {class_name}::ProcessMidiEvents(const Upp::Vector<PluginSDK::MidiEvent>& events) {{",
		"\t// Process incoming MIDI events",
		"\tfor(const auto& evt : events) {",
		"\t\tRouteMidiEvent(evt);",
		"\t}",
		"}",
		"",
		f"void {class_name}::RouteMidiEvent(const PluginSDK::MidiEvent& evt) {{",
		"\t// Route MIDI events to appropriate handlers based on event type",
		"\tswitch(evt.GetType()) {",
		"\t\tcase PluginSDK::MidiEvent::NOTE_ON:",
		"\t\t\tNoteOn(evt.AsNoteEvent());",
		"\t\t\tbreak;",
		"\t\tcase PluginSDK::MidiEvent::NOTE_OFF:",
		"\t\t\tNoteOff(evt.AsNoteEvent());",
		"\t\t\tbreak;",
		"\t\tcase PluginSDK::MidiEvent::CONTROL_CHANGE:",
		"\t\t\t// Process control change",
		"\t\t\tbreak;",
		"\t\tcase PluginSDK::MidiEvent::POLY_PRESSURE:",
		"\t\t\t// Process polyphonic pressure",
		"\t\t\tbreak;",
		"\t\tcase PluginSDK::MidiEvent::PITCH_BEND:",
		"\t\t\t// Process pitch bend",
		"\t\t\tbreak;",
		"\t\tdefault:",
		"\t\t\t// Other MIDI events",
		"\t\t\tbreak;",
		"\t}",
		"}",
		"",
		f"}} // namespace {namespace}",
		""
	])

	source_path.write_text("\n".join(source_lines), encoding="utf-8")

	# Enhanced .upp file with graph visualization support
	upp_lines = [
		"description \"" + ('MIDI ' if 'MIDI' in str(data['title']).upper() 
		                    else ('Effect' if is_effect else 'Instrument')) + f" Plugin: {display_name}\\377200,200,200\";",
		"",
		"uses",
		"\tCtrlLib,",
		"\tPluginSDK,",
		"\tAudioCore,",
		"\tDSP,", 
		"\tAudioUI;",
		"",
		"file",
		"\tAGENTS.md,",
		f"\t{class_name}.h,",
		f"\t{class_name}.cpp;",
	]
	upp_path.write_text("\n".join(upp_lines) + "\n", encoding="utf-8")


def main():
	effects_sections = parse_sections(EFFECTS_MD)
	instrument_sections = parse_sections(INSTRUMENTS_MD)

	effects_root = REPO / "effects"
	instruments_root = REPO / "instruments"
	effects_root.mkdir(exist_ok=True)
	instruments_root.mkdir(exist_ok=True)

	for title, class_name in EFFECTS_SECTIONS.items():
		if title not in effects_sections:
			continue
		data = effects_sections[title]
		display = camel_to_header(class_name)
		write_stub(effects_root / class_name, class_name, display, data, is_effect=True)

	for title, class_name in INSTRUMENT_SECTIONS.items():
		if title not in instrument_sections:
			continue
		data = instrument_sections[title]
		display = camel_to_header(class_name)
		write_stub(instruments_root / class_name, class_name, display, data, is_effect=False)


if __name__ == "__main__":
	main()
