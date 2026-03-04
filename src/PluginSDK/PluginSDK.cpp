#include "PluginSDK.h"
#include "PluginTypes.h"

namespace PluginSDK {

void PluginProcessor::Prepare(const AudioConfig& config) { current_config = config; }
void PluginProcessor::Reset() {}
void PluginProcessor::SetParameter(const Upp::String& id, double value) { parameter_set.SetValueById(id, value); }
double PluginProcessor::GetParameter(const Upp::String& id) const { return parameter_set.GetValueById(id); }
ParameterSet& PluginProcessor::Parameters() { return parameter_set; }
const ParameterSet& PluginProcessor::Parameters() const { return parameter_set; }
GraphVisualization& PluginProcessor::Graph() { return graph; }
const GraphVisualization& PluginProcessor::Graph() const { return graph; }

int ParameterSet::Add(const ParameterDescriptor& descriptor) {
    int index = descriptors.GetCount();
    descriptors.Add(descriptor);
    states.Add(descriptor.default_value);
    return index;
}

bool ParameterSet::SetValue(int index, double value) {
    if (index >= 0 && index < descriptors.GetCount()) {
        const auto& desc = descriptors[index];
        states[index] = Upp::clamp(value, desc.min, desc.max);
        return true;
    }
    return false;
}

double ParameterSet::GetValue(int index) const {
    if (index >= 0 && index < states.GetCount()) {
        return states[index];
    }
    return 0.0;
}

bool ParameterSet::SetValueById(const Upp::String& id, double value) {
    for (int i = 0; i < descriptors.GetCount(); ++i) {
        if (descriptors[i].id == id) {
            return SetValue(i, value);
        }
    }
    return false;
}

double ParameterSet::GetValueById(const Upp::String& id) const {
    for (int i = 0; i < descriptors.GetCount(); ++i) {
        if (descriptors[i].id == id) {
            return GetValue(i);
        }
    }
    return 0.0;
}

const ParameterDescriptor* ParameterSet::Find(const Upp::String& id) const {
    for (int i = 0; i < descriptors.GetCount(); ++i) {
        if (descriptors[i].id == id) {
            return &descriptors[i];
        }
    }
    return nullptr;
}

const Upp::Vector<ParameterDescriptor>& ParameterSet::Descriptors() const {
    return descriptors;
}

bool AudioBus::IsValid() const {
    return channels != nullptr && channel_count > 0 && frame_count > 0;
}

float* AudioBus::GetChannel(int index) const {
    if (index >= 0 && index < channel_count) {
        return channels[index];
    }
    return nullptr;
}

} // namespace PluginSDK
