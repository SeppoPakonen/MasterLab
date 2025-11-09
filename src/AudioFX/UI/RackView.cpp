#include "RackView.h"

namespace UI {

RackView::RackView() : presetManager(nullptr) {
    // Initialize the rack view
    AddFrame(BlackFrame());
}

RackView::~RackView() {
    // Clean up modules
    for (auto& module : modules) {
        if (module.control) {
            RemoveChild(module.control);
            delete module.control;
        }
    }
}

void RackView::AddModule(const String& name, Ctrl* control) {
    ModuleSlot slot;
    slot.name = name;
    slot.control = control;
    modules.Add(slot);
    
    if (control) {
        AddChild(control);
    }
    
    ModuleAdded();
    RefreshLayout();
}

void RackView::RemoveModule(const String& name) {
    for (int i = 0; i < modules.GetCount(); i++) {
        if (modules[i].name == name) {
            if (modules[i].control) {
                RemoveChild(modules[i].control);
                delete modules[i].control;
            }
            modules.Remove(i);
            break;
        }
    }
    
    ModuleRemoved();
    RefreshLayout();
}

void RackView::RefreshLayout() {
    int y = 0;
    int width = GetSize().cx;
    const int moduleHeight = 80;
    
    for (auto& module : modules) {
        module.bounds = Rect(0, y, width, y + moduleHeight);
        if (module.control) {
            module.control->SetRect(module.bounds);
        }
        y += moduleHeight + 5; // 5px spacing
    }
    
    SetMinSize(Size(width, y));
}

void RackView::Refresh() {
    RefreshLayout();
    Refresh();
}

void RackView::SetPresetManager(AudioFX::PresetManager* presetMgr) {
    presetManager = presetMgr;
}

void RackView::LoadPreset(const String& name) {
    if (presetManager) {
        // Load preset using preset manager
        // In a real implementation, this would restore parameter values
    }
}

void RackView::SavePreset(const String& name) {
    if (presetManager) {
        // Save preset using preset manager
        // In a real implementation, this would save current parameter values
    }
}

void RackView::ApplyAutomation(const ValueMap& automationData) {
    // Apply automation data to modules
    // In a real implementation, this would apply time-varying parameter changes
}

ValueMap RackView::GetAutomationData() const {
    ValueMap data;
    // In a real implementation, this would collect automation data from modules
    return data;
}

void RackView::Paint(Draw& draw) {
    draw.DrawRect(GetSize(), SColorFace());
    
    // Draw module slots
    for (const auto& module : modules) {
        draw.DrawRect(module.bounds, GrayColor());
        draw.DrawText(module.bounds.left + 10, module.bounds.top + 10, module.name, StdFont(), White());
    }
}

void RackView::Layout() {
    RefreshLayout();
}

void RackView::ModuleAdded() {
    // Callback when a module is added
}

void RackView::ModuleRemoved() {
    // Callback when a module is removed
}

} // namespace UI