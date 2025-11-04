#ifndef _DSP_ZenCoreMFXCatalogue_h_
#define _DSP_ZenCoreMFXCatalogue_h_

#include "DSP.h"
using namespace Upp;

namespace DSP {

enum MFXCategory {
    FILTER,
    EQ,
    DYNAMICS,
    MODULATION,
    DELAY,
    REVERB,
    SPECIAL,
    PITCH,
    SPATIAL
};

struct ParameterTemplate : public Moveable<ParameterTemplate> {
    Upp::String id;
    Upp::String name;
    double default_value;
    double min_value;
    double max_value;
    Upp::String unit;  // e.g., "Hz", "%", "dB", ""
    
    ParameterTemplate() : default_value(0.0), min_value(0.0), max_value(1.0) {}
    ParameterTemplate(const Upp::String& param_id, const Upp::String& param_name, 
                     double default_val, double min_val, double max_val, const Upp::String& unit_str = "")
        : id(param_id), name(param_name), default_value(default_val), 
          min_value(min_val), max_value(max_val), unit(unit_str) {}
};

struct MFXAlgorithm : public Moveable<MFXAlgorithm> {
    Upp::String id;
    Upp::String name;
    Upp::String description;
    MFXCategory category;
    bool supports_combination;
    Upp::Vector<ParameterTemplate> parameter_templates;  // Enhanced with templates instead of just names
    Upp::Vector<Upp::String> default_presets;  // Default presets for model expansions
    
    MFXAlgorithm() : category(FILTER), supports_combination(false) {}
    MFXAlgorithm(const Upp::String& alg_id, const Upp::String& alg_name, MFXCategory cat)
        : id(alg_id), name(alg_name), category(cat), supports_combination(true) {}
};

class ZenCoreMFXCatalogue {
public:
    typedef ZenCoreMFXCatalogue CLASSNAME;
    
    ZenCoreMFXCatalogue();
    virtual ~ZenCoreMFXCatalogue();
    
    // Register an MFX algorithm
    void RegisterAlgorithm(const MFXAlgorithm& algorithm);
    
    // Get algorithm by ID
    const MFXAlgorithm* GetAlgorithm(const Upp::String& id) const;
    
    // Enumerate algorithms by category
    Upp::Vector<Upp::String> GetAlgorithmsByCategory(MFXCategory category) const;
    
    // Check if algorithm supports combination
    bool SupportsCombination(const Upp::String& id) const;
    
    // Get all available categories
    Upp::Vector<MFXCategory> GetCategories() const;
    
    // Get algorithm metadata
    ValueMap GetMetadata(const Upp::String& id) const;
    
    // Apply default parameters for specific model expansion
    ValueMap ApplyDefaults(const Upp::String& algorithmId, const Upp::String& modelExpansion) const;
    
    // Get default parameters for a specific model expansion
    ValueMap GetDefaultParameters(const Upp::String& algorithmId, const Upp::String& modelExpansion) const;
    
    // Initialize with ZenCore model expansion defaults
    void InitializeWithModelDefaults();
    
private:
    VectorMap<Upp::String, MFXAlgorithm> algorithms;
    
    // Helper method to set up default parameters for model expansions
    ValueMap GetModelExpansionDefaults(const Upp::String& algorithmId, const Upp::String& modelExpansion) const;
};

}

#endif