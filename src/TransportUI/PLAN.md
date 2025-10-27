# TransportUI Plan

## Objective
Recreate the Cubase 5 floating transport window complete with meters, recording modes, locator controls, dual-time displays, transport buttons, tempo/sync stack, marker shortcuts, activity meters, master output slider, and optional virtual keyboard overlay.

## Delivery Phases

### Phase 1 — UI Skeleton
1. Build `TransportWindow` shell with docking frame, dual close buttons, and always-on-top behaviour.
2. Lay out primary panes: system meters, recording mode stack, left/right locator modules, central time & button block, metronome/tempo/sync stack, marker shortcuts, activity meters, master output slider, and virtual keyboard host.
3. Expose setter APIs (`SetUsageMeters`, `SetLocatorState`, `SetTimeDisplays`, `SetTransportState`, `SetTempoState`, `SetMarkerBank`, `SetActivityLevels`, `SetMasterGain`) accepting neutral data structs/`ValueMap`s for presenter integration.

### Phase 2 — Behaviour Wiring
4. Hook button/toggle callbacks to `ProjectMgmt::CommandManager` once transport command IDs are available (Tasks 78/22).
5. Connect position slider scrubbing, tempo/signature edits, and punch/loop toggles to `AudioCore::Transport` state.
6. Integrate `Metronome`, `CycleRange`, and `PrePostRoll` helpers with the new UI nodes (shared presenters).

### Phase 3 — Advanced Features
7. Implement overload detection visuals and latching clip LEDs with reset actions.
8. Animate virtual keyboard overlays and MIDI routing (Alt+K toggle, Shift+Tab mode swap).
9. Deliver localization-ready label registry and theme hand-offs for `Theme::WorkAreaTheme`.

## Dependencies
- `AudioCore::Transport`, `AudioCore::TempoMap` for state.
- `ProjectMgmt::CommandManager` for shortcuts and actions.
- `Theme` package for colour/palette integration.
- `Preferences/KeyCommands` for accelerator bindings (F2 toggle, click modifiers).
