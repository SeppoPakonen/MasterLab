#ifndef _Tooling_ToolModifiers_h_
#define _Tooling_ToolModifiers_h_

#include <Core/Core.h>
#include <ProjectMgmt/ProjectMgmt.h>
using namespace Upp;

namespace am {

enum ToolId {
	SELECT_TOOL,
	RANGE_TOOL,
	GLUE_TOOL,
	ERASE_TOOL,
	SPLIT_TOOL,
	TRIM_TOOL,
	TIME_WARP_TOOL,
	AUDIO_WARP_TOOL,
	COLOR_TOOL,
	INFO_LINE_TOOL,
	SIZE_OBJECTS_TOOL,
	// Add more tools as needed
};

struct ModifierBinding : public Upp::Moveable<ModifierBinding> {
	ToolId tool;
	Upp::String action;
	dword keys;
	
	ModifierBinding() : tool(SELECT_TOOL), keys(0) {}
	ModifierBinding(ToolId t, const Upp::String& a, dword k) : tool(t), action(a), keys(k) {}
	
	// Copy constructor
	ModifierBinding(const ModifierBinding& other) = default;
	
	// Move constructor
	ModifierBinding(ModifierBinding&& other) = default;
	
	// Assignment operators
	ModifierBinding& operator=(const ModifierBinding& other) = default;
	ModifierBinding& operator=(ModifierBinding&& other) = default;
};

class ToolModifierMap {
public:
	ToolModifierMap();
	
	// Binding management
	void Set(ToolId tool, const Upp::String& action, dword keys);
	Optional<dword> Get(ToolId tool, const Upp::String& action) const;
	void Remove(ToolId tool, const Upp::String& action);
	void Clear();
	
	// Get all bindings for a tool
	Upp::Vector<ModifierBinding> GetBindingsForTool(ToolId tool) const;
	
	// Signal when bindings change
	Event<> WhenChanged;
	
private:
	VectorMap<Upp::String, dword> bindings; // Key format: "toolId:action"
	
	// Helper to create key from tool and action
	Upp::String CreateKey(ToolId tool, const Upp::String& action) const;
};

}

#endif