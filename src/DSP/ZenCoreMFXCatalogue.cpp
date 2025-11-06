#include "ZenCoreMFXCatalogue.h"

namespace DSP {

ZenCoreMFXCatalogue::ZenCoreMFXCatalogue() {
    // Initialize with model expansion defaults
    InitializeWithModelDefaults();
    InitializeModelExpansionDefaults();
}

ZenCoreMFXCatalogue::~ZenCoreMFXCatalogue() {
}

void ZenCoreMFXCatalogue::RegisterAlgorithm(const MFXAlgorithm& algorithm) {
    // Register the algorithm
    MFXAlgorithm& alg = algorithms.GetAdd(algorithm.id);
    alg.id = algorithm.id;
    alg.name = algorithm.name;
    alg.description = algorithm.description;
    alg.category = algorithm.category;
    alg.supports_combination = algorithm.supports_combination;
    alg.parameter_templates <<= algorithm.parameter_templates;
    alg.default_presets <<= algorithm.default_presets;
    alg.supported_model_expansions <<= algorithm.supported_model_expansions;
    alg.category_defaults = algorithm.category_defaults;
    
    // Register the algorithm with its model expansions
    for(const String& expansion : algorithm.supported_model_expansions) {
        AddModelExpansionToAlgorithm(algorithm.id, expansion);
    }
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
            paramInfo.Set("steps", param.steps);
            paramInfo.Set("group", param.group);
            paramInfo.Set("automatable", param.automatable);
            paramTemplates.Add(paramInfo);
        }
        metadata.Set("parameter_templates", paramTemplates);
        
        // Default presets for model expansions
        ValueArray presets;
        for (const Upp::String& preset : alg.default_presets) {
            presets.Add(preset);
        }
        metadata.Set("default_presets", presets);
        
        // Supported model expansions
        ValueArray expansions;
        for (const String& exp : alg.supported_model_expansions) {
            expansions.Add(exp);
        }
        metadata.Set("supported_model_expansions", expansions);
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
                // Check if this parameter has a default for the specific model expansion
                String key = modelExpansion + "_" + param.id;
                if (alg.category_defaults.Find(key) >= 0) {
                    params.Set(param.id, alg.category_defaults[key]);
                } else {
                    params.Set(param.id, param.default_value);
                }
            }
        }
    }
    
    return params;
}

void ZenCoreMFXCatalogue::InitializeWithModelDefaults() {
    // Initialize with common ZenCore model expansion defaults
    // This would typically be called during system startup
}

