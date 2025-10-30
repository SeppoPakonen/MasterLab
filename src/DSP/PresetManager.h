#ifndef _DSP_PresetManager_h_
#define _DSP_PresetManager_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

struct Preset : public Moveable<Preset> {
    Upp::String id;
    Upp::String name;
    Upp::String description;
    ValueMap parameters;  // Map of parameter names to values
    
    Preset() {}
    Preset(const Upp::String& preset_id, const Upp::String& preset_name) 
        : id(preset_id), name(preset_name) {}
};

class PresetManager {
public:
    typedef PresetManager CLASSNAME;
    
    PresetManager();
    virtual ~PresetManager();
    
    // Load a preset by ID
    bool LoadPreset(const Upp::String& id, ParameterSet& params);
    
    // Store a preset
    bool StorePreset(const Preset& preset);
    
    // Enumerate all available presets in the library
    Upp::Vector<Upp::String> EnumerateLibrary() const;
    
    // Delete a preset
    bool DeletePreset(const Upp::String& id);
    
    // Get preset by ID
    const Preset* GetPreset(const Upp::String& id) const;
    
    // Bridge to automation system
    void ConnectToAutomation(ParameterSet& params);
    
private:
    VectorMap<Upp::String, Preset> presets;
};

}

#endif