#include "Tooling.h"
namespace am {

ToolModifierMap::ToolModifierMap() {
	// Initialize with default modifier bindings
	// AudioWarp Tool
	Set(AUDIO_WARP_TOOL, "delete_tab", Ctrl+Key::Delete);
	
	// Color Tool
	Set(COLOR_TOOL, "popup_event_colors", Ctrl+Key::LeftClick);
	Set(COLOR_TOOL, "sample_event_color", Alt+Key::LeftClick);
	
	// Controls
	Set(SIZE_OBJECTS_TOOL, "value_box_mode", Ctrl+Key::LeftClick);  // For this example
	
	// Define Audio Grid
	Set(TIME_WARP_TOOL, "adjust_tempo", Ctrl+Key::LeftClick);  // For this example
	
	// Drag & Drop
	Set(SELECT_TOOL, "constraint_direction", Ctrl+Key::LeftClick);
	Set(SELECT_TOOL, "copy", Alt+Key::LeftClick);
	Set(SELECT_TOOL, "shared_copy", Alt+Shift+Key::LeftClick);
	
	// Edit Pitch/Warp Tool
	Set(AUDIO_WARP_TOOL, "absolute_pitch_snapping", ModKeys());  // No modifier
	Set(AUDIO_WARP_TOOL, "no_pitch_snapping", Shift+Key::LeftClick);
	Set(AUDIO_WARP_TOOL, "relative_pitch_snapping", Ctrl+Key::LeftClick);
	
	// Erase Tool
	Set(ERASE_TOOL, "delete_later_events", Alt+Key::LeftClick);
	
	// Glue Tool
	Set(GLUE_TOOL, "glue_all_following_events", Alt+Key::LeftClick);
	
	// Info Line
	Set(INFO_LINE_TOOL, "all_events_same_value", Ctrl+Key::LeftClick);
	
	// Range Tool
	Set(RANGE_TOOL, "exclude_row", Ctrl+Key::LeftClick);
	Set(RANGE_TOOL, "select_full_vertical", Ctrl+Shift+Key::LeftClick);
	
	// Select Tool
	Set(SELECT_TOOL, "edit_velocity", Ctrl+Shift+Key::LeftClick);
	Set(SELECT_TOOL, "slip_event", Ctrl+Alt+Key::LeftClick);
	Set(SELECT_TOOL, "split_event", Alt+Key::LeftClick);
	
	// Size Objects
	Set(SIZE_OBJECTS_TOOL, "common_objects", ModKeys());  // No modifier
	Set(SIZE_OBJECTS_TOOL, "disable_snapping", Ctrl+Key::LeftClick);
	Set(SIZE_OBJECTS_TOOL, "repeat_event", Alt+Key::LeftClick);
	Set(SIZE_OBJECTS_TOOL, "time_stretch", ModKeys());  // No modifier
	
	// Split Tool
	Set(SPLIT_TOOL, "split_repeated", Alt+Key::LeftClick);
	
	// Time Warp Tool
	Set(TIME_WARP_TOOL, "create_or_erase", Shift+Key::LeftClick);
	Set(TIME_WARP_TOOL, "no_correction", Alt+Key::LeftClick);
	
	// Trim Tool
	Set(TRIM_TOOL, "constraint_direction", Ctrl+Key::LeftClick);
	Set(TRIM_TOOL, "trim_start", Alt+Key::LeftClick);
}

void ToolModifierMap::Set(ToolId tool, const String& action, const ModKeys& keys) {
	String key = CreateKey(tool, action);
	bindings.GetAdd(key) = keys;
	WhenChanged();
}

Optional<ModKeys> ToolModifierMap::Get(ToolId tool, const String& action) const {
	String key = CreateKey(tool, action);
	if (bindings.Find(key) >= 0) {
		return bindings.Get(key);
	}
	return Optional<ModKeys>(); // Return null optional if not found
}

void ToolModifierMap::Remove(ToolId tool, const String& action) {
	String key = CreateKey(tool, action);
	bindings.Remove(key);
	WhenChanged();
}

void ToolModifierMap::Clear() {
	bindings.Clear();
	WhenChanged();
}

Vector<ModifierBinding> ToolModifierMap::GetBindingsForTool(ToolId tool) const {
	Vector<ModifierBinding> result;
	
	for(const auto& pair : bindings) {
		String key = pair.key;
		// Parse the key "toolId:action" to extract tool and action
		int pos = key.Find(':');
		if (pos > 0) {
			String toolStr = key.Mid(0, pos);
			ToolId parsedTool = (ToolId)ScanInt(toolStr);
			if (parsedTool == tool) {
				ModifierBinding binding;
				binding.tool = parsedTool;
				binding.action = key.Mid(pos + 1);
				binding.keys = pair.value;
				result.Add(binding);
			}
		}
	}
	
	return result;
}

String ToolModifierMap::CreateKey(ToolId tool, const String& action) const {
	returnAsString()<< (int)tool << ":" << action;
}

}