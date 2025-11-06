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
    int steps;         // For discrete parameters
    Upp::String group; // Parameter grouping (e.g., "Filter", "Oscillator", "Envelope")
    bool automatable;  // Whether this parameter can be automated
    
    ParameterTemplate() : default_value(0.0), min_value(0.0), max_value(1.0), 
                         steps(0), automatable(true) {}
    ParameterTemplate(const Upp::String& param_id, const Upp::String& param_name, 
                     double default_val, double min_val, double max_val, 
                     const Upp::String& unit_str = "", int num_steps = 0,
                     const Upp::String& param_group = "", bool auto_able = true)
        : id(param_id), name(param_name), default_value(default_val), 
          min_value(min_val), max_value(max_val), unit(unit_str), 
          steps(num_steps), group(param_group), automatable(auto_able) {}
};

struct ParameterPreset : public Moveable<ParameterPreset> {
    Upp::String id;
    Upp::String name;
    Upp::String algorithm_id;
    ValueMap parameter_values;       // Parameter ID to value mapping
    Upp::String description;
    Upp::String model_expansion;     // Specific model expansion this preset is for
    Time creation_time;
    
    ParameterPreset() { creation_time = GetSysTime(); }
    ParameterPreset(const Upp::String& preset_id, const Upp::String& preset_name, 
                   const Upp::String& alg_id)
        : id(preset_id), name(preset_name), algorithm_id(alg_id) { 
            creation_time = GetSysTime(); 
        }
};

struct MFXAlgorithm : public Moveable<MFXAlgorithm> {
    Upp::String id;
    Upp::String name;
    Upp::String description;
    MFXCategory category;
    bool supports_combination;
    Upp::Vector<ParameterTemplate> parameter_templates;  // Enhanced with templates instead of just names
    Upp::Vector<Upp::String> default_presets;  // Default presets for model expansions
    Upp::Vector<String> supported_model_expansions; // List of supported model expansions
    Upp::ValueMap category_defaults;  // Default parameter values per model expansion
    
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
    
    // Parameter preset management
    void AddParameterPreset(const ParameterPreset& preset);
    bool RemovePreset(const Upp::String& presetId);
    const ParameterPreset* GetPreset(const Upp::String& presetId) const;
    Vector<String> GetPresetsForAlgorithm(const String& algorithmId) const;
    Vector<String> GetPresetsForModelExpansion(const String& modelExpansion) const;
    
    // Apply preset to parameter values
    ValueMap ApplyPreset(const String& presetId, const ValueMap& currentParams) const;
    
    // Model expansion management
    Vector<String> GetSupportedModelExpansions() const;
    Vector<String> GetAlgorithmsForModelExpansion(const String& modelExpansion) const;
    
    // Template-based parameter validation
    bool ValidateParameterValue(const String& algorithmId, const String& paramId, double value) const;
    bool ValidateParameters(const String& algorithmId, const ValueMap& params) const;
    
    // Bulk parameter management
    ValueMap GetDefaultParameterSet(const String& algorithmId) const;
    ValueMap GetModelExpansionParameterSet(const String& algorithmId, const String& modelExpansion) const;
    
private:
    VectorMap<Upp::String, MFXAlgorithm> algorithms;
    VectorMap<Upp::String, ParameterPreset> presets;
    VectorMap<Upp::String, Vector<Upp::String>> model_expansion_algorithms; // Maps model expansions to algorithms
    
    // Helper method to set up default parameters for model expansions
    ValueMap GetModelExpansionDefaults(const Upp::String& algorithmId, const Upp::String& modelExpansion) const;
    
    // Initialize common model expansion defaults
    void InitializeModelExpansionDefaults();
    
    // Add a model expansion to the algorithm
    void AddModelExpansionToAlgorithm(const Upp::String& algorithmId, const Upp::String& expansion);
};

}

#endif