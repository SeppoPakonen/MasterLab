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
    void AddScene(const String& name, const AudioFX::ParameterSet& params);
    
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
    void ApplyMorphedParams(AudioFX::ParameterSet& target) const;
    
    // Refresh the UI
    void Refresh();
    
protected:
    virtual void Paint(Draw& draw) override;
    virtual void Layout() override;
    
private:
    struct Scene {
        String name;
        AudioFX::ParameterSet params;
        
        Scene() {}
        Scene(const String& n) : name(n) {}
        
        // Support for U++ container operations
        void  operator<<=(const Scene& s) {
            name = s.name; params <<= s.params;
        }
        bool  operator==(const Scene& b) const {
            return name == b.name && params == b.params;
        }
        int   Compare(const Scene& b) const { return name.Compare(b.name); }

        // U++ guest requirement
        void  Guest() const {}

        // Support for U++ deep copy
        void  Move(Scene& s) { *this = pick(s); }
        
        // JSON serialization for guest type compatibility
        void Jsonize(Json& jz) {
            jz("name", name)("params", params);
        }
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