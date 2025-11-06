#include "SceneManager.h"

namespace UI {

SceneManager::SceneManager() {
    // Initialize scene manager
}

SceneManager::~SceneManager() {
    // Clean up
}

void SceneManager::CaptureScene(const Upp::String& id, const Upp::String& name,
                               const DSP::ParameterSet& param_set) {
    Scene scene(id, name);
    
    // Capture all parameters from the parameter set
    // This is a simplified approach - in reality we'd need to iterate through
    // all registered parameters in the param_set
    // For now, we'll assume we have access to parameter names through metadata
    
    scenes.GetAdd(id) = scene;
}

bool SceneManager::ApplyScene(const Upp::String& id, DSP::ParameterSet& param_set) {
    int idx = scenes.Find(id);
    if (idx >= 0) {
        const Scene& scene = scenes[idx];
        
        // Apply all parameters from the scene to the parameter set
        for (int i = 0; i < scene.parameters.GetCount(); i++) {
            Upp::String param_name = scene.parameters.GetKey(i);
            double value = scene.parameters[i];
            param_set.SetValue(param_name, value);
        }
        
        return true;
    }
    return false; // Scene not found
}

bool SceneManager::ApplyScene(const Upp::String& id, 
                             Upp::Vector<DSP::ParameterSet*>& param_sets) {
    int idx = scenes.Find(id);
    if (idx >= 0) {
        const Scene& scene = scenes[idx];
        
        // Apply parameters to all parameter sets
        for (DSP::ParameterSet* param_set : param_sets) {
            if (!param_set) continue;
            
            for (int i = 0; i < scene.parameters.GetCount(); i++) {
                Upp::String param_name = scene.parameters.GetKey(i);
                double value = scene.parameters[i];
                param_set->SetValue(param_name, value);
            }
        }
        
        return true;
    }
    return false; // Scene not found
}

bool SceneManager::DeleteScene(const Upp::String& id) {
    int idx = scenes.Find(id);
    if (idx >= 0) {
        scenes.Remove(idx);
        return true;
    }
    return false; // Scene not found
}

Upp::Vector<Upp::String> SceneManager::GetSceneIds() const {
    Upp::Vector<Upp::String> ids;
    for (int i = 0; i < scenes.GetCount(); i++) {
        ids.Add(scenes.GetKey(i));
    }
    return ids;
}

const Scene* SceneManager::GetScene(const Upp::String& id) const {
    int idx = scenes.Find(id);
    if (idx >= 0) {
        return &scenes[idx];
    }
    return nullptr;
}

void SceneManager::CrossfadeScenes(const Upp::String& from_scene, const Upp::String& to_scene,
                                  double ratio, DSP::ParameterSet& param_set) {
    const Scene* scene1 = GetScene(from_scene);
    const Scene* scene2 = GetScene(to_scene);
    
    if (!scene1 || !scene2) return;
    
    // Interpolate between parameter values of the two scenes
    for (int i = 0; i < scene1->parameters.GetCount(); i++) {
        Upp::String param_name = scene1->parameters.GetKey(i);
        double val1 = scene1->parameters[i];
        double val2 = scene2->parameters.Get(param_name, val1); // Use val1 as default if param doesn't exist in scene2
        
        // Interpolate
        double interpolated_val = val1 + ratio * (val2 - val1);
        param_set.SetValue(param_name, interpolated_val);
    }
}

}