void ZenCoreMFXCatalogue::InitializeModelExpansionDefaults() {
    // Enhanced initialization with more model-specific defaults
    
    // Add JX-8P model expansion defaults
    MFXAlgorithm jx8p_filter;
    jx8p_filter.id = "ZC_JX8P_FILTER";
    jx8p_filter.name = "ZenCore JX-8P Filter";
    jx8p_filter.description = "Emulation of JX-8P filter section";
    jx8p_filter.category = FILTER;
    jx8p_filter.supports_combination = false;
    
    // Add JX-8P specific parameter templates
    ParameterTemplate cutoff("cutoff", "Cutoff", 1000.0, 20.0, 20000.0, "Hz", 0, "Filter");
    ParameterTemplate resonance("resonance", "Resonance", 0.7, 0.0, 4.0, "", 0, "Filter", true);
    ParameterTemplate env_mod("env_mod", "Env.Mod", 0.5, 0.0, 1.0, "", 0, "Filter", true);
    ParameterTemplate kbd_track("kbd_track", "KBD Track", 0.5, 0.0, 1.0, "", 0, "Filter", true);
    
    jx8p_filter.parameter_templates.Add(cutoff);
    jx8p_filter.parameter_templates.Add(resonance);
    jx8p_filter.parameter_templates.Add(env_mod);
    jx8p_filter.parameter_templates.Add(kbd_track);
    
    // Set JX-8P specific defaults in category_defaults
    jx8p_filter.category_defaults.Set("JX-8P_cutoff", 2000.0);
    jx8p_filter.category_defaults.Set("JX-8P_resonance", 1.2);
    jx8p_filter.category_defaults.Set("JX-8P_env_mod", 0.7);
    jx8p_filter.category_defaults.Set("JX-8P_kbd_track", 1.0);
    
    // Add to supported expansions
    jx8p_filter.supported_model_expansions.Add("JX-8P");
    jx8p_filter.supported_model_expansions.Add("JX-08");
    
    RegisterAlgorithm(jx8p_filter);
    
    // Add JUNO-106 model expansion defaults
    MFXAlgorithm juno106_filter;
    juno106_filter.id = "ZC_JUNO106_FILTER";
    juno106_filter.name = "ZenCore JUNO-106 Filter";
    juno106_filter.description = "Emulation of JUNO-106 filter section";
    juno106_filter.category = FILTER;
    juno106_filter.supports_combination = false;
    
    // Add JUNO-106 specific parameter templates
    ParameterTemplate juno_cutoff("cutoff", "Cutoff", 2000.0, 20.0, 20000.0, "Hz", 0, "Filter");
    ParameterTemplate juno_resonance("resonance", "Resonance", 0.3, 0.0, 1.0, "", 0, "Filter", true);
    ParameterTemplate juno_env_mod("env_mod", "Env.Mod", 0.3, 0.0, 1.0, "", 0, "Filter", true);
    ParameterTemplate juno_kbd_track("kbd_track", "KBD Track", 0.5, 0.0, 1.0, "", 0, "Filter", true);
    
    juno106_filter.parameter_templates.Add(juno_cutoff);
    juno106_filter.parameter_templates.Add(juno_resonance);
    juno106_filter.parameter_templates.Add(juno_env_mod);
    juno106_filter.parameter_templates.Add(juno_kbd_track);
    
    // Set JUNO-106 specific defaults
    juno106_filter.category_defaults.Set("JUNO-106_cutoff", 5000.0);
    juno106_filter.category_defaults.Set("JUNO-106_resonance", 0.7);
    juno106_filter.category_defaults.Set("JUNO-106_env_mod", 0.5);
    juno106_filter.category_defaults.Set("JUNO-106_kbd_track", 0.0);
    
    // Add to supported expansions
    juno106_filter.supported_model_expansions.Add("JUNO-106");
    juno106_filter.supported_model_expansions.Add("JUNO-6");
    
    RegisterAlgorithm(juno106_filter);
    
    // Add Chorus algorithm with model-specific defaults
    MFXAlgorithm chorus;
    chorus.id = "ZC_CHORUS";
    chorus.name = "ZenCore Chorus";
    chorus.description = "Classic chorus effect from ZenCore";
    chorus.category = MODULATION;
    chorus.supports_combination = true;
    
    // Add parameter templates with defaults
    ParameterTemplate rate("rate", "Rate", 1.0, 0.1, 10.0, "Hz", 0, "Modulation");
    ParameterTemplate depth("depth", "Depth", 0.5, 0.0, 1.0, "", 0, "Modulation", true);
    ParameterTemplate feedback("feedback", "Feedback", 0.3, 0.0, 0.9, "", 0, "Modulation", true);
    ParameterTemplate mix("mix", "Mix", 0.5, 0.0, 1.0, "", 0, "Output", true);
    
    chorus.parameter_templates.Add(rate);
    chorus.parameter_templates.Add(depth);
    chorus.parameter_templates.Add(feedback);
    chorus.parameter_templates.Add(mix);
    
    // Set model-specific defaults
    chorus.category_defaults.Set("JX-8P_rate", 0.8);
    chorus.category_defaults.Set("JX-8P_depth", 0.6);
    chorus.category_defaults.Set("JUNO-106_rate", 1.2);
    chorus.category_defaults.Set("JUNO-106_depth", 0.4);
    
    // Add to supported expansions
    chorus.supported_model_expansions.Add("JX-8P");
    chorus.supported_model_expansions.Add("JUNO-106");
    chorus.supported_model_expansions.Add("Generic");
    
    RegisterAlgorithm(chorus);
    
    // Add additional algorithms for other model expansions...
    MFXAlgorithm reverb;
    reverb.id = "ZC_REVERB";
    reverb.name = "ZenCore Reverb";
    reverb.description = "Studio-quality reverb from ZenCore";
    reverb.category = REVERB;
    reverb.supports_combination = true;
    
    ParameterTemplate time("time", "Time", 2.0, 0.1, 10.0, "s", 0, "Reverb");
    ParameterTemplate size("size", "Size", 0.8, 0.1, 1.0, "", 0, "Reverb", true);
    ParameterTemplate damp("damp", "Damping", 0.5, 0.0, 1.0, "", 0, "Reverb", true);
    ParameterTemplate early_refl("early_refl", "Early Reflections", 0.3, 0.0, 1.0, "", 0, "Reverb", true);
    
    reverb.parameter_templates.Add(time);
    reverb.parameter_templates.Add(size);
    reverb.parameter_templates.Add(damp);
    reverb.parameter_templates.Add(early_refl);
    
    // Set model-specific defaults
    reverb.category_defaults.Set("JX-8P_time", 1.8);
    reverb.category_defaults.Set("JX-8P_damp", 0.4);
    reverb.category_defaults.Set("JUNO-106_time", 2.5);
    reverb.category_defaults.Set("JUNO-106_size", 0.9);
    
    // Add to supported expansions
    reverb.supported_model_expansions.Add("JX-8P");
    reverb.supported_model_expansions.Add("JUNO-106");
    reverb.supported_model_expansions.Add("Generic");
    
    RegisterAlgorithm(reverb);
}

