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

## Key Editor Support Plan
- **`MidiPartFollower` service:** listens to project selection changes, resolves the latest MIDI part, and notifies subscribed editors. Handles stacked takes vs. lane selections and emits `WhenPartRemoved` so `KeyEditorPresenter` can close when its source disappears.
- **Command IDs:** expand `Commands.h` to enumerate toolbar toggles/actions (Solo Editor, Acoustic Feedback, Show Info Bar, Auto-Scroll, Independent Track Loop, Snap toggles, Quantize Setup, Line Tool submodes, Time Warp modes, Input Mode, Capture toggles, Color Mode changes, controller lane presets). Task 78 will register these IDs and associate them with menu/shortcut bindings.
- **`EditorCommandContext`:** lightweight execution context that stores active editor state (`KeyEditorState`, `ScoreEditorState`, etc.) and injects it into undoable commands for precise redo/undo.
- **History Hooks:** extend `History::BeginGroup` helpers to batch note edits originating from scrub-to-edit, draw/erase, or controller painting so a single drag produces a single undo step.
- **Loop Coordination:** provide API for editor-specific loop requests (`RegisterScopedLoop(EditorId, LoopRegion)`, `UnregisterLoop(EditorId)`) that the transport system can honour in parallel with the global cycle flag.
- **Selection Mirror:** create `MidiSelectionSnapshot` type representing note/controller selections. `KeyEditorPresenter` uses it to update the info bar and to translate multi-selection edits back into undoable commands.

## Relations to Other Packages
- `Core`: Basic U++ framework functionality
- `CtrlCore`, `CtrlLib`: UI controls and framework
- `Draw`: Drawing/graphics functionality
- `AudioCore`: Audio project elements that need management

## Package Classes Relations
- Commands class interfaces with UI elements to process user actions
- History class maintains the undo/redo stack using operations from various parts of the application
- Selection class manages selected items that can come from any part of the project
