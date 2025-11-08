#ifndef _AudioFX_PresetManager_h_
#define _AudioFX_PresetManager_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "ParameterSet.h"

using namespace Upp;

namespace AudioFX {

// Preset manager for handling parameter presets
class PresetManager {
public:
    PresetManager();

    // Add a preset with current parameters
    void AddPreset(const ParameterSet& params, const String& name);

    // Load a preset by name
    bool LoadPreset(const String& name, ParameterSet& params);

    // Save current parameters as a preset
    void SavePreset(const ParameterSet& params, const String& name);

    // Delete a preset
    void DeletePreset(const String& name);

    // Get list of available presets
    Vector<String> GetPresetNames() const;

    // Get preset by index
    String GetPresetName(int index) const;

    // Get number of presets
    int GetPresetCount() const;

    // Rename a preset
    void RenamePreset(const String& oldName, const String& newName);

private:
    struct Preset {
        String name;
        ValueMap parameters;
    };

    Vector<Preset> presets;
};

} // namespace AudioFX

#endif