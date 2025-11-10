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
        
        // Default constructor
        Preset() {}
        
        // Constructor with parameters
        Preset(const String& n) : name(n) {}
        
        // Copy constructor
        Preset(const Preset& other) : name(other.name), parameters(other.parameters) {}
        
        // Assignment operator
        Preset& operator=(const Preset& other) {
            if (this != &other) {
                name = other.name;
                parameters = other.parameters;
            }
            return *this;
        }
        
        // Support for U++ container operations
        void  operator<<=(const Preset& s) { name = s.name; parameters = s.parameters; }
        bool  operator==(const Preset& b) const { return name == b.name && parameters == b.parameters; }
        int   Compare(const Preset& b) const { return name.Compare(b.name); }
        
        // U++ guest requirement
        void  Guest() const {}
        
        // Support for U++ deep copy
        void  Move(Preset& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("name", name)("parameters", parameters);
        }
    };

    Vector<Preset> presets;
};


} // namespace AudioFX

// Register AudioFX::PresetManager::Preset as a U++ guest type
namespace Upp {
    template<>
    inline constexpr bool is_upp_guest<AudioFX::PresetManager::Preset> = true;
}

#endif