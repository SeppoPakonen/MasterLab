#include "UI.h"

namespace am {
namespace UI {

// RackView implementation
RackView::RackView() : graphCtrl(nullptr), showGraph(false) {
	Init();
}

RackView::~RackView() {
	// Clean up modules
	for(int i = 0; i < modules.GetCount(); i++) {
		if(modules[i].ctrl) {
			RemoveChild(modules[i].ctrl);
		}
	}
	
	// Clean up graph visualization if it exists
	if(graphCtrl) {
		RemoveChild(graphCtrl);
		delete graphCtrl;
	}
}

void RackView::Init() {
	// Initialize the RackView control
	graphCtrl = nullptr;
	showGraph = false;
}

void RackView::AddModule(Ctrl& module_ctrl, const String& name) {
	ModuleInfo info;
	info.ctrl = &module_ctrl;
	info.name = name;
	info.visible = true;
	info.enabled = true;
	
	modules.Add(info);
	module_lookup.GetAdd(name) = modules.GetCount() - 1;
	
	// If showing graph, don't add to child controls
	if(!showGraph) {
		// Add the module control as a child
		AddChild(&module_ctrl);  // Need to pass pointer, not reference
	}
	
	// Arrange modules in a vertical stack
	// This is a simplified layout - in a real implementation, 
	// you might allow free positioning
	LayoutModules();
}

void RackView::RemoveModule(const String& name) {
	int idx = module_lookup.Get(name, -1);
	if(idx >= 0 && idx < modules.GetCount()) {
		if(modules[idx].ctrl) {
			RemoveChild(modules[idx].ctrl);
			delete modules[idx].ctrl;
		}
		
		// Remove from vector
		modules.Remove(idx);
		
		// Update lookup table
		module_lookup.Clear();
		for(int i = 0; i < modules.GetCount(); i++) {
			module_lookup.GetAdd(modules[i].name) = i;
		}
	}
	
	LayoutModules();
}

void RackView::LayoutModules() {
	// If showing graph, don't layout traditional modules
	if(showGraph && graphCtrl) {
		graphCtrl->SetRect(GetSize());
		return;
	}
	
	// Arrange modules in a vertical stack
	int y = 0;
	for(int i = 0; i < modules.GetCount(); i++) {
		if(modules[i].ctrl && modules[i].visible) {
			modules[i].ctrl->LeftPos(0, GetSize().cx).TopPos(y, 100); // 100px height per module
			y += 105; // 100px + 5px spacing
		}
	}
}

void RackView::ConnectModules(const String& source, const String& destination) {
	// Implementation for connecting modules
	// In a real implementation, this would create visual connections between modules
	LOG("Connecting " + source + " to " + destination);
}

void RackView::DisconnectModules(const String& source, const String& destination) {
	// Implementation for disconnecting modules
	LOG("Disconnecting " + source + " from " + destination);
}

void RackView::SetModuleVisible(const String& name, bool visible) {
	int idx = module_lookup.Get(name, -1);
	if(idx >= 0 && idx < modules.GetCount()) {
		modules[idx].visible = visible;
		if(modules[idx].ctrl) {
			modules[idx].ctrl->Show(visible);
		}
		LayoutModules();
	}
}

void RackView::SetModuleEnabled(const String& name, bool enabled) {
	int idx = module_lookup.Get(name, -1);
	if(idx >= 0 && idx < modules.GetCount()) {
		modules[idx].enabled = enabled;
		if(modules[idx].ctrl) {
			// In a real implementation, this would affect the module's functionality
		}
	}
}

void RackView::OnParameterChanged(const String& param_id, double new_value) {
	// Handle parameter changes from automation
	// This would update the UI to reflect parameter changes
	LOG("Parameter " + param_id + " changed to " + AsString(new_value));
}

void RackView::SetGraphVisualization(const PluginSDK::GraphVisualization& graph_) {
	// Since PluginSDK::GraphVisualization can't be assigned directly,
	// we need to copy fields manually
	graph.nodes.Clear();
	graph.edges.Clear();
	
	// Copy nodes
	for(const auto& node : graph_.nodes) {
		graph.nodes.Add(node);
	}
	
	// Copy edges
	for(const auto& edge : graph_.edges) {
		graph.edges.Add(edge);
	}
	
	UpdateGraphVisualization();
}

void RackView::SetActivePath(const Vector<String>& nodePath) {
	activePath.Clear();
	for(const auto& item : nodePath) {
		activePath.Add(item);
	}
	if(graphCtrl) {
		graphCtrl->SetActivePath(nodePath);
	}
}

void RackView::SetModuleNodeMapping(const VectorMap<String, String>& mapping) {
	moduleToNodeMap <<= mapping;
}

void RackView::ShowGraphVisualization() {
	if(!graphCtrl) {
		graphCtrl = new GraphVisualizationCtrl();
		graphCtrl->SetGraph(graph);
		graphCtrl->SetActivePath(activePath);
		AddChild(graphCtrl);  // Pass pointer, not dereferenced object
	}
	
	// Hide module controls
	for(int i = 0; i < modules.GetCount(); i++) {
		if(modules[i].ctrl) {
			modules[i].ctrl->Show(false);
		}
	}
	
	// Show graph visualization
	graphCtrl->Show(true);
	graphCtrl->SetRect(GetSize());
	showGraph = true;
}

void RackView::HideGraphVisualization() {
	if(graphCtrl) {
		graphCtrl->Show(false);
	}
	
	// Show module controls
	for(int i = 0; i < modules.GetCount(); i++) {
		if(modules[i].ctrl) {
			modules[i].ctrl->Show(modules[i].visible);
		}
	}
	
	showGraph = false;
	LayoutModules();
}

void RackView::UpdateGraphVisualization() {
	if(graphCtrl) {
		graphCtrl->SetGraph(graph);
		
		// Update active path
		graphCtrl->SetActivePath(activePath);
	}
}

// SceneManager implementation
SceneManager::SceneManager() {
	Init();
}

SceneManager::~SceneManager() {
	// Destructor implementation
}

void SceneManager::Init() {
	// Initialize controls
	Add(scene_selector.TopPos(0, 25).HSizePos());
	Add(morph_slider.TopPos(30, 25).HSizePos());
	Add(next_scene_btn.TopPos(60, 25).RightPos(0, 80));
	Add(prev_scene_btn.TopPos(60, 25).RightPos(85, 80));
	
	// Set up event handlers
	scene_selector.WhenAction = [this]() {
		String selected = AsString(scene_selector.Get());
		SelectScene(selected);
	};
	
	next_scene_btn.SetLabel("Next");
	prev_scene_btn.SetLabel("Prev");
	next_scene_btn << [this]() { /* Implement next scene */ };
	prev_scene_btn << [this]() { /* Implement previous scene */ };
	
	// Add default scenes
	AddScene("Scene 1");
	AddScene("Scene 2");
	scene_selector.SetIndex(0);
}

void SceneManager::AddScene(const String& name) {
	scene_selector.Add(name);
}

void SceneManager::RemoveScene(const String& name) {
	int idx = scene_selector.Find(name);
	if(idx >= 0) {
		scene_selector.Remove(idx);
	}
}

void SceneManager::RenameScene(const String& old_name, const String& new_name) {
	int idx = scene_selector.Find(old_name);
	if(idx >= 0) {
		scene_selector.Set(idx, Value(new_name));
	}
}

void SceneManager::SelectScene(const String& name) {
	int idx = scene_selector.Find(name);
	if(idx >= 0) {
		scene_selector.SetIndex(idx);
		current_scene = name;
		// In a real implementation, this would apply the scene parameters
	}
}

void SceneManager::SetMorphAmount(double amount) {
	morph_amount = max(0.0, min(1.0, amount));
	// In a real implementation, this would apply the morph between scenes
}

Value SceneManager::GetData() const {
	return Value(morph_amount);
}

void SceneManager::SetData(const Value& data) {
	if(data.Is<double>()) {
		SetMorphAmount(data);
	}
}

// XYPAD implementation
XYPAD::XYPAD() {
	Init();
}

XYPAD::~XYPAD() {
	// Destructor implementation
}

void XYPAD::Init() {
	// Initial setup
}

void XYPAD::Paint(Draw& draw) {
	Size sz = GetSize();
	
	// Draw the background
	draw.DrawRect(sz, White());
	
	// Draw grid lines
	for(int i = 1; i < 10; i++) {
		int x = (sz.cx * i) / 10;
		int y = (sz.cy * i) / 10;
		
		draw.DrawLine(x, 0, x, sz.cy, 1, Gray());
		draw.DrawLine(0, y, sz.cx, y, 1, Gray());
	}
	
	// Draw center lines
	draw.DrawLine(sz.cx/2, 0, sz.cx/2, sz.cy, 1, LtGray());
	draw.DrawLine(0, sz.cy/2, sz.cx, sz.cy/2, 1, LtGray());
	
	// Draw the handle
	int handle_x = (int)(x_pos * sz.cx);
	int handle_y = (int)(y_pos * sz.cy);
	
	// Draw a circle at the current position
	draw.DrawEllipse(handle_x - 8, handle_y - 8, 16, 16, Blue(), 2, Blue());
}

void XYPAD::LeftDown(Point p, dword keyflags) {
	SetPos(Pointf((double)p.x / GetSize().cx, (double)p.y / GetSize().cy));
	is_dragging = true;
}

void XYPAD::MouseMove(Point p, dword keyflags) {
	if(is_dragging) {
		SetPos(Pointf((double)p.x / GetSize().cx, (double)p.y / GetSize().cy));
		// In a real implementation, this would trigger value change events
	}
}

void XYPAD::LeftUp(Point p, dword keyflags) {
	is_dragging = false;
	SetPos(Pointf((double)p.x / GetSize().cx, (double)p.y / GetSize().cy));
	// In a real implementation, this would trigger value change events
}

}  // namespace UI
}  // namespace am