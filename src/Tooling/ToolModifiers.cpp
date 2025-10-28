#include "Tooling.h"
namespace am {

ToolModifierMap::ToolModifierMap() {
	// Initialize with default modifier bindings
	// AudioWarp Tool
	Set(AUDIO_WARP_TOOL, "delete_tab", K_CTRL|K_DELETE);
	
	// Color Tool
	Set(COLOR_TOOL, "popup_event_colors", K_CTRL|K_LEFT);
	Set(COLOR_TOOL, "sample_event_color", K_ALT|K_LEFT);
	
	// Controls
	Set(SIZE_OBJECTS_TOOL, "value_box_mode", K_CTRL|K_LEFT);  // For this example
	
	// Define Audio Grid
	Set(TIME_WARP_TOOL, "adjust_tempo", K_CTRL|K_LEFT);  // For this example
	
	// Drag & Drop
	Set(SELECT_TOOL, "constraint_direction", K_CTRL|K_LEFT);
	Set(SELECT_TOOL, "copy", K_ALT|K_LEFT);
	Set(SELECT_TOOL, "shared_copy", K_ALT|K_SHIFT|K_LEFT);
	
	// Edit Pitch/Warp Tool
	Set(AUDIO_WARP_TOOL, "absolute_pitch_snapping", 0);  // No modifier
	Set(AUDIO_WARP_TOOL, "no_pitch_snapping", K_SHIFT|K_LEFT);
	Set(AUDIO_WARP_TOOL, "relative_pitch_snapping", K_CTRL|K_LEFT);
	
	// Erase Tool
	Set(ERASE_TOOL, "delete_later_events", K_ALT|K_LEFT);
	
	// Glue Tool
	Set(GLUE_TOOL, "glue_all_following_events", K_ALT|K_LEFT);
	
	// Info Line
	Set(INFO_LINE_TOOL, "all_events_same_value", K_CTRL|K_LEFT);
	
	// Range Tool
	Set(RANGE_TOOL, "exclude_row", K_CTRL|K_LEFT);
	Set(RANGE_TOOL, "select_full_vertical", K_CTRL|K_SHIFT|K_LEFT);
	
	// Select Tool
	Set(SELECT_TOOL, "edit_velocity", K_CTRL|K_SHIFT|K_LEFT);
	Set(SELECT_TOOL, "slip_event", K_CTRL|K_ALT|K_LEFT);
	Set(SELECT_TOOL, "split_event", K_ALT|K_LEFT);
	
	// Size Objects
	Set(SIZE_OBJECTS_TOOL, "common_objects", 0);  // No modifier
	Set(SIZE_OBJECTS_TOOL, "disable_snapping", K_CTRL|K_LEFT);
	Set(SIZE_OBJECTS_TOOL, "repeat_event", K_ALT|K_LEFT);
	Set(SIZE_OBJECTS_TOOL, "time_stretch", 0);  // No modifier
	
	// Split Tool
	Set(SPLIT_TOOL, "split_repeated", K_ALT|K_LEFT);
	
	// Time Warp Tool
	Set(TIME_WARP_TOOL, "create_or_erase", K_SHIFT|K_LEFT);
	Set(TIME_WARP_TOOL, "no_correction", K_ALT|K_LEFT);
	
	// Trim Tool
	Set(TRIM_TOOL, "constraint_direction", K_CTRL|K_LEFT);
	Set(TRIM_TOOL, "trim_start", K_ALT|K_LEFT);
}

void ToolModifierMap::Set(ToolId tool, const String& action, dword keys) {
	String key = CreateKey(tool, action);
	bindings.GetAdd(key) = keys;
	WhenChanged();
}

Optional<dword> ToolModifierMap::Get(ToolId tool, const String& action) const {
	String key = CreateKey(tool, action);
	if (bindings.Find(key) >= 0) {
		return bindings.Get(key);
	}
	return Optional<dword>(); // Return null optional if not found
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
	
	for(int i = 0; i < bindings.GetCount(); i++) {
		String key = bindings.GetKey(i);
		// Parse the key "toolId:action" to extract tool and action
		int pos = key.Find(':');
		if (pos > 0) {
			String toolStr = key.Mid(0, pos);
			ToolId parsedTool = (ToolId)ScanInt(toolStr);
			if (parsedTool == tool) {
				ModifierBinding binding;
				binding.tool = parsedTool;
				binding.action = key.Mid(pos + 1);
				binding.keys = bindings[i];
				result.Add(binding);
			}
		}
	}
	
	return result;
}

String ToolModifierMap::CreateKey(ToolId tool, const String& action) const {
	return AsString((int)tool) + ":" + action;
}

}