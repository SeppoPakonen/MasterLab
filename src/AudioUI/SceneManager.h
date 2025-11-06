#ifndef _AudioUI_SceneManager_h_
#define _AudioUI_SceneManager_h_

#include <CtrlLib/CtrlLib.h>
#include <DSP/DSP.h>
using namespace Upp;

namespace UI {

// Represents a scene with parameter states
struct Scene : public Moveable<Scene> {
    Upp::String id;
    Upp::String name;
    Upp::String description;
    ValueMap parameters;  // Map of parameter names to values
    Time timestamp;
    
    Scene() : timestamp(GetSysTime()) {}
    Scene(const Upp::String& scene_id, const Upp::String& scene_name) 
        : id(scene_id), name(scene_name), timestamp(GetSysTime()) {}
};

class SceneManager {
public:
    SceneManager();
    virtual ~SceneManager();
    
    // Create a new scene from current parameter states
    void CaptureScene(const Upp::String& id, const Upp::String& name, 
                     const DSP::ParameterSet& param_set);
    
    // Apply a scene to parameter set
    bool ApplyScene(const Upp::String& id, DSP::ParameterSet& param_set);
    
    // Apply a scene to multiple parameter sets
    bool ApplyScene(const Upp::String& id, 
                   Upp::Vector<DSP::ParameterSet*>& param_sets);
    
    // Delete a scene
    bool DeleteScene(const Upp::String& id);
    
    // Get all available scene IDs
    Upp::Vector<Upp::String> GetSceneIds() const;
    
    // Get scene info
    const Scene* GetScene(const Upp::String& id) const;
    
    // Smooth transition between scenes
    void CrossfadeScenes(const Upp::String& from_scene, const Upp::String& to_scene,
                        double ratio, DSP::ParameterSet& param_set);
    
private:
    VectorMap<Upp::String, Scene> scenes;
};

}

#endif