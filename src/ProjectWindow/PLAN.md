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

## Longer-Term Considerations
- Support detachable inspector/track list panes for multi-monitor workflows.
- Implement automation lane rendering and comp-lane track lane setup.
- Add context menu routing to `ProjectMgmt::CommandContext` for selection-sensitive actions.
- Provide theming hooks so `Theme::WorkAreaTheme` can restyle the project window (colors, gradients, iconography).
