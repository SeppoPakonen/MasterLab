# Editors Package

## Overview
The Editors package contains various MIDI and audio editing surfaces including Key Editor, Drum Editor, Score Editor, List Editor, and In-Place Editor. These provide different views and interfaces for editing musical content.

## Key Components

### KeyEditor
- Piano roll style editor for MIDI notes
- Provides time/pitch grid for precise note editing

### DrumEditor
- Drum lane focused editor
- Optimized for percussion and drum pattern editing

### ScoreEditor
- Traditional music notation editor
- Displays content in standard musical notation

### ListEditor
- List view editor for MIDI events
- Provides detailed parameter editing

### InPlaceEditor
- Context-sensitive editor for quick edits
- Small footprint editor for rapid modifications

## Score Editor Implementation Plan

### File Layout
- `ScoreEditor.h` / `ScoreEditor.cpp` will define the `ScoreEditorWindow` (TopWindow shell) while respecting the U++ include discipline (`Editors.h` remains the only header that pulls external dependencies).
- Supporting components (`ScoreEditorCtrl`, presenters, toolbars) will be declared in `ScoreEditor.h` and implemented in new `.cpp` files (`ScoreEditorCtrl.cpp`, `ScoreEditorToolbars.cpp`, `ScoreEditorPresenter.cpp`).  Inline helpers live in `.hpp` files only when templates/inline definitions make it mandatory.

### UI Composition
- **`ScoreEditorCtrl`** — `ParentCtrl` owning the full layout (stacked toolbars, info bar, splitter between Symbols pane and notation canvas). Exposes `SetDocument(const Scores::NotationDocumentRef&)`, `SetViewState(const Scores::ScoreViewState&)`, and `WhenAction(const ScoreEditorAction&)`.
- **Toolbar Strips** — Discrete controls:
  - `ScoreEditorTopBar` — groups Solo/Acoustic Feedback, visibility toggles, tool palette (exclusive buttons), Snap/Quantize fields, input mode toggles, MIDI capture toggles, color dropdown, and Auto-Scroll toggle. Uses `Tooling::ToggleGroup` for exclusive handling.
  - `ScoreEditorToolStrip` — thin strip with Insert buttons, note length palette, augmentation toggles, enharmonic shift pad, function buttons, and layer toggles.
  - `ScoreEditorFilterStrip` — filter visibility toggles, bar handles, quantize/layout flags, stems options. Exposed as `ValueMap GetFilterState()`.
- **`ScoreInfoBar`** — compact control showing Start/End/Length/Pitch/etc. Provides `UpdateFromSelection(const Scores::SelectionSnapshot&)` and edit callbacks for inline value changes.
- **`ScoreSymbolsPane`** — collapsible left pane hosting categorized symbol palettes. Supports search/filter, sections for Favorites, Scale, Clefs, etc., and `WhenInsertSymbol(const Scores::SymbolDescriptor&)`.
- **`ScoreCanvas`** — scrollable notation canvas. Initially uses placeholder draw routines from `Scores::LayoutEngine`, later upgraded to custom paint with caching. Handles hover HUD (pitch/time) and selection marquee.

### Presenter & Workflow
- **`ScoreEditorPresenter`** orchestrates data flow between UI controls and `Scores::NotationDocument`. Responsibilities:
  - Map tool selections to editor modes (`InsertNoteMode`, `CutMode`, etc.).
  - Manage quantize, snap, and length quantize settings via `Scores::QuantizeState`.
  - Dispatch commands to `ProjectMgmt::CommandBus` for undoable actions (`InsertNote`, `GlueNotes`, etc.).
  - Subscribe to `ProjectMgmt::SelectionService` for part selection updates; request `Scores::NotationFacade::LoadPart(partId)`.
- Presenter exposes `WhenRequestPlaybackPreview` to `AudioCore::MidiPreview` for Acoustic Feedback.

### Reuse & Dependencies
- Reuse `Tooling::ButtonPalette` for tool buttons.
- Use `Scores::LayoutEngine` for drawing and hit-testing infrastructure.
- Hook into `ProjectMgmt::CommandManager` to trigger global commands (Zoom, Quantize Setup, etc.).
- Integrate with `Preferences::PrefStore` for Score Editor visibility toggles (persistent state).

### Command & Accelerator Hooks
- Implement `ScoreEditor.key` to define shortcuts (Solo, Acoustic Feedback, Step Input, etc.).
- Map `Show Quantize`, `Quantize Setup`, `Auto Layout`, `Score Settings`, etc., into existing command namespace (ties into Task 78).

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for editor windows
- `Draw`: Drawing functionality for custom editor UI
- `AudioCore`: Integration with audio project elements

## Package Classes Relations
- All editors interface with MIDI and audio data from AudioCore
- Editors may communicate with each other through shared data structures
- Each editor type serves a specific workflow need for different types of content
