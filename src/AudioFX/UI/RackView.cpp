#include "RackView.h"

namespace UI {

#ifdef GUI

RackView::RackView() : presetManager(nullptr) {
}

RackView::~RackView() {
	for(int i = 0; i < modules.GetCount(); i++) {
		if(modules[i].control) {
			modules[i].control->Remove();
		}
	}
	modules.Clear();
}

void RackView::AddModule(const String& name, Ctrl* control) {
	if(!control) return;
	
	ModuleSlot slot;
	slot.name = name;
	slot.control = control;
	slot.bounds = Rect(0, 0, 100, 100); // Default size
	
	modules.Add(slot);
	Add(*control);
	RefreshLayout();
	ModuleAdded();
}

void RackView::RemoveModule(const String& name) {
	for(int i = 0; i < modules.GetCount(); i++) {
		if(modules[i].name == name) {
			if(modules[i].control) {
				modules[i].control->Remove();
			}
			modules.Remove(i);
			RefreshLayout();
			ModuleRemoved();
			return;
		}
	}
}

void RackView::RefreshLayout() {
	int y = 0;
	int width = GetSize().cx;
	
	for(int i = 0; i < modules.GetCount(); i++) {
		int height = 100; // Default module height
		if(modules[i].control) {
			modules[i].control->SetRect(0, y, width, height);
			y += height;
		}
	}
}

void RackView::Refresh() {
	RefreshLayout();
	Ctrl::Refresh();
}

void RackView::SetPresetManager(AudioFX::PresetManager* presetMgr) {
	presetManager = presetMgr;
}

void RackView::LoadPreset(const String& name) {
	if(presetManager) {
		// Implementation for loading preset into rack modules
	}
}

void RackView::SavePreset(const String& name) {
	if(presetManager) {
		// Implementation for saving rack state as preset
	}
}

void RackView::ApplyAutomation(const ValueMap& automationData) {
	// Implementation for applying automation to rack modules
}

ValueMap RackView::GetAutomationData() const {
	ValueMap data;
	// Implementation for getting automation data from rack modules
	return data;
}

void RackView::Paint(Draw& draw) {
	Size sz = GetSize();
	draw.DrawRect(sz, SColorFace());
	
	if(modules.IsEmpty()) {
		draw.DrawText(sz.cx / 2 - 50, sz.cy / 2, "Rack is empty", Arial(12), SColorText());
	}
}

void RackView::Layout() {
	RefreshLayout();
}

void RackView::ModuleAdded() {
	// Optional callback when module is added
}

void RackView::ModuleRemoved() {
	// Optional callback when module is removed
}

#endif // GUI

} // namespace UI
