# Preferences Package

## Overview
The Preferences package handles application-wide preferences and settings including key command configuration and input/output mappings. It provides the UI and backend for configuring the application behavior.

## Key Components

### KeyCommands
- Manages keyboard shortcuts and key bindings
- Allows users to customize key commands

### Mapping
- Handles input/output mappings
- Manages controller mappings

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for preferences dialogs
- `ProjectMgmt`: Integration with command system

## Package Classes Relations
- KeyCommands interface with the command system in ProjectMgmt
- Mapping provides configuration for input/output devices

## Planned Additions
- **EditorPreferences** surface storing per-editor defaults (Key/Drum/List/Score). Includes Key Editor flags: default Insert Velocity preset, color mode, visible controller lanes, Snap/Quantize defaults, and whether Auto Select Controllers is respected.
- **VelocityPresetStore** manages the shared preset list for Insert Velocity. Provides CRUD operations and persistence via `PrefStore`.
- **ToolModifierProfiles** integration so Key Editor can swap modifier behaviors per user profile.
