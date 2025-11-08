#include "SceneManager.h"

namespace UI {

SceneManager::SceneManager() : currentSceneIndex(-1), morphPosition(0.0) {
    // Initialize the scene manager
    AddFrame(BlackFrame());
}

SceneManager::~SceneManager() {
    // Clean up scenes
}

void SceneManager::AddScene(const String& name, const AudioFX::ParameterSet& params) {
    Scene scene;
    scene.name = name;
    scene.params = params;
    scenes.Add(scene);
    
    SceneAdded();
    
    // If this is the first scene, make it current
    if (scenes.GetCount() == 1) {
        currentSceneIndex = 0;
    }
}

bool SceneManager::SetCurrentScene(const String& name) {
    for (int i = 0; i < scenes.GetCount(); i++) {
        if (scenes[i].name == name) {
            currentSceneIndex = i;
            SceneChanged();
            Refresh();
            return true;
        }
    }
    return false;
}

bool SceneManager::SetCurrentScene(int index) {
    if (index >= 0 && index < scenes.GetCount()) {
        currentSceneIndex = index;
        SceneChanged();
        Refresh();
        return true;
    }
    return false;
}

String SceneManager::GetCurrentSceneName() const {
    if (currentSceneIndex >= 0 && currentSceneIndex < scenes.GetCount()) {
        return scenes[currentSceneIndex].name;
    }
    return "";
}

int SceneManager::GetCurrentSceneIndex() const {
    return currentSceneIndex;
}

Vector<String> SceneManager::GetSceneNames() const {
    Vector<String> names;
    for (const auto& scene : scenes) {
        names.Add(scene.name);
    }
    return names;
}

void SceneManager::MorphScenes(int scene1, int scene2, double position) {
    if (scene1 >= 0 && scene1 < scenes.GetCount() && 
        scene2 >= 0 && scene2 < scenes.GetCount()) {
        
        sceneMorph.SetScenes(scenes[scene1].params, scenes[scene2].params);
        sceneMorph.SetMorphPosition(position);
        morphPosition = position;
    }
}

void SceneManager::ApplyMorphedParams(AudioFX::ParameterSet& target) const {
    // Apply the morphed parameters to the target
    AudioFX::ParameterSet morphed = sceneMorph.GetMorphedParameters();
    
    Vector<AudioFX::ParameterId> ids = morphed.GetParameterIds();
    for (const auto& id : ids) {
        target.Set(id, morphed.Get(id));
    }
}

void SceneManager::Refresh() {
    Refresh();
}

void SceneManager::SceneAdded() {
    // Callback when a scene is added
}

void SceneManager::SceneChanged() {
    // Callback when the current scene changes
}

void SceneManager::Paint(Draw& draw) {
    draw.DrawRect(GetSize(), SColorFace());
    
    // Draw scene information
    Rect r = GetSize();
    if (currentSceneIndex >= 0 && currentSceneIndex < scenes.GetCount()) {
        String currentSceneText = "Current Scene: " + scenes[currentSceneIndex].name;
        draw.DrawText(10, 10, currentSceneText, StdFont(), Black());
    } else {
        draw.DrawText(10, 10, "No Scene Selected", StdFont(), Red());
    }
    
    // Draw morph position if morphing
    if (morphPosition > 0.0 && morphPosition < 1.0) {
        String morphText = "Morph: " + Upp::Format("%.2f", morphPosition);
        draw.DrawText(10, 30, morphText, StdFont(), Blue());
    }
    
    // Draw scene list
    int y = 60;
    for (int i = 0; i < scenes.GetCount(); i++) {
        String sceneText = (i == currentSceneIndex ? "> " : "  ") + scenes[i].name;
        Color color = (i == currentSceneIndex) ? Red() : Black();
        draw.DrawText(10, y, sceneText, StdFont(), color);
        y += 20;
    }
}

void SceneManager::Layout() {
    // Handle layout if needed
}

} // namespace UI