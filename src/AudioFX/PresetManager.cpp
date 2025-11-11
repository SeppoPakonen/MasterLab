#include "PresetManager.h"

namespace AudioFX {

PresetManager::PresetManager() {
    // Initialize with no presets
}

void PresetManager::AddPreset(const ParameterSet& params, const String& name) {
    Preset preset;
    preset.name = name;

    // Save current parameter values
    Vector<ParameterId> ids = params.GetParameterIds();
    for (const auto& id : ids) {
        preset.parameters.Set(id, params.Get(id));
    }

    presets.Add(pick(preset));
}

bool PresetManager::LoadPreset(const String& name, ParameterSet& params) {
    for (const auto& preset : presets) {
        if (preset.name == name) {
            // Restore parameters from preset
            for (int i = 0; i < preset.parameters.GetCount(); i++) {
                params.Set(preset.parameters.GetKey(i), (double)preset.parameters[i]);
            }
            return true;
        }
    }
    return false;
}

void PresetManager::SavePreset(const ParameterSet& params, const String& name) {
    // Check if preset with this name already exists and update it
    for (auto& preset : presets) {
        if (preset.name == name) {
            // Update existing preset
            preset.parameters.Clear();

            Vector<ParameterId> ids = params.GetParameterIds();
            for (const auto& id : ids) {
                preset.parameters.Set(id, params.Get(id));
            }
            return;
        }
    }

    // Add new preset if it doesn't exist
    AddPreset(params, name);
}

void PresetManager::DeletePreset(const String& name) {
    for (int i = 0; i < presets.GetCount(); i++) {
        if (presets[i].name == name) {
            presets.Remove(i);
            return;
        }
    }
}

Vector<String> PresetManager::GetPresetNames() const {
    Vector<String> names;
    for (const auto& preset : presets) {
        names.Add(preset.name);
    }
    return names;
}

String PresetManager::GetPresetName(int index) const {
    if (index >= 0 && index < presets.GetCount()) {
        return presets[index].name;
    }
    return "";
}

int PresetManager::GetPresetCount() const {
    return presets.GetCount();
}

void PresetManager::RenamePreset(const String& oldName, const String& newName) {
    for (auto& preset : presets) {
        if (preset.name == oldName) {
            preset.name = newName;
            return;
        }
    }
}

} // namespace AudioFX