ValueMap ZenCoreMFXCatalogue::GetModelExpansionDefaults(const Upp::String& algorithmId, const Upp::String& modelExpansion) const {
    ValueMap defaults;
    int idx = algorithms.Find(algorithmId);
    
    if (idx >= 0) {
        const MFXAlgorithm& alg = algorithms[idx];
        
        // Check if there are specific defaults for this model expansion
        bool has_model_defaults = false;
        for (int i = 0; i < alg.parameter_templates.GetCount(); i++) {
            const ParameterTemplate& param = alg.parameter_templates[i];
            String key = modelExpansion + "_" + param.id;
            if (alg.category_defaults.Find(key) >= 0) {
                defaults.Set(param.id, alg.category_defaults[key]);
                has_model_defaults = true;
            }
        }
        
        if (!has_model_defaults) {
            // If no model-specific defaults, return basic algorithm defaults
            for (const ParameterTemplate& param : alg.parameter_templates) {
                defaults.Set(param.id, param.default_value);
            }
        }
    }
    
    return defaults;
}

void ZenCoreMFXCatalogue::AddParameterPreset(const ParameterPreset& preset) {
    presets.GetAdd(preset.id) = preset;
}

bool ZenCoreMFXCatalogue::RemovePreset(const Upp::String& presetId) {
    int idx = presets.Find(presetId);
    if (idx >= 0) {
        presets.RemoveKey(presetId);
        return true;
    }
    return false;
}

const ParameterPreset* ZenCoreMFXCatalogue::GetPreset(const Upp::String& presetId) const {
    int idx = presets.Find(presetId);
    if (idx >= 0) {
        return &presets[idx];
    }
    return nullptr;
}

Vector<String> ZenCoreMFXCatalogue::GetPresetsForAlgorithm(const String& algorithmId) const {
    Vector<String> result;
    for (int i = 0; i < presets.GetCount(); i++) {
        if (presets[i].algorithm_id == algorithmId) {
            result.Add(presets.GetKey(i));
        }
    }
    return result;
}

Vector<String> ZenCoreMFXCatalogue::GetPresetsForModelExpansion(const String& modelExpansion) const {
    Vector<String> result;
    for (int i = 0; i < presets.GetCount(); i++) {
        if (presets[i].model_expansion == modelExpansion) {
            result.Add(presets.GetKey(i));
        }
    }
    return result;
}

ValueMap ZenCoreMFXCatalogue::ApplyPreset(const String& presetId, const ValueMap& currentParams) const {
    ValueMap newParams = currentParams;
    const ParameterPreset* preset = GetPreset(presetId);
    if (preset) {
        // Apply preset values to current parameters
        for (int i = 0; i < preset->parameter_values.GetCount(); i++) {
            String key = preset->parameter_values.GetKey(i);
            newParams.Set(key, preset->parameter_values[i]);
        }
    }
    return newParams;
}

Vector<String> ZenCoreMFXCatalogue::GetSupportedModelExpansions() const {
    Vector<String> expansions;
    for (int i = 0; i < model_expansion_algorithms.GetCount(); i++) {
        expansions.Add(model_expansion_algorithms.GetKey(i));
    }
    return expansions;
}

Vector<String> ZenCoreMFXCatalogue::GetAlgorithmsForModelExpansion(const String& modelExpansion) const {
    int idx = model_expansion_algorithms.Find(modelExpansion);
    if (idx >= 0) {
        return model_expansion_algorithms[idx];
    }
    return Vector<String>(); // Empty vector if not found
}

bool ZenCoreMFXCatalogue::ValidateParameterValue(const String& algorithmId, const String& paramId, double value) const {
    const MFXAlgorithm* alg = GetAlgorithm(algorithmId);
    if (!alg) return false;
    
    for (const ParameterTemplate& param : alg->parameter_templates) {
        if (param.id == paramId) {
            return value >= param.min_value && value <= param.max_value;
        }
    }
    return false; // Parameter not found
}

bool ZenCoreMFXCatalogue::ValidateParameters(const String& algorithmId, const ValueMap& params) const {
    const MFXAlgorithm* alg = GetAlgorithm(algorithmId);
    if (!alg) return false;
    
    for (int i = 0; i < params.GetCount(); i++) {
        String paramId = params.GetKey(i);
        double value = params[i];
        
        if (!ValidateParameterValue(algorithmId, paramId, value)) {
            return false;
        }
    }
    return true;
}

ValueMap ZenCoreMFXCatalogue::GetDefaultParameterSet(const String& algorithmId) const {
    ValueMap params;
    const MFXAlgorithm* alg = GetAlgorithm(algorithmId);
    if (alg) {
        for (const ParameterTemplate& param : alg->parameter_templates) {
            params.Set(param.id, param.default_value);
        }
    }
    return params;
}

ValueMap ZenCoreMFXCatalogue::GetModelExpansionParameterSet(const String& algorithmId, const String& modelExpansion) const {
    ValueMap params;
    const MFXAlgorithm* alg = GetAlgorithm(algorithmId);
    if (alg) {
        for (const ParameterTemplate& param : alg->parameter_templates) {
            String key = modelExpansion + "_" + param.id;
            if (alg->category_defaults.Find(key) >= 0) {
                params.Set(param.id, alg->category_defaults[key]);
            } else {
                params.Set(param.id, param.default_value);
            }
        }
    }
    return params;
}

void ZenCoreMFXCatalogue::AddModelExpansionToAlgorithm(const Upp::String& algorithmId, const Upp::String& expansion) {
    // Add the algorithm to the list of algorithms that support this model expansion
    Vector<String>& algs = model_expansion_algorithms.GetAdd(expansion);
    if (find(algs.begin(), algs.end(), algorithmId) == algs.end()) {  // Avoid duplicates
        algs.Add(algorithmId);
    }
}

}
