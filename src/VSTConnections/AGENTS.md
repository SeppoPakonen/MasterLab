# VSTConnections AGENTS Documentation

## Overview
The VSTConnections package implements a Cubase-style VST Connections window that allows users to configure audio and MIDI routing between devices, external effects, instruments, and internal tracks.

## Key Classes

### VSTConnectionsCtrl
- Main UI control implementing the multi-tab connection interface
- Contains tabs for: Inputs, Outputs, Groups/FX, External FX, External Instruments, Studio
- Each tab has its own toolbar and tree control for visualizing connections
- Implements U++ ParentCtrl for hosting the UI elements

### ConnectionTreeCtrl
- Custom TreeCtrl implementation for displaying connection hierarchies
- Supports different connection item types (inputs, outputs, groups, etc.)
- Handles visualization of routing parameters (speakers, devices, ports, delays, etc.)

### VSTConnectionsPresenter
- MVP pattern presenter that connects UI to data model
- Manages communication with IOMatrixService for routing operations
- Handles loading and applying connection configurations

### VSTConnectionsWnd
- Main window implementation with docking support
- Integrates the control, presenter, and service components
- Provides menu and toolbar for common operations

### IOMatrixService (in Devices package)
- Service layer managing the routing matrix
- Provides CRUD operations for all connection types
- Handles preset management via RoutingRepository

## Architecture Pattern
- Uses Model-View-Presenter (MVP) pattern
- Follows U++ conventions for package structure
- Integrates with Devices package for hardware routing management
- Uses Vector<<= for data copying as per U++ conventions

## Dependencies
- Devices: For IOMatrixService and hardware device management
- AudioCore: For audio system integration
- CtrlLib: For UI components
- Docking: For window management