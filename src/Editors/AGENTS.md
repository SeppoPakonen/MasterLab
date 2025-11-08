# Editors AGENTS Documentation

## Overview
The Editors package implements various editor windows for the DAW application, including Key Editor, Drum Editor, Score Editor, List Editor, and In-Place Editor. These provide different views and editing capabilities for the musical content.

## Key Classes

### ScoreEditorCtrl
- Main UI control for the Score Editor implementing notation display
- Contains toolbar, toolstrip, and filterstrip for control
- Provides notation visualization with zooming and selection capabilities
- Implements U++ Ctrl for drawing staff notation and musical elements

### ScoreEditorController
- MVP pattern controller connecting UI to data model
- Manages communication with NotationModel and CommandManager
- Handles user interactions and translates them to commands
- Coordinates with MIDI preview for real-time auditioning

### ScoreEditor
- Main Score Editor window implementation
- Integrates control and controller components
- Implements project management operations (save/load/modify)
- Connects to global systems (CommandManager, MIDI preview)

## Architecture Pattern
- Uses Model-View-Presenter (MVP) pattern for clear separation of concerns
- Follows U++ conventions for package structure and UI components
- Integrates with ProjectMgmt for command management and undo/redo
- Uses with Scores package for notation model handling
- Integrates with AudioCore for MIDI preview capabilities

## Dependencies
- ProjectMgmt: For CommandManager integration and undo/redo operations
- Scores: For NotationModel and score rendering
- AudioCore: For MIDI preview and auditioning
- FileIO: For project persistence operations
- CtrlLib: For UI components
- Core: For basic types and utilities

## Refactoring Notes
- ScoreEditor now properly connects to ProjectMgmt::CommandManager through the controller
- Uses Scores::NotationDocument for notation data management
- Implements proper controller/toolstrip layout as requested
- Connects to global services appropriately during initialization