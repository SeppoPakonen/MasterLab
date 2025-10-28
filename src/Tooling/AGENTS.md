# Tooling Package

## Overview
The Tooling package handles tool modifier mappings - the system that defines how modifier keys (Ctrl, Alt, Shift) change the behavior of tools in the editors. It provides a central registry of tool → modifier mappings that editors can query to alter their behaviors on-the-fly.

## Key Components

### ToolModifierMap
- Central registry of tool modifier bindings
- Stores ToolId + action + ModKeys associations
- Provides query interface for editors to check current bindings
- Signals WhenChanged when bindings are modified

## Relations to Other Packages
- `ProjectMgmt`: Integration with command system
- `Editors`: Integration with editor tools to modify their behavior

## Package Classes Relations
- ToolModifierMap provides mappings that Editors query during user interaction
- When modifier keys are pressed, editors check ToolModifierMap to determine behavior
- Changes to mappings are broadcast via WhenChanged signal to update UI

## Upcoming Enhancements for Editors Integration
- **ToolPaletteModel**: central description of editor tools (icon id, tooltip, command id, default modifier bindings). Enables reuse across Key, Drum, and List editors.
- **ToggleGroup**: helper managing exclusive toggle sets (e.g., the 10-way Key Editor tool palette) with `SetActive(id)` / `WhenChange`.
- **ToolControllerBridge**: provides hooks so editors can register custom gesture handlers (draw lines, parabola/sine shapes) while still honouring global modifier overrides defined in the preferences UI.
