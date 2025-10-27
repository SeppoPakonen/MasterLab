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

## Upcoming Integrations
- Register Cubase-style utility windows (`VSTConnectionsHost`, future MediaBay/Pool variants) with unique IDs for quick show/hide commands.
- Persist geometry/layout for floating windows through `Workspace::SaveState`/`LoadState`, keyed by window ID.
- Provide helper `ShowOrActivate(String id)` so command handlers can open the VST Connections window without duplicating lookup logic.
- Expose `WhenWindowRegistered` signal so subsystems (e.g., `TransportUI`, `VSTConnections`) can auto-bind accelerators after registration.

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for window management

## Package Classes Relations
- WindowRegistry provides centralized access to all windows
- Workspace manages layout configurations for the windows
