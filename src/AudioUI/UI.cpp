#include <PluginSDK/PluginSDK.h> // Explicitly include PluginSDK first
#include "UI.h"
#include "PluginHost.h" // For PluginHost
#include <CtrlLib/CtrlLib.h> // For BlackFrame, ThinFrame, etc.

namespace am {
namespace UI {

// --- RackView ---

RackView::RackView()
{
	SetFrame(BlackFrame());
	graphCtrl = new GraphVisualizationCtrl();
	Add(*graphCtrl);
	graphCtrl->Hide(); // Initially hidden
}

RackView::~RackView()
{
	delete graphCtrl;
}

void RackView::AddPlugin(PluginSDK::PluginProcessor& processor, PluginSDK::PluginEditor& editor)
{
	// Create a PluginHost for the new plugin
	PluginHost* host = new PluginHost;
	host->SetPlugin(processor, editor);
	
	AddModule(static_cast<Ctrl&>(*host), processor.GetName()); // Explicit cast to Ctrl&
	
	// Update graph visualization
	graphCtrl->SetGraph(processor.Graph()); // Assuming PluginProcessor has a Graph() method
	graphCtrl->RefreshLayout();
}

void RackView::AddModule(Ctrl& module_ctrl, const String& name) {
	// Add module to internal list
	ModuleInfo& info = modules.Add();
	info.ctrl = &module_ctrl;
	info.name = name;
	info.visible = true;
	info.enabled = true;
	
	module_lookup.Add(name, modules.GetCount() - 1);
	
	// Add the control to the UI
	Add(module_ctrl.SizePos()); // Simple layout for now
	LayoutModules();
}

void RackView::RemoveModule(const String& name) {
	int idx = module_lookup.Find(name);
	if (idx >= 0) {
		int moduleIdx = module_lookup[idx];
		modules[moduleIdx].ctrl->Remove();
		delete modules[moduleIdx].ctrl; // Assuming dynamically allocated
		modules.Remove(moduleIdx);
		module_lookup.Remove(idx);
		LayoutModules();
	}
}

void RackView::ConnectModules(const String& source, const String& destination) {
	// Placeholder for connection logic
}

void RackView::DisconnectModules(const String& source, const String& name) {
	// Placeholder for disconnection logic
}

void RackView::SetModuleVisible(const String& name, bool visible) {
	int idx = module_lookup.Find(name);
	if (idx >= 0) {
		modules[module_lookup[idx]].visible = visible;
		modules[module_lookup[idx]].ctrl->Show(visible);
	}
}

void RackView::SetModuleEnabled(const String& name, bool enabled) {
	int idx = module_lookup.Find(name);
	if (idx >= 0) {
		modules[module_lookup[idx]].enabled = enabled;
		modules[module_lookup[idx]].ctrl->Enable(enabled);
	}
}

void RackView::OnParameterChanged(const String& param_id, double new_value) {
	// Placeholder for parameter change handling
}

void RackView::SetGraphVisualization(const PluginSDK::GraphVisualization& graph_)
{
	graphCtrl->SetGraph(graph_);
}

void RackView::SetActivePath(const Vector<String>& nodePath)
{
	graphCtrl->SetActivePath(nodePath);
}

void RackView::SetModuleNodeMapping(const VectorMap<String, String>& mapping)
{
	graphCtrl->SetNodeMapping(mapping);
}

void RackView::ShowGraphVisualization()
{
	for (auto& mi : modules) {
		mi.ctrl->Hide();
	}
	graphCtrl->Show();
}

void RackView::HideGraphVisualization()
{
	graphCtrl->Hide();
	for (auto& mi : modules) {
		mi.ctrl->Show();
	}
}

void RackView::Init() {
	// Common initialization for RackView
}

void RackView::UpdateGraphVisualization() {
	// Update graph visualization logic here
}

void RackView::LayoutModules() {
	// Simple vertical layout for now
	Size sz = GetSize();
	int y = 0;
	for (int i = 0; i < modules.GetCount(); ++i) {
		if (modules[i].visible) {
			modules[i].ctrl->SetRect(0, y, sz.cx, 100); // Fixed height for now
			y += 100;
		}
	}
}

// --- SceneManager ---

SceneManager::SceneManager() {
	// Add controls, set up layout, etc.
}

SceneManager::~SceneManager() {
	// Clean up
}

void SceneManager::AddScene(const String& name) {
	// Add scene to internal list and UI
}

void SceneManager::RemoveScene(const String& name) {
	// Remove scene from internal list and UI
}

void SceneManager::RenameScene(const String& old_name, const String& new_name) {
	// Rename scene
}

void SceneManager::SelectScene(const String& name) {
	// Select scene
}

void SceneManager::SetMorphAmount(double amount) {
	// Set morph amount
}

Value SceneManager::GetData() const {
	return Value(); // Placeholder
}

void SceneManager::SetData(const Value& data) {
	// Set data
}

void SceneManager::Init() {
	// Common initialization for SceneManager
}


// --- XYPAD ---

XYPAD::XYPAD() {
	SetFrame(ThinFrame()); // ThinFrame is from CtrlLib, needs to be visible
	SetWantFocus();
}

XYPAD::~XYPAD() {
	
}

void XYPAD::Init() {
	
}

void XYPAD::Paint(Draw& draw) {
	Size sz = GetSize();
	draw.DrawRect(sz, White()); // Background
	
	// Draw crosshairs
	draw.DrawLine(sz.cx * x_pos, 0, sz.cx * x_pos, sz.cy, 1, Gray());
	draw.DrawLine(0, sz.cy * y_pos, sz.cx, sz.cy * y_pos, 1, Gray());
	
	// Draw knob
	int knobSize = 20;
	draw.DrawEllipse(sz.cx * x_pos - knobSize/2, sz.cy * y_pos - knobSize/2, knobSize, knobSize, Blue(), 1, Black());
}

void XYPAD::LeftDown(Point p, dword keyflags) {
	SetFocus();
	is_dragging = true;
	MouseMove(p, keyflags); // Update position immediately
}

void XYPAD::MouseMove(Point p, dword keyflags) {
	if (is_dragging) {
		Size sz = GetSize();
		x_pos = (double)p.x / sz.cx;
		y_pos = (double)p.y / sz.cy;
		SetPos(Pointf(x_pos, y_pos));
		// WhenAction(); // Notify listener of change (if any)
	}
}

void XYPAD::LeftUp(Point p, dword keyflags) {
	is_dragging = false;
}

} // namespace UI
} // namespace am
