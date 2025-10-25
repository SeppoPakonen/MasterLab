# Windowing Package

## Overview
The Windowing package handles window management including workspace layouts, window registration, and window organization. It provides the infrastructure for managing multiple windows and different workspace configurations.

## Key Components

### Workspace
- Manages different workspace layouts
- Handles saving and restoring window positions

### WindowRegistry
- Maintains registry of application windows
- Provides centralized window management

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for window management

## Package Classes Relations
- WindowRegistry provides centralized access to all windows
- Workspace manages layout configurations for the windows