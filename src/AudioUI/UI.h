#ifndef _AudioUI_UI_h_
#define _AudioUI_UI_h_

#include <CtrlLib/CtrlLib.h>
#include <AudioCore/AudioCore.h>
#include <AudioFX/AudioFX.h>
#include <PluginSDK/PluginSDK.h>
#include "GraphVisualizationCtrl.h"  // Include GraphVisualizationCtrl instead of forward declaration
using namespace Upp;

namespace am {
namespace UI {

// RackView - UI component for displaying and controlling rack modules
class RackView : public ParentCtrl {
public:
	typedef RackView CLASSNAME;
	
	RackView();
	virtual ~RackView();
	
	void AddModule(Ctrl& module_ctrl, const String& name);
	void RemoveModule(const String& name);
	void ConnectModules(const String& source, const String& destination);
	void DisconnectModules(const String& source, const String& destination);
	
	void SetModuleVisible(const String& name, bool visible);
	void SetModuleEnabled(const String& name, bool enabled);
	
	// For automation bridging with DSP::PresetManager
	void OnParameterChanged(const String& param_id, double new_value);
	
	// Graph visualization integration
	void SetGraphVisualization(const PluginSDK::GraphVisualization& graph);
	void SetActivePath(const Vector<String>& nodePath);
	void SetModuleNodeMapping(const VectorMap<String, String>& mapping); // Map module names to graph nodes
	void ShowGraphVisualization();
	void HideGraphVisualization();
	
private:
	void Init();
	void UpdateGraphVisualization();
	void LayoutModules();
	
	// Inner class to represent a module in the rack
	struct ModuleInfo : public Moveable<ModuleInfo> {
		Ctrl* ctrl;
		String name;
		bool visible;
		bool enabled;
	};
	
	// Graph visualization components
	PluginSDK::GraphVisualization graph;
	Vector<String> activePath;
	VectorMap<String, String> moduleToNodeMap;  // Map module names to graph nodes
	GraphVisualizationCtrl* graphCtrl;
	bool showGraph;
	
	Vector<ModuleInfo> modules;
	VectorMap<String, int> module_lookup;  // name to index
};

// SceneManager - UI for managing and morphing between scenes
class SceneManager : public Ctrl {
public:
	typedef SceneManager CLASSNAME;
	
	SceneManager();
	virtual ~SceneManager();
	
	void AddScene(const String& name);
	void RemoveScene(const String& name);
	void RenameScene(const String& old_name, const String& new_name);
	void SelectScene(const String& name);
	void SetMorphAmount(double amount);  // 0.0 to 1.0
	
	Value GetData() const;
	void SetData(const Value& data);
	
private:
	void Init();
	
	DropList scene_selector;
	SliderCtrl morph_slider;
	Button next_scene_btn;
	Button prev_scene_btn;
	
	String current_scene;
	double morph_amount;
};

// XYPAD - 2D control surface for dual parameter control
class XYPAD : public Ctrl {
public:
	typedef XYPAD CLASSNAME;
	
	XYPAD();
	virtual ~XYPAD();
	
	// Get/set the X and Y coordinates (0.0 to 1.0)
	double GetX() const { return x_pos; }
	double GetY() const { return y_pos; }
	void SetX(double x) { x_pos = max(0.0, min(1.0, x)); Refresh(); }
	void SetY(double y) { y_pos = max(0.0, min(1.0, y)); Refresh(); }
	
	// Get/set both coordinates
	Pointf GetPos() const { return Pointf(x_pos, y_pos); }
	void SetPos(const Pointf& pos) { 
		x_pos = max(0.0, min(1.0, pos.x)); 
		y_pos = max(0.0, min(1.0, pos.y)); 
		Refresh(); 
	}
	
	Value GetData() const { return Value(Pointf(x_pos, y_pos)); }
	void SetData(const Value& data) { 
		if(data.Is<Pointf>()) {
			Pointf pt = data;
			SetPos(pt);
		}
	}
	
private:
	void Init();
	virtual void Paint(Draw& draw);
	virtual void LeftDown(Point p, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);
	virtual void LeftUp(Point p, dword keyflags);
	
	double x_pos = 0.5;
	double y_pos = 0.5;
	bool is_dragging = false;
	
	// Control dimensions (will be calculated based on actual control size)
	int control_width = 0;
	int control_height = 0;
};

}  // namespace UI
}  // namespace am

#endif