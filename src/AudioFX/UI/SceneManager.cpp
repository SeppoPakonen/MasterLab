#include "SceneManager.h"

namespace UI {

#ifdef GUI

SceneManager::SceneManager() : currentSceneIndex(-1), morphPosition(0.0) {
}

SceneManager::~SceneManager() {
	scenes.Clear();
}

void SceneManager::AddScene(const String& name, const AudioFX::ParameterSet& params) {
	Scene s;
	s.name = name;
	s.params <<= params;
	scenes.Add(s);
	SceneAdded();
}

bool SceneManager::SetCurrentScene(const String& name) {
	for(int i = 0; i < scenes.GetCount(); i++) {
		if(scenes[i].name == name) {
			currentSceneIndex = i;
			SceneChanged();
			return true;
		}
	}
	return false;
}

bool SceneManager::SetCurrentScene(int index) {
	if(index >= 0 && index < scenes.GetCount()) {
		currentSceneIndex = index;
		SceneChanged();
		return true;
	}
	return false;
}

String SceneManager::GetCurrentSceneName() const {
	if(currentSceneIndex >= 0 && currentSceneIndex < scenes.GetCount()) {
		return scenes[currentSceneIndex].name;
	}
	return "";
}

int SceneManager::GetCurrentSceneIndex() const {
	return currentSceneIndex;
}

Vector<String> SceneManager::GetSceneNames() const {
	Vector<String> names;
	for(int i = 0; i < scenes.GetCount(); i++) {
		names.Add(scenes[i].name);
	}
	return names;
}

void SceneManager::MorphScenes(int scene1, int scene2, double position) {
	if(scene1 >= 0 && scene1 < scenes.GetCount() && 
	   scene2 >= 0 && scene2 < scenes.GetCount()) {
		sceneMorph.SetScenes(scenes[scene1].params, scenes[scene2].params);
		sceneMorph.SetMorphPosition(position);
		morphPosition = position;
		Refresh();
	}
}

void SceneManager::ApplyMorphedParams(AudioFX::ParameterSet& target) const {
	target <<= sceneMorph.GetMorphedParameters();
}

void SceneManager::Refresh() {
	Ctrl::Refresh();
}

void SceneManager::Paint(Draw& draw) {
	Size sz = GetSize();
	draw.DrawRect(sz, SColorFace());
	
	String text = Format("Scene: %s", GetCurrentSceneName());
	draw.DrawText(10, 10, text, Arial(12), SColorText());
	
	// Draw morph indicator if active
	if(morphPosition > 0.0 && morphPosition < 1.0) {
		int w = (int)(sz.cx * morphPosition);
		draw.DrawRect(0, sz.cy - 5, w, 5, LtBlue());
	}
}

void SceneManager::Layout() {
}

void SceneManager::SceneAdded() {
}

void SceneManager::SceneChanged() {
	Refresh();
}

#endif // GUI

} // namespace UI
