# ProjectWindow Plan

## Goal
Reproduce the Cubase 5 project window experience: toolbar groupings, contextual info line, collapsible inspector, multi-row track list, and clip timeline with rulers/zoom.

## Near-Term Tasks
1. Hook `ProjectWindowHost` into `AudioMaster::MainWindow` lifecycle (open on project load, close on project unload).
2. Replace placeholder button callbacks with `ProjectMgmt::CommandManager` dispatches once CommandIDs (Task 78) are defined.
3. Connect track/instrument inspector models so panel states reflect selected tracks.
4. Populate track list with real project tracks and color swatches.
5. Attach timeline/time ruler widgets to transport state and snapping grid providers.
6. Integrate overview/minimap rendering and configurable zoom presets.

## Track List Roadmap
- Implement a presenter that resolves `ProjectMgmt::TrackRegistry` snapshots into the `ValueMap` schema consumed by `TrackListPane`.
- Add row templates for instruments, audio, MIDI, folders, FX, and group tracks (per-row colors, lane badges, automation indicators).
- Wire selection callbacks (`WhenSel`, context menus) to the command manager so tools can operate on the highlighted tracks.
- Support filtering/sorting (visibility agents, folder collapse) without rebuilding the entire control tree.

## Inspector Roadmap
- Map `ValueMap` descriptions to concrete sub-controls (switch grids, slider rows, dropdown columns) and hydrate from `ProjectMgmt::InspectorState`.
- Persist panel expand/collapse state per track type; restore when track selection changes.
- Integrate automation read/write toggles and VST device editors via lazy-loaded child controls.
- Provide signal-slot style events for parameter edits so `AudioCore::Mixer` and plugin hosts receive immediate updates.

## Work Area Roadmap
- Replace the static `StaticRect` canvas with a timeline renderer that understands clips, lanes, and edit cursors (backed by `AudioCore::Timeline` data).
- Sync ruler format and zoom with transport notifications; support smooth zooming (mousewheel + keyboard accelerators).
- Embed overview/minimap and vertical track height controls, driven by the cached work area state.
- Add draw buffers for selection ranges, locators, and comp lanes, enabling reactive updates during editing operations.

## Longer-Term Considerations
- Support detachable inspector/track list panes for multi-monitor workflows.
- Implement automation lane rendering and comp-lane track lane setup.
- Add context menu routing to `ProjectMgmt::CommandContext` for selection-sensitive actions.
- Provide theming hooks so `Theme::WorkAreaTheme` can restyle the project window (colors, gradients, iconography).
