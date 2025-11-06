#ifndef _AudioUI_RackView_h_
#define _AudioUI_RackView_h_

#include <CtrlLib/CtrlLib.h>
#include <DSP/DSP.h>
#include <PluginSDK/PluginSDK.h>
#include <AudioUI/GraphVisualizationCtrl.h>
using namespace Upp;

namespace UI {

// Represents a module in the rack view
struct RackModule : public Moveable<RackModule> {
    Upp::String id;
    Upp::String name;
    Upp::String type;  // "effect", "instrument", "utility", etc.
    int input_channels;
    int output_channels;
    Upp::Vector<Upp::String> parameters;
    Upp::ValueMap metadata;
    
    // DSP components for this module
    DSP::ParameterSet parameter_set;
    DSP::ModMatrix mod_matrix;
};

// Represents a connection between two modules
struct RackConnection : public Moveable<RackConnection> {
    Upp::String source_module_id;
    Upp::String source_port;
    Upp::String dest_module_id;
    Upp::String dest_port;
    bool is_active;
    
    RackConnection() : is_active(true) {}
    RackConnection(const Upp::String& src_mod, const Upp::String& src_port,
                   const Upp::String& dst_mod, const Upp::String& dst_port)
        : source_module_id(src_mod), source_port(src_port),
          dest_module_id(dst_mod), dest_port(dst_port), is_active(true) {}
};

// Main rack view control
class RackView : public Ctrl {
public:
    typedef RackView CLASSNAME;
    
    RackView();
    virtual ~RackView();
    
    // Add a module to the rack
    void AddModule(const RackModule& module);
    
    // Remove a module from the rack
    bool RemoveModule(const Upp::String& id);
    
    // Connect two modules
    bool ConnectModules(const Upp::String& source_module, const Upp::String& source_port,
                       const Upp::String& dest_module, const Upp::String& dest_port);
    
    // Disconnect modules
    bool DisconnectModules(const Upp::String& source_module, const Upp::String& source_port,
                           const Upp::String& dest_module, const Upp::String& dest_port);
    
    // Get module by ID
    RackModule* GetModule(const Upp::String& id);
    const RackModule* GetModule(const Upp::String& id) const;
    
    // Parameter automation bridging
    void BridgeToAutomation(DSP::ParameterSet& param_set);
    
    // Preset management integration
    void LoadPreset(const Upp::String& preset_id, DSP::PresetManager& preset_mgr);
    void SavePreset(const Upp::String& preset_id, DSP::PresetManager& preset_mgr);
    
    // Layout management
    void SetModulePosition(const Upp::String& id, Point pos);
    Point GetModulePosition(const Upp::String& id) const;
    
    // Graph Visualization integration
    void UpdateGraphVisualization();
    void SetGraphVisualizationCtrl(GraphVisualizationCtrl* viz_ctrl);
    
    // UI events
    Event<> WhenChanged;
    
protected:
    virtual void Paint(Draw& draw) override;
    virtual void LeftDown(Point p, dword keyflags) override;
    virtual void MouseMove(Point p, dword keyflags) override;
    virtual void RightDown(Point p, dword keyflags) override;
    
private:
    Upp::Vector<RackModule> modules;
    Upp::Vector<RackConnection> connections;
    Upp::VectorMap<Upp::String, Point> module_positions;
    
    // For drag/drop of connections
    bool is_connecting;
    Upp::String connection_source_module;
    Upp::String connection_source_port;
    Point connection_mouse_pos;
    
    // Graph visualization integration
    GraphVisualizationCtrl* graph_viz_ctrl;
    
    // Internal helper methods
    void DrawModule(Draw& draw, const RackModule& module, Point pos);
    void DrawConnection(Draw& draw, const RackConnection& conn);
    Point GetPortPosition(const Upp::String& module_id, const Upp::String& port_name) const;
    Upp::String GetModuleAt(Point p) const;
    Upp::String GetPortAt(Point p) const;
    
    // Convert rack structure to graph visualization
    PluginSDK::GraphVisualization ConvertToGraphVisualization() const;
};

}

#endif