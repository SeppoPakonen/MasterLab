#include "PluginSDK.h"

namespace PluginSDK {

bool AudioBus::IsValid() const {
	return channels != nullptr && channel_count > 0 && frame_count >= 0;
}

float* AudioBus::GetChannel(int index) const {
	if(!channels || index < 0 || index >= channel_count)
		return nullptr;
	return channels[index];
}

void ModulationBus::Clear() {
	lanes.Clear();
	lane_length = 0;
}

int ParameterSet::Add(const ParameterDescriptor& descriptor) {
	int index = descriptors.GetCount();
	descriptors.Add(descriptor);
	ParameterState& state = states.Add();
	state.value = descriptor.default_value;
	return index;
}

bool ParameterSet::SetValue(int index, double value) {
	if(index < 0 || index >= states.GetCount())
		return false;
	const ParameterDescriptor& desc = descriptors[index];
	states[index].value = Upp::clamp(value, desc.min, desc.max);
	return true;
}

double ParameterSet::GetValue(int index) const {
	if(index < 0 || index >= states.GetCount())
		return 0.0;
	return states[index].value;
}

bool ParameterSet::SetValueById(const String& id, double value) {
	for(int i = 0; i < descriptors.GetCount(); ++i) {
		if(descriptors[i].id == id)
			return SetValue(i, value);
	}
	return false;
}

double ParameterSet::GetValueById(const String& id) const {
	for(int i = 0; i < descriptors.GetCount(); ++i) {
		if(descriptors[i].id == id)
			return states[i].value;
	}
	return 0.0;
}

const ParameterDescriptor* ParameterSet::Find(const String& id) const {
	for(int i = 0; i < descriptors.GetCount(); ++i) {
		if(descriptors[i].id == id)
			return &descriptors[i];
	}
	return nullptr;
}

const Vector<ParameterDescriptor>& ParameterSet::Descriptors() const {
	return descriptors;
}

void RoutingMap::Add(const String& source, const String& destination) {
	Edge& e = edges.Add();
	e.source = source;
	e.destination = destination;
	e.active = true;
}

const Vector<RoutingMap::Edge>& RoutingMap::GetEdges() const {
	return edges;
}

void GraphVisualization::Clear() {
	nodes.Clear();
	edges.Clear();
}

void PluginProcessor::Prepare(const AudioConfig& config) {
	current_config = config;
}

void PluginProcessor::Reset() {
}

void PluginProcessor::SetParameter(const String& id, double value) {
	parameter_set.SetValueById(id, value);
}

double PluginProcessor::GetParameter(const String& id) const {
	return parameter_set.GetValueById(id);
}

ParameterSet& PluginProcessor::Parameters() {
	return parameter_set;
}

const ParameterSet& PluginProcessor::Parameters() const {
	return parameter_set;
}

GraphVisualization& PluginProcessor::Graph() {
	return graph;
}

const GraphVisualization& PluginProcessor::Graph() const {
	return graph;
}

void InstrumentProcessor::NoteOn(const NoteEvent&) {
}

void InstrumentProcessor::NoteOff(const NoteEvent&) {
}

void InstrumentProcessor::ControlChange(const ControlEvent&) {
}

void InstrumentProcessor::AllNotesOff() {
}

void MidiEffectProcessor::Prepare(const AudioConfig& cfg) {
	current_config = cfg;
}

void MidiEffectProcessor::Reset() {
}

void MidiEffectProcessor::SetParameter(const String& id, double value) {
	parameter_set.SetValueById(id, value);
}

double MidiEffectProcessor::GetParameter(const String& id) const {
	return parameter_set.GetValueById(id);
}

ParameterSet& MidiEffectProcessor::Parameters() {
	return parameter_set;
}

const ParameterSet& MidiEffectProcessor::Parameters() const {
	return parameter_set;
}

GraphVisualization& MidiEffectProcessor::Graph() {
	return graph;
}

const GraphVisualization& MidiEffectProcessor::Graph() const {
	return graph;
}

void MidiInstrumentProcessor::Prepare(const AudioConfig& cfg) {
	MidiEffectProcessor::Prepare(cfg);
}

void MidiInstrumentProcessor::Reset() {
	MidiEffectProcessor::Reset();
}

void MidiInstrumentProcessor::Process(ProcessContext& ctx, Vector<NoteEvent>& in_notes, Vector<NoteEvent>& out_notes,
	Vector<ControlEvent>& in_controls, Vector<ControlEvent>& out_controls) {
	(void)in_notes;
	(void)in_controls;
	GeneratePattern(ctx, out_notes, out_controls);
}

} // namespace PluginSDK
