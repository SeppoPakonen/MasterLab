#ifndef _AudioFX_UI_RackView_h_
#define _AudioFX_UI_RackView_h_

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include "../Modulation.h"
#include "../PresetManager.h"

using namespace Upp;

namespace UI {

// Rack view for displaying and controlling audio processing modules
class RackView : public Ctrl {
public:
    RackView();
    virtual ~RackView();
    
    // Add a module to the rack
    void AddModule(const String& name, Ctrl* control);
    
    // Remove a module from the rack
    void RemoveModule(const String& name);
    
    // Update the rack view
    void Refresh();
    
    // Set the preset manager for the rack
    void SetPresetManager(AudioFX::PresetManager* presetMgr);
    
    // Load a preset
    void LoadPreset(const String& name);
    
    // Save current state as preset
    void SavePreset(const String& name);
    
    // Apply parameter automation to the rack
    void ApplyAutomation(const ValueMap& automationData);
    
    // Get automation data from the rack
    ValueMap GetAutomationData() const;
    
protected:
    virtual void Paint(Draw& draw) override;
    virtual void Layout() override;
    
private:
    struct ModuleSlot {
        String name;
        Ctrl* control;
        Rect bounds;
    };
    
    Vector<ModuleSlot> modules;
    AudioFX::PresetManager* presetManager;
    
    void RefreshLayout();
    void ModuleAdded();
    void ModuleRemoved();
};

} // namespace UI

#endif