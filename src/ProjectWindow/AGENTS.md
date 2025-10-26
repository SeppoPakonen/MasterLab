# ProjectWindow Package

## Overview
The ProjectWindow package scaffolds the Cubase 5 style project window.  It provides a reusable control (`ProjectWindowCtrl`) that hosts the toolbar, info line, inspector, track list, and project area panes needed by the main application.  The package focuses on layout composition, state placeholders, and wiring hooks so higher-level logic (transport, editing, track management) can attach behaviour incrementally.

## Key Classes

- **ProjectToolbarPane** — ToolBar-derived frame that arranges toggle buttons, transport controls, and helper widgets exactly as described in `cubase5_main_window.md`.  Provides stub callbacks (`WhenAction`) for project activation, panel visibility, automation mode changes, transport, tool toggles, and snapping/quantize configuration.
- **ProjectInfoLinePane** — Hosts a contextual `TabCtrl` that swaps between MIDI and Audio info tables.  Columns mirror the Info Line descriptions (Name, Start, Length, Lock, Transpose, Velocity, etc.) so controllers can populate values for the currently selected clip type.
- **InspectorPane** — Accordion-style list that models track-specific inspector panels (Instrument, MIDI, Audio, FX, Group, Folder).  Each entry reserves space for button grids, sliders, dropdown selectors, and future dynamic widgets.
- **TrackListPane** — Shows track rows with a compact toolbar for bulk actions (Mute All, Edit In-Place, Track Colors).  The `ArrayCtrl` schema matches the multi-row layout (primary controls on row 1/2/3) and exposes hooks for context menus and color updates.
- **ProjectAreaPane** — Displays the ruler, project overview, zoom sliders, and clip canvas placeholders.  Delegates timeline updates and clip rendering to upcoming sequencing/arrangement subsystems via protected helper methods.
- **ProjectWindowCtrl** — Top-level container that stacks the toolbar and info line, keeps a horizontal splitter for inspector/track list/project area, and exposes service methods (`InitDefaultLayout`, `SetProjectTitle`, `SetProjectZoomState`) for the host window.
- **ProjectWindowHost** — Thin `TopWindow` shell that embeds `ProjectWindowCtrl`.  Provides modal/non-modal open helpers so `AudioMaster::MainWindow` can surface the Cubase-style project interface on demand.

## Extension Points

- **Model Binding:** Controller code can call `BindTimelineModel`, `BindTrackModel`, and `BindInspectorSource` (declared in `ProjectWindowCtrl`) to connect real project data structures once they exist.
- **Commands:** Toolbar buttons expose `WhenAction` callbacks and track list items expose `WhenBar`/`WhenLeftDouble` hooks; these will be wired to the command bus when CommandIDs (Task 78) are available.
- **Customization:** Inspector and info line panes provide `SetPanelState`, `ShowMidiColumns`, and `ShowAudioColumns` helpers to remain flexible for automation lanes, folder collapse, and alternate clip types.

## Related Packages

- `AudioMaster` — Hosts `ProjectWindowHost` inside the main application window and routes menu/command events to the project UI.
- `ProjectMgmt` — Will provide project metadata, track registries, and selection contexts that populate the info line and inspector.
- `AudioCore` — Supplies transport state, track audio attributes, and timeline metrics consumed by the project area and rulers.

## Current Status

- Layout scaffolding implemented with placeholder data and stub callbacks.
- Project, info, inspector, track list, and project area panes expose typed methods required by upcoming controllers.
- Plan captured in `PLAN.md` to incrementally wire data models, implement tool behaviours, and connect command infrastructure.
