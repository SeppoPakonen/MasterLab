#ifndef _AudioFX_UI_SceneManager_h_
#define _AudioFX_UI_SceneManager_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "../Modulation.h"

using namespace Upp;

namespace UI {

// Scene manager for managing and switching between different parameter scenes
class SceneManager : public Ctrl {
public:
    SceneManager();
    virtual ~SceneManager();
    
    // Add a scene with parameters
    void AddScene(const String& name, const DSP::ParameterSet& params);
    
    // Set current scene by name
    bool SetCurrentScene(const String& name);
    
    // Set current scene by index
    bool SetCurrentScene(int index);
    
    // Get current scene name
    String GetCurrentSceneName() const;
    
    // Get current scene index
    int GetCurrentSceneIndex() const;
    
    // Get list of scene names
    Vector<String> GetSceneNames() const;
    
    // Morph between two scenes
    void MorphScenes(int scene1, int scene2, double position);
    
    // Apply morphed parameters to target parameter set
    void ApplyMorphedParams(DSP::ParameterSet& target) const;
    
    // Refresh the UI
    void Refresh();
    
protected:
    virtual void Paint(Draw& draw) override;
    virtual void Layout() override;
    
private:
    struct Scene {
        String name;
        DSP::ParameterSet params;
    };
    
    Vector<Scene> scenes;
    int currentSceneIndex;
    DSP::SceneMorph sceneMorph;
    double morphPosition;
    
    void SceneAdded();
    void SceneChanged();
};

} // namespace UI

#endif