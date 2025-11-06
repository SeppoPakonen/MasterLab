#include "RackView.h"

namespace UI {

RackView::RackView() : is_connecting(false), graph_viz_ctrl(nullptr) {
    // Initialize the rack view
    NoWantFocus();
}

RackView::~RackView() {
    // Clean up
}

void RackView::AddModule(const RackModule& module) {
    // Check if module with this ID already exists
    for (int i = 0; i < modules.GetCount(); i++) {
        if (modules[i].id == module.id) {
            modules[i] = module; // Update existing module
            break; // Exit the loop after updating
        }
    }
    
    // If module wasn't found, add it as new
    if (GetModule(module.id) == nullptr) {
        modules.Add(module);
    }
    
    // Trigger UI update
    Refresh();
    if (graph_viz_ctrl) {
        UpdateGraphVisualization();
    }
    if (WhenChanged)
        WhenChanged();
}

bool RackView::RemoveModule(const Upp::String& id) {
    for (int i = 0; i < modules.GetCount(); i++) {
        if (modules[i].id == id) {
            modules.Remove(i);
            
            // Also remove any connections involving this module
            for (int j = connections.GetCount() - 1; j >= 0; j--) {
                if (connections[j].source_module_id == id || 
                    connections[j].dest_module_id == id) {
                    connections.Remove(j);
                }
            }
            
            // Remove position data
            int pos_idx = module_positions.Find(id);
            if (pos_idx >= 0) {
                module_positions.Remove(pos_idx);
            }
            
            Refresh();
            if (graph_viz_ctrl) {
                UpdateGraphVisualization();
            }
            if (WhenChanged)
                WhenChanged();
            return true;
        }
    }
    return false;
}

bool RackView::ConnectModules(const Upp::String& source_module, const Upp::String& source_port,
                              const Upp::String& dest_module, const Upp::String& dest_port) {
    // Check if connection already exists
    for (const auto& conn : connections) {
        if (conn.source_module_id == source_module && conn.source_port == source_port &&
            conn.dest_module_id == dest_module && conn.dest_port == dest_port) {
            return false; // Connection already exists
        }
    }
    
    // Verify modules exist
    bool src_exists = false, dst_exists = false;
    for (const auto& mod : modules) {
        if (mod.id == source_module) src_exists = true;
        if (mod.id == dest_module) dst_exists = true;
    }
    
    if (!src_exists || !dst_exists) {
        return false; // One of the modules doesn't exist
    }
    
    connections.Add(RackConnection(source_module, source_port, dest_module, dest_port));
    
    Refresh();
    if (graph_viz_ctrl) {
        UpdateGraphVisualization();
    }
    if (WhenChanged)
        WhenChanged();
    
    return true;
}

bool RackView::DisconnectModules(const Upp::String& source_module, const Upp::String& source_port,
                                 const Upp::String& dest_module, const Upp::String& dest_port) {
    for (int i = 0; i < connections.GetCount(); i++) {
        const auto& conn = connections[i];
        if (conn.source_module_id == source_module && conn.source_port == source_port &&
            conn.dest_module_id == dest_module && conn.dest_port == dest_port) {
            connections.Remove(i);
            
            Refresh();
            if (graph_viz_ctrl) {
                UpdateGraphVisualization();
            }
            if (WhenChanged)
                WhenChanged();
            return true;
        }
    }
    return false;
}

RackModule* RackView::GetModule(const Upp::String& id) {
    for (int i = 0; i < modules.GetCount(); i++) {
        if (modules[i].id == id) {
            return &modules[i];
        }
    }
    return nullptr;
}

const RackModule* RackView::GetModule(const Upp::String& id) const {
    for (int i = 0; i < modules.GetCount(); i++) {
        if (modules[i].id == id) {
            return &modules[i];
        }
    }
    return nullptr;
}

void RackView::BridgeToAutomation(DSP::ParameterSet& param_set) {
    // This method connects the parameter set to the UI controls in RackView
    // In a real implementation, this would set up two-way binding between
    // UI controls and parameters so changes are recorded for automation
    // This is just a placeholder implementation
}

void RackView::LoadPreset(const Upp::String& preset_id, DSP::PresetManager& preset_mgr) {
    // Load parameters from preset into all modules
    for (int i = 0; i < modules.GetCount(); i++) {
        preset_mgr.LoadPreset(preset_id + "_" + modules[i].id, modules[i].parameter_set);
    }
    
    Refresh();
    if (graph_viz_ctrl) {
        UpdateGraphVisualization();
    }
}

void RackView::SavePreset(const Upp::String& preset_id, DSP::PresetManager& preset_mgr) {
    // Save parameters from all modules to preset
    for (int i = 0; i < modules.GetCount(); i++) {
        DSP::Preset preset(preset_id + "_" + modules[i].id, modules[i].name + " Settings");
        
        // Extract all parameter values
        for (int j = 0; j < modules[i].parameters.GetCount(); j++) {
            const Upp::String& param_name = modules[i].parameters[j];
            preset.parameters.Set(param_name, modules[i].parameter_set.GetValue(param_name));
        }
        
        preset_mgr.StorePreset(preset);
    }
    if (graph_viz_ctrl) {
        UpdateGraphVisualization();
    }
}

void RackView::SetModulePosition(const Upp::String& id, Point pos) {
    module_positions.GetAdd(id) = pos;
    Refresh();
}

Point RackView::GetModulePosition(const Upp::String& id) const {
    int idx = module_positions.Find(id);
    if (idx >= 0) {
        return module_positions[idx];
    }
    return Point(0, 0); // Default position
}

void RackView::Paint(Draw& draw) {
    // Draw the rack view background
    draw.DrawRect(GetSize(), Gray());
    
    // Draw connections first (so they appear behind modules)
    for (const auto& conn : connections) {
        DrawConnection(draw, conn);
    }
    
    // Draw modules
    for (const auto& mod : modules) {
        Point pos = GetModulePosition(mod.id);
        DrawModule(draw, mod, pos);
    }
    
    // Draw ongoing connection if we're in the middle of connecting
    if (is_connecting) {
        Point src_pos = GetPortPosition(connection_source_module, connection_source_port);
        // Draw line from source to mouse position
        draw.DrawLine(src_pos.x, src_pos.y, connection_mouse_pos.x, connection_mouse_pos.y, 2, Red());
    }
}

void RackView::LeftDown(Point p, dword keyflags) {
    // Handle module selection or connection initiation
    Upp::String module_id = GetModuleAt(p);
    if (!module_id.IsEmpty()) {
        // Module clicked - could be starting a drag or selecting
        SetFocus();
        Refresh();
    } else {
        // Empty space clicked - end any ongoing connection
        is_connecting = false;
        Refresh();
    }
}

void RackView::MouseMove(Point p, dword keyflags) {
    if (is_connecting) {
        connection_mouse_pos = p;
        Refresh();
    }
}

void RackView::RightDown(Point p, dword keyflags) {
    // Start connection process
    Upp::String module_id = GetModuleAt(p);
    Upp::String port_name = GetPortAt(p);
    
    if (!module_id.IsEmpty() && !port_name.IsEmpty()) {
        is_connecting = true;
        connection_source_module = module_id;
        connection_source_port = port_name;
        connection_mouse_pos = p;
        Refresh();
    }
}

void RackView::DrawModule(Draw& draw, const RackModule& module, Point pos) {
    // Draw a simple representation of the module
    Size module_size(120, 80);
    
    // Draw module background
    draw.DrawRect(pos.x, pos.y, module_size.cx, module_size.cy, LtBlue());
    draw.DrawRect(pos.x, pos.y, module_size.cx, module_size.cy, 1, Black());
    
    // Draw module name
    draw.DrawText(pos.x + 5, pos.y + 5, module.name, StdFont(10), Black());
    
    // Draw input ports on the left
    for (int i = 0; i < module.input_channels; i++) {
        Point port_pos(pos.x, pos.y + 20 + i * 15);
        draw.DrawEllipse(port_pos.x - 5, port_pos.y - 5, 10, 10, Green());
        draw.DrawEllipse(port_pos.x - 5, port_pos.y - 5, 10, 10, 1, Black());
    }
    
    // Draw output ports on the right
    for (int i = 0; i < module.output_channels; i++) {
        Point port_pos(pos.x + module_size.cx, pos.y + 20 + i * 15);
        draw.DrawEllipse(port_pos.x - 5, port_pos.y - 5, 10, 10, Red());
        draw.DrawEllipse(port_pos.x - 5, port_pos.y - 5, 10, 10, 1, Black());
    }
}

void RackView::DrawConnection(Draw& draw, const RackConnection& conn) {
    Point src_pos = GetPortPosition(conn.source_module_id, conn.source_port + "_output");
    Point dst_pos = GetPortPosition(conn.dest_module_id, conn.dest_port + "_input");
    
    if (src_pos.x != -1 && dst_pos.x != -1) { // Check if ports exist
        draw.DrawLine(src_pos.x, src_pos.y, dst_pos.x, dst_pos.y, 2, conn.is_active ? Blue() : LightBlue());
    }
}

Point RackView::GetPortPosition(const Upp::String& module_id, const Upp::String& port_name) const {
    const RackModule* mod = GetModule(module_id);
    if (!mod) return Point(-1, -1); // Not found
    
    Point module_pos = GetModulePosition(module_id);
    Size module_size(120, 80);
    
    // Simplified: assume "input" in name means input port on the left
    // and "output" in name means output port on the right
    if (port_name.Find("input") >= 0) {
        // Find the input port by its index
        int port_index = 0; // Simplified - assume first input
        return Point(module_pos.x, module_pos.y + 20 + port_index * 15);
    } else if (port_name.Find("output") >= 0) {
        // Find the output port by its index
        int port_index = 0; // Simplified - assume first output
        return Point(module_pos.x + module_size.cx, module_pos.y + 20 + port_index * 15);
    }
    
    return Point(-1, -1); // Not found
}

Upp::String RackView::GetModuleAt(Point p) const {
    // Find which module contains this point
    for (int i = 0; i < modules.GetCount(); i++) {
        Point pos = GetModulePosition(modules[i].id);
        Size module_size(120, 80);
        
        if (p.x >= pos.x && p.x <= pos.x + module_size.cx &&
            p.y >= pos.y && p.y <= pos.y + module_size.cy) {
            return modules[i].id;
        }
    }
    return Upp::String(); // Empty string if no module at this position
}

Upp::String RackView::GetPortAt(Point p) const {
    // Find which port is at this point by checking proximity to port positions
    for (int i = 0; i < modules.GetCount(); i++) {
        Point module_pos = GetModulePosition(modules[i].id);
        Size module_size(120, 80);
        
        // Check input ports
        for (int in = 0; in < modules[i].input_channels; in++) {
            Point port_pos(module_pos.x, module_pos.y + 20 + in * 15);
            if (abs(p.x - port_pos.x) < 10 && abs(p.y - port_pos.y) < 10) {
                return "input_" + IntStr(in);
            }
        }
        
        // Check output ports
        for (int out = 0; out < modules[i].output_channels; out++) {
            Point port_pos(module_pos.x + module_size.cx, module_pos.y + 20 + out * 15);
            if (abs(p.x - port_pos.x) < 10 && abs(p.y - port_pos.y) < 10) {
                return "output_" + IntStr(out);
            }
        }
    }
    
    return Upp::String(); // Empty string if no port at this position
}

void RackView::UpdateGraphVisualization() {
    if (!graph_viz_ctrl) return;
    
    // Convert our rack structure to the visualization format
    PluginSDK::GraphVisualization graph = ConvertToGraphVisualization();
    
    // Set the graph data to the visualization control
    graph_viz_ctrl->SetGraph(graph);
    
    // Optionally highlight active paths based on current routing
    // For now, we'll highlight all connections
    Vector<String> highlighted_edges;
    for (const auto& conn : connections) {
        highlighted_edges.Add(conn.source_module_id + "->" + conn.dest_module_id);
    }
    graph_viz_ctrl->SetHighlightedEdges(highlighted_edges);
}

void RackView::SetGraphVisualizationCtrl(GraphVisualizationCtrl* viz_ctrl) {
    graph_viz_ctrl = viz_ctrl;
    
    // If we have modules already, update the visualization
    if (graph_viz_ctrl) {
        UpdateGraphVisualization();
    }
}

PluginSDK::GraphVisualization RackView::ConvertToGraphVisualization() const {
    PluginSDK::GraphVisualization graph;
    
    // Convert our modules to graph nodes
    for (const auto& module : modules) {
        PluginSDK::GraphNode node;
        node.id = module.id;
        node.label = module.name;
        node.group = module.type; // Group by type
        graph.nodes.Add(node);
    }
    
    // Convert our connections to graph edges
    for (const auto& connection : connections) {
        PluginSDK::GraphEdge edge;
        edge.from = connection.source_module_id;
        edge.to = connection.dest_module_id;
        edge.audio = true;  // For now, all connections are audio connections
        edge.control = false;  // May add control connections later
        edge.active = connection.is_active;
        graph.edges.Add(edge);
    }
    
    return graph;
}

}