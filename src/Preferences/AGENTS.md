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