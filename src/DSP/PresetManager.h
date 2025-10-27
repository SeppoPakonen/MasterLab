#ifndef _DSP_PresetManager_h_
#define _DSP_PresetManager_h_

#include "DSP.h"
#include <pluginSDK/PluginSDK.h>  // For parameter integration
using namespace Upp;

namespace DSP {

struct Preset {
    String id;
    String name;
    String description;
    ValueMap parameters;  // Map of parameter names to values
    
    Preset() {}
    Preset(const String& preset_id, const String& preset_name) 
        : id(preset_id), name(preset_name) {}
};

class PresetManager {
public:
    typedef PresetManager CLASSNAME;
    
    PresetManager();
    virtual ~PresetManager();
    
    // Load a preset by ID
    bool LoadPreset(const String& id, ParameterSet& params);
    
    // Store a preset
    bool StorePreset(const Preset& preset);
    
    // Enumerate all available presets in the library
    Vector<String> EnumerateLibrary() const;
    
    // Delete a preset
    bool DeletePreset(const String& id);
    
    // Get preset by ID
    const Preset* GetPreset(const String& id) const;
    
    // Bridge to automation system
    void ConnectToAutomation(ParameterSet& params);
    
private:
    VectorMap<String, Preset> presets;
};

}

#endif