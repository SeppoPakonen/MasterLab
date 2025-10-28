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

## Key Editor Implementation Plan

### File Layout
- Keep `KeyEditor.h` as the public header housing forward declarations and high-level types; implementation details live in new `.cpp` units included in the package manifest.
- Split the monolithic stub into purpose-specific files: `KeyEditorWindow.cpp`, `KeyEditorPresenter.cpp`, `KeyEditorState.cpp`, `KeyEditorToolbar.cpp`, `KeyEditorInfoBar.cpp`, `KeyEditorRuler.cpp`, `KeyEditorPianoRoll.cpp`, and `KeyEditorControllerLanes.cpp`.
- Introduce lightweight component headers (`KeyEditorToolbar.h`, `KeyEditorInfoBar.h`, `KeyEditorRuler.h`, `KeyEditorPianoRoll.h`, `KeyEditorControllerLanes.h`) that expose small UI classes without bringing in external includes (all dependencies flow through `Editors.h`).
- Add a `KeyEditor.key` accelerator manifest and list it in `Editors.upp` alongside the new sources. Ensure `AGENTS.md` appears first in the manifest per package guidelines.

### Shell & Presenter
- `KeyEditorWindow` (TopWindow shell) hosts the complete layout: toolbar stack, optional info bar, ruler, piano roll, and controller dock. Exposes `OpenWithPart(const AudioCore::MidiPartRef&)`, `AttachPresenter(KeyEditorPresenter&)`, and `SetInitialLayout(const KeyEditorLayoutState&)`.
- `KeyEditorPresenter` mediates between UI controls and project services. Responsibilities: follow `ProjectMgmt::SelectionService` for last-selected MIDI part, request editor closure when part is removed, mirror playhead via `TransportUI::PlayheadBus`, and dispatch undoable commands through `ProjectMgmt::CommandManager`.
- `KeyEditorState` persists mode toggles, snap settings, quantize values, visible controller lanes, and independent loop region. Backed by `ProjectMgmt::CommandContext` for undo and `Preferences::PrefStore` for last-used defaults.

### Toolbar & Tools
- `KeyEditorToolbar` builds the Cubase-style toolbar: Solo/Acoustic Feedback toggles, Info Bar toggle, 10-way exclusive tool palette, Auto-Scroll pair, misc toggles (Auto Select Controllers, Show Part Borders, Edit Active Part Only), Parts drop-down, Indicate Transpositions, Insert Velocity presets, Snap/Snap Type, Quantize, Length Quantize, Input Mode, Capture toggles, HUD readouts, Independent Track Loop, color picker, and chord readout.
- Tool palette leverages `Tooling::ToolModifierMap` for modifier behaviors and uses `Tooling::ToggleGroup` for mutual exclusion. Specialized drop-down tools (Line Tool, Time Warp) expose context menus described in the spec.
- Insert Velocity presets rely on `Preferences::PrefStore` for persistence and emit `WhenVelocityPresetChanged` so the presenter can update the data model.

### Info Bar
- `KeyEditorInfoBar` (optional strip) surfaces Start, End, Length, Pitch, Velocity, Channel, Release Velocity, and Articulations. Implements scrub-to-edit by translating drag deltas into `ProjectMgmt::Command` invocations (`UpdateNoteStart`, `UpdateNoteVelocity`, etc.).
- Consumes selection snapshots from `AudioCore::MidiPartDocument` to keep numeric values synchronized. Handles multi-selection editing via aggregated operations.

### Ruler & Loop Controls
- `KeyEditorRuler` renders bar/beat/time formats, part handles, loop handles, and context menu actions. Uses `Windowing::TimelineMarkers` components once available; until then, provides internal drawing helpers.
- Independent Track Loop toggle and HUD integrate with `TransportUI::LoopCoordinator` to register editor-specific loop ranges without disturbing the global project cycle.

### Piano Roll Canvas
- `KeyEditorPianoRoll` combines keyboard strip, grid, note rendering, snapping, and editing gestures. Implements object selection, draw/erase, trim, split, mute, glue, zoom, line, and time warp behaviors per tool selection.
- Renders notes using `Draw::Painter` with color providers supplied by `KeyEditorColorScheme` (computed from velocity/pitch/channel/part/grid match/sound slot mode). Hover HUD displays “Chord / Note” using `AudioCore::HarmonyAnalyzer` once available; initially stubbed with root detection from `Math::PitchClass`.
- Supports auto-scroll by subscribing to `TransportUI::PlayheadBus` and respects the “Suspend While Editing” toggle by throttling updates during drag gestures.

### Controller Lanes
- `KeyEditorControllerDock` manages a vector of `KeyEditorControllerLane` controls. Each lane supports chooser drop-down, value readouts, draw/line editing, presets, and `Organize…` dialog.
- Lanes reuse `Editors::ControllerLaneModel` (to be extracted from Drum/List editors) for consistent MIDI CC data manipulation. Presenter orchestrates lane stack persistence and ensures draw/erase events route to `AudioCore::MidiAutomation` tracks.

### Data & Integration Points
- Presenter queries `AudioCore::MidiPartRepository` for note data, controller lanes, and transpose offsets. Updates propagate through `ProjectMgmt::History` as undoable operations.
- Step Input mode drives `AudioCore::MidiPreview` (for acoustic feedback) and inserts notes via `ProjectMgmt::CommandBus::Queue(InsertNoteCommand)`. Virtual Keyboard integration is deferred to TransportUI task 106 but the presenter exposes `TriggerStepInput(MidiKey)` for when it arrives.
- Color modes and Snap/Quantize values use shared enums from `Editors::QuantizeCatalog` to stay consistent with other editors.

### Dependencies & uses()
- `Editors.upp` needs `uses Tooling, ProjectMgmt, Preferences, TransportUI` in addition to existing dependencies. Future integration with `AudioUI` (for color themes) can be added once the theme service stabilizes.
- Reuse existing `ProjectWindow::PartFollower` (planned) for multi-part selection instead of re-implementing part tracking logic.

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
