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

struct ModifierBinding {
	ToolId tool;
	String action;
	ModKeys keys;
};

class ToolModifierMap {
public:
	ToolModifierMap();
	
	// Binding management
	void Set(ToolId tool, const String& action, const ModKeys& keys);
	Optional<ModKeys> Get(ToolId tool, const String& action) const;
	void Remove(ToolId tool, const String& action);
	void Clear();
	
	// Get all bindings for a tool
	Vector<ModifierBinding> GetBindingsForTool(ToolId tool) const;
	
	// Signal when bindings change
	Event<> WhenChanged;
	
private:
	HashMap<String, ModKeys> bindings; // Key format: "toolId:action"
	
	// Helper to create key from tool and action
	String CreateKey(ToolId tool, const String& action) const;
};

}

#endif