# ProjectMgmt Package

## Overview
The ProjectMgmt package handles global command routing, undo/redo functionality, selection models, and clipboard integration. It serves as the central hub for managing user interactions and project state changes.

## Key Components

### Commands
- Manages command IDs and routing
- Provides centralized command execution
- Handles command enable/disable states and toggle states

### History
- Implements undo/redo functionality
- Maintains operation stack
- Provides history navigation

### Selection
- Handles selection models for various project elements
- Manages selected items across the application

## Relations to Other Packages
- `Core`: Basic U++ framework functionality
- `CtrlCore`, `CtrlLib`: UI controls and framework
- `Draw`: Drawing/graphics functionality
- `AudioCore`: Audio project elements that need management

## Package Classes Relations
- Commands class interfaces with UI elements to process user actions
- History class maintains the undo/redo stack using operations from various parts of the application
- Selection class manages selected items that can come from any part of the project