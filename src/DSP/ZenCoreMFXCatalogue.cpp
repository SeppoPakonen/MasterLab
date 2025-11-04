#include "ZenCoreMFXCatalogue.h"

namespace DSP {

ZenCoreMFXCatalogue::ZenCoreMFXCatalogue() {
}

ZenCoreMFXCatalogue::~ZenCoreMFXCatalogue() {
}

void ZenCoreMFXCatalogue::RegisterAlgorithm(const MFXAlgorithm& algorithm) {
    // Since MFXAlgorithm contains Vector members that can't be copied,
    // we'll use a different approach - create a new one and assign fields individually
    MFXAlgorithm& alg = algorithms.GetAdd(algorithm.id);
    alg.id = algorithm.id;
    alg.name = algorithm.name;
    alg.description = algorithm.description;
    alg.category = algorithm.category;
    alg.supports_combination = algorithm.supports_combination;
    alg.parameter_templates <<= algorithm.parameter_templates;
    alg.default_presets <<= algorithm.default_presets;
}

const MFXAlgorithm* ZenCoreMFXCatalogue::GetAlgorithm(const Upp::String& id) const {
    int idx = algorithms.Find(id);
    if (idx >= 0) {
        return &algorithms[idx];
    }
    return nullptr;
}

Upp::Vector<Upp::String> ZenCoreMFXCatalogue::GetAlgorithmsByCategory(MFXCategory category) const {
    Upp::Vector<Upp::String> result;
    for (int i = 0; i < algorithms.GetCount(); i++) {
        if (algorithms[i].category == category) {
            result.Add(algorithms.GetKey(i));
        }
    }
    return result;
}

bool ZenCoreMFXCatalogue::SupportsCombination(const Upp::String& id) const {
    int idx = algorithms.Find(id);
    if (idx >= 0) {
        return algorithms[idx].supports_combination;
    }
    return false;
}

Upp::Vector<MFXCategory> ZenCoreMFXCatalogue::GetCategories() const {
    Upp::Vector<MFXCategory> categories;
    Upp::Vector<bool> seen_category(9, false); // Assuming 9 categories based on enum
    
    for (int i = 0; i < algorithms.GetCount(); i++) {
        MFXCategory cat = algorithms[i].category;
        if (!seen_category[cat]) {
            categories.Add(cat);
            seen_category[cat] = true;
        }
    }
    return categories;
}

ValueMap ZenCoreMFXCatalogue::GetMetadata(const Upp::String& id) const {
    ValueMap metadata;
    int idx = algorithms.Find(id);
    if (idx >= 0) {
        const MFXAlgorithm& alg = algorithms[idx];
        metadata.Set("id", alg.id);
        metadata.Set("name", alg.name);
        metadata.Set("description", alg.description);
        metadata.Set("category", (int)alg.category);
        metadata.Set("supports_combination", alg.supports_combination);
        
        // Enhanced parameter information with templates
        ValueArray paramTemplates;
        for (const ParameterTemplate& param : alg.parameter_templates) {
            ValueMap paramInfo;
            paramInfo.Set("id", param.id);
            paramInfo.Set("name", param.name);
            paramInfo.Set("default_value", param.default_value);
            paramInfo.Set("min_value", param.min_value);
            paramInfo.Set("max_value", param.max_value);
            paramInfo.Set("unit", param.unit);
            paramTemplates.Add(paramInfo);
        }
        metadata.Set("parameter_templates", paramTemplates);
        
        // Default presets for model expansions
        ValueArray presets;
        for (const Upp::String& preset : alg.default_presets) {
            presets.Add(preset);
        }
        metadata.Set("default_presets", presets);
    }
    return metadata;
}

ValueMap ZenCoreMFXCatalogue::ApplyDefaults(const Upp::String& algorithmId, const Upp::String& modelExpansion) const {
    ValueMap defaults = GetDefaultParameters(algorithmId, modelExpansion);
    
    // If specific model defaults aren't found, return basic algorithm defaults
    if (defaults.GetCount() == 0) {
        int idx = algorithms.Find(algorithmId);
        if (idx >= 0) {
            const MFXAlgorithm& alg = algorithms[idx];
            for (const ParameterTemplate& param : alg.parameter_templates) {
                defaults.Set(param.id, param.default_value);
            }
        }
    }
    
    return defaults;
}

ValueMap ZenCoreMFXCatalogue::GetDefaultParameters(const Upp::String& algorithmId, const Upp::String& modelExpansion) const {
    ValueMap params = GetModelExpansionDefaults(algorithmId, modelExpansion);
    
    // If specific model defaults aren't found, return basic algorithm defaults
    if (params.GetCount() == 0) {
        int idx = algorithms.Find(algorithmId);
        if (idx >= 0) {
            const MFXAlgorithm& alg = algorithms[idx];
            for (const ParameterTemplate& param : alg.parameter_templates) {
                params.Set(param.id, param.default_value);
            }
        }
    }
    
    return params;
}

void ZenCoreMFXCatalogue::InitializeWithModelDefaults() {
    // Initialize with common ZenCore model expansion defaults
    // This would typically be called during system startup
    
    // Example: Add some defaults for common model expansions
    MFXAlgorithm chorus;
    chorus.id = "ZC_CHORUS";
    chorus.name = "ZenCore Chorus";
    chorus.description = "Classic chorus effect from ZenCore";
    chorus.category = MODULATION;
    chorus.supports_combination = true;
    
    // Add parameter templates with defaults
    ParameterTemplate rate("rate", "Rate", 1.0, 0.1, 10.0, "Hz");
    ParameterTemplate depth("depth", "Depth", 0.5, 0.0, 1.0, "");
    ParameterTemplate feedback("feedback", "Feedback", 0.3, 0.0, 0.9, "");
    ParameterTemplate mix("mix", "Mix", 0.5, 0.0, 1.0, "");
    
    chorus.parameter_templates.Add(rate);
    chorus.parameter_templates.Add(depth);
    chorus.parameter_templates.Add(feedback);
    chorus.parameter_templates.Add(mix);
    
    // Add default presets for model expansions
    chorus.default_presets.Add("JX-8P Clean");
    chorus.default_presets.Add("JUNO-106 Vintage");
    chorus.default_presets.Add("Analog Warm");
    
    RegisterAlgorithm(chorus);
    
    // Add other common algorithms with their parameter templates...
    MFXAlgorithm reverb;
    reverb.id = "ZC_REVERB";
    reverb.name = "ZenCore Reverb";
    reverb.description = "Studio-quality reverb from ZenCore";
    reverb.category = REVERB;
    reverb.supports_combination = true;
    
    ParameterTemplate time("time", "Time", 2.0, 0.1, 10.0, "s");
    ParameterTemplate size("size", "Size", 0.8, 0.1, 1.0, "");
    ParameterTemplate damp("damp", "Damping", 0.5, 0.0, 1.0, "");
    ParameterTemplate early_refl("early_refl", "Early Reflections", 0.3, 0.0, 1.0, "");
    
    reverb.parameter_templates.Add(time);
    reverb.parameter_templates.Add(size);
    reverb.parameter_templates.Add(damp);
    reverb.parameter_templates.Add(early_refl);
    
    reverb.default_presets.Add("JX-8P Hall");
    reverb.default_presets.Add("JUNO-106 Room");
    reverb.default_presets.Add("Plate Classic");
    
    RegisterAlgorithm(reverb);
}

ValueMap ZenCoreMFXCatalogue::GetModelExpansionDefaults(const Upp::String& algorithmId, const Upp::String& modelExpansion) const {
    ValueMap defaults;
    int idx = algorithms.Find(algorithmId);
    
    if (idx >= 0) {
        const MFXAlgorithm& alg = algorithms[idx];
        
        // For model-specific defaults, we could have preset mappings
        if (modelExpansion == "JX-8P" || modelExpansion.Find("JX-8P") >= 0) {
            // JX-8P defaults for this algorithm
            for (const ParameterTemplate& param : alg.parameter_templates) {
                if (param.id == "rate") {
                    defaults.Set(param.id, param.default_value * 1.2); // Slightly faster
                } else if (param.id == "depth") {
                    defaults.Set(param.id, param.default_value * 0.8); // Slightly less deep
                } else {
                    defaults.Set(param.id, param.default_value);
                }
            }
        } else if (modelExpansion == "JUNO-106" || modelExpansion.Find("JUNO-106") >= 0) {
            // JUNO-106 defaults for this algorithm
            for (const ParameterTemplate& param : alg.parameter_templates) {
                if (param.id == "feedback") {
                    defaults.Set(param.id, min(param.max_value, param.default_value * 1.5)); // More feedback
                } else {
                    defaults.Set(param.id, param.default_value);
                }
            }
        } else {
            // Return basic algorithm defaults if no specific model match
            for (const ParameterTemplate& param : alg.parameter_templates) {
                defaults.Set(param.id, param.default_value);
            }
        }
    }
    
    return defaults;
}

}
