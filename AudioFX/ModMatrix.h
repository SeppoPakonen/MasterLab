#ifndef _AudioFX_ModMatrix_h_
#define _AudioFX_ModMatrix_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "ParameterSet.h"

using namespace Upp;

namespace DSP {

// Enum for modulation sources
enum class ModSource {
    kLFO1,
    kLFO2,
    kEnvelope1,
    kEnvelope2,
    kVelocity,
    kKeyTrack,
    kMIDI_CC1,
    kMIDI_CC2,
    kMIDI_CC3,
    kMIDI_CC4,
    kModWheel,
    kAftertouch,
    kBend,
    kRandom,
    kUser1,
    kUser2
};

// Enum for modulation destinations
enum class ModDestination {
    kOsc1Pitch,
    kOsc2Pitch,
    kOsc1Volume,
    kOsc2Volume,
    kFilterCutoff,
    kFilterResonance,
    kAmpGain,
    kPan,
    kLFO1Rate,
    kLFO2Rate
};

// Simple structure for modulation mapping
struct ModulationMapping {
    ModSource source;
    ModDestination destination;
    ParameterValue amount;
    
    ModulationMapping(ModSource s, ModDestination d, ParameterValue a = 1.0) 
        : source(s), destination(d), amount(a) {}
};

// Modulation matrix for routing modulation sources to destinations
class ModMatrix {
public:
    ModMatrix();
    
    // Add a modulation mapping
    void AddMapping(ModSource source, ModDestination destination, ParameterValue amount = 1.0);
    
    // Remove a modulation mapping
    void RemoveMapping(ModSource source, ModDestination destination);
    
    // Update the modulation matrix with current parameter values
    void Process();
    
    // Get the modulation amount for a specific source/destination pair
    ParameterValue GetModulationAmount(ModSource source, ModDestination destination) const;
    
    // Get all active mappings
    Vector<ModulationMapping> GetMappings() const;
    
    // Clear all mappings
    void Clear();
    
private:
    Vector<ModulationMapping> mappings;
};

} // namespace DSP

#endif