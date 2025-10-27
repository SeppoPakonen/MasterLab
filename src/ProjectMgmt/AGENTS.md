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

## Upcoming Workflows
- **Score Editor Integration:** add `ScoreSelectionContext` so `Editors::ScoreEditorPresenter` can push/pull selections (notes, symbols, clefs) and receive callbacks when global selection changes.
- **Routing Presets:** expose `PresetRepository` with scoped namespaces (Global, Project) used by `Devices::IOMatrixService` to store VST Connections layouts.
- **Command Extensions:** register score-specific command descriptors (Insert Note, Glue Notes, Flip, Auto Layout, Create Chord Symbols) so the command bus can produce undoable operations shared by Key/Score editors.

## Relations to Other Packages
- `Core`: Basic U++ framework functionality
- `CtrlCore`, `CtrlLib`: UI controls and framework
- `Draw`: Drawing/graphics functionality
- `AudioCore`: Audio project elements that need management

## Package Classes Relations
- Commands class interfaces with UI elements to process user actions
- History class maintains the undo/redo stack using operations from various parts of the application
- Selection class manages selected items that can come from any part of the project
