#include "PresetManager.h"
#include "ParameterSet.h"

namespace DSP {

PresetManager::PresetManager() {
}

PresetManager::~PresetManager() {
}

bool PresetManager::LoadPreset(const String& id, ParameterSet& params) {
    int idx = presets.Find(id);
    if (idx >= 0) {
        const Preset& preset = presets[idx];
        
        // Load parameter values from preset
        for (int i = 0; i < preset.parameters.GetCount(); i++) {
            String param_name = preset.parameters.GetKey(i);
            double value = preset.parameters[i];
            params.SetValue(param_name, value);
        }
        return true;
    }
    return false; // Preset not found
}

bool PresetManager::StorePreset(const Preset& preset) {
    presets.GetAdd(preset.id) = preset;
    return true;
}

Vector<String> PresetManager::EnumerateLibrary() const {
    Vector<String> ids;
    for (int i = 0; i < presets.GetCount(); i++) {
        ids.Add(presets.GetKey(i));
    }
    return ids;
}

bool PresetManager::DeletePreset(const String& id) {
    int idx = presets.Find(id);
    if (idx >= 0) {
        presets.Remove(idx);
        return true;
    }
    return false; // Preset not found
}

const Preset* PresetManager::GetPreset(const String& id) const {
    int idx = presets.Find(id);
    if (idx >= 0) {
        return &presets[idx];
    }
    return nullptr;
}

void PresetManager::ConnectToAutomation(ParameterSet& params) {
    // In a real implementation, this would connect the parameters
    // to the automation system so parameter changes are recorded
    // This is a placeholder for the automation bridge functionality
}

}