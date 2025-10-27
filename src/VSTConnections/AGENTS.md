# VSTConnections Package — Planning Dossier

## Purpose
The `VSTConnections` package will host the Cubase 5 style “VST Connections” window, modelling six routing tabs (Inputs, Outputs, Groups/FX, External FX, External Instruments, Studio).  It focuses on UI scaffolding, tab-specific presenters, and wiring hooks so existing device managers can supply port/bus data without duplicating logic.

## Planned Files (listed in `.upp`)
1. `AGENTS.md` *(this document — listed first for visibility in TheIDE)*
2. `VSTConnections.h` / `VSTConnections.cpp` — main header/implementation with top-level window + controller
3. `Tabs.h` / `Tabs.cpp` — shared tab base classes and per-tab panes
4. `ToolbarModels.h` / `ToolbarModels.cpp` — structured command descriptors for toolbar buttons/presets
5. `MatrixModels.h` / `MatrixModels.cpp` — value models describing bus matrices, routings, and latency data
6. `Presenters.h` / `Presenters.cpp` — presenter layer that binds `Devices` services to UI panes
7. `VSTConnections.key` — accelerator definitions (Expand/Collapse, Add Bus, Presets navigation)

Initial scaffolding will add empty headers with class declarations so downstream packages can include the types while implementation is staged.

## Key UI Classes

### `VSTConnectionsCtrl`
- Inherits `ParentCtrl`.
- Owns a `TabCtrl` and lazily instantiates each tab pane.
- Exposes `SetSnapshot(const Devices::IOMatrixSnapshot&)` to diff/apply routing models.
- Maintains `Callback WhenRequestAction(const VSTConnectionsAction&)` to bubble toolbar/button events to the presenter.
- Handles preset dropdown wiring and updates key accelerators (`ExpandAll`, `CollapseAll`, etc.).

### `VSTConnectionsHost`
- Inherits `TopWindow`.
- Embeds `VSTConnectionsCtrl` and adds window chrome (title, status text).
- Registers with `Windowing::WindowRegistry` under `"VSTConnections"` so the menu/command system can show/hide it.

### `VSTConnectionsTabBase`
- Abstract base for all six tabs.
- Provides `virtual void SetModel(const Devices::BusMatrixModel&)=0`.
- Exposes helpers for common toolbar button placement, column descriptors, and tree/list expansion.
- Supplies `WhenAddEntity`, `WhenPresetAction`, `WhenToggleColumn` callbacks so presenters connect logic.

### Per-tab panes (`InputsTab`, `OutputsTab`, `GroupsFxTab`, `ExternalFxTab`, `ExternalInstrumentTab`, `StudioTab`)
- Derive from `VSTConnectionsTabBase`.
- Define tab-specific column layout metadata and cell editors (combo boxes, toggles).
- For tree tabs, reuse `AudioUI::TreeGridCtrl` once available; interim fallback is `ArrayCtrl` + manual expand state.
- Own `ValueArray` caches to track hierarchical rows (`BusRow`, `ChannelRow`) so presenter can patch fields incrementally.

## Data & Presenter Layer

### `Devices::IOMatrixSnapshot`
- New struct living in `Devices` (see Devices/AGENTS update).
- Contains six `BusMatrixModel` instances representing each tab.
- Presenter queries `Devices::AudioDeviceManager`, `Devices::MidiDeviceManager`, and `Devices::RoutingRepository` to build snapshots.

### `VSTConnectionsPresenter`
- Lives in `Presenters.cpp`.
- Binds a `VSTConnectionsCtrl` to `Devices::IOMatrixService`.
- Provides `Refresh()`, `ApplyChange(const BusRouteChange&)`, `CreatePreset`, `DeletePreset`, `LoadPreset`.
- Delegates Add Bus / Add External FX / Add Instrument dialogs to `Devices` package factories (modal windows remain stubs until fleshed out).

### `BusRouteChange`
- Immutable command descriptor (target tab, bus id, column id, new value).
- Routed to `Devices::RoutingRepository::ApplyChange`.

## Integration Points
- **Windowing:** Register `VSTConnectionsHost` and expose default geometry for workspace persistence.
- **Devices:** Supply `IOMatrixService` with `FetchSnapshot()`, `EnumeratePorts()`, `CreateBus(...)`, `CreateExternalFx(...)`, etc.
- **ProjectMgmt:** Provide project-level preset store (per project + global).  Presenter requests `ProjectMgmt::PresetRepository`.
- **AudioCore:** Update transport/metronome routing when `Click` column toggles on Outputs tab.  `AudioCore::MetronomeRouter` will receive events from `Devices::RoutingRepository`.

## Implementation Phases
1. **Scaffolding:** create package files, define tab classes, host window, and presenter skeletons.
2. **Snapshot Wiring:** implement `Devices::IOMatrixSnapshot`/`BusMatrixModel` and stub `FetchSnapshot`.
3. **Editing Hooks:** handle cell edits → `BusRouteChange` commands → update snapshot + notify listeners.
4. **Dialogs & Presets:** scaffold Add dialogs using `CtrlLib::WithDropChoice` wrappers; wire preset commands to `ProjectMgmt`.
5. **External FX/Instrument Special Fields:** integrate delay compensation + MIDI device association once `Devices::LatencyCompensator` and `MidiDeviceManager` support watchers.

## Reuse & Dependencies
- Reuses `Devices::AudioDeviceManager` discovery, `Devices::MidiDeviceManager` enumeration, and `Preferences::PrefStore` for presets.
- Shares window styling with `Windowing::Workspace`.
- Tab cell editors leverage `Tooling::ToolModifiers` combos for consistent button theming.

## Outstanding Questions / Follow-ups
- Confirm where “Click” routing state lives (plan assumes `AudioCore::MetronomeRouter`).
- Determine whether Studio tab requires Control Room-specific service (likely separate `Devices::ControlRoomService`).
- Align accelerator IDs with existing command ID namespace once Task 78 completes.
