# TransportUI Package

## Overview
The TransportUI package handles the transport panel UI and related controls including metronome, cycle range, and pre/post-roll controls. It integrates with the AudioCore transport system to provide a complete transport control interface.

## Key Components

### Metronome
- Controls metronome functionality
- Handles volume, sound, and enable settings

### CycleRange
- Manages cycle/loop range settings
- Controls looping behavior during playback

### PrePostRoll
- Handles pre-roll and post-roll functionality
- Allows for lead-in and lead-out time during playback/recording

### TransportWindow
- Floating top-level window with Cubase-style transport layout (always-on-top, dual close buttons, F2 toggle expected by host).
- Aggregates functional panes:
  - **UsageMetersPane** — ASIO/Disk meters with overload LEDs.
  - **RecordingModePane** — Linear/Cycle record modes and Auto Quantize toggle.
  - **LocatorPane** — Left/Right locator timing, punch toggles, pre/post-roll editors, go-to buttons.
  - **TimeDisplayPane** — Primary/secondary time fields, format swapper, nudge controls, progress slider.
  - **TransportButtonPane** — Marker nav, rewind/ff, cycle, stop, play, record.
  - **TempoSyncPane** — Metronome, precount, tempo/signature, tempo track toggle, external sync.
  - **MarkerQuickPane** — Marker list button plus 1–15 jump buttons with Alt-assign behaviour.
  - **ActivityMetersPane** — MIDI and audio activity bars with clip LEDs.
  - **MasterOutputPane** — Compact vertical slider with press-and-hold expanded slider.
  - **VirtualKeyboardPane** — Host for Alt+K QWERTY keys and Shift+Tab piano view.
- Provides setter APIs for presenters (`SetUsageMeters`, `SetRecordingModes`, `SetLocators`, `SetPrimaryTime`, `SetTransportState`, `SetTempoState`, `SetMarkers`, `SetActivity`, `SetMasterGain`, `ToggleVirtualKeyboard`).

## Relations to Other Packages
- `CtrlLib`: UI controls and framework for transport panel
- `AudioCore`: Integration with the core transport system
- `ProjectMgmt`: Command dispatch for transport actions, marker management, and recording mode switches.
- `Preferences/KeyCommands`: Provides accelerator mappings (e.g., F2 toggle, Alt+K virtual keyboard, Ctrl-click behaviours).

## Package Classes Relations
- All components interact with the AudioCore::Transport system
- Metronome provides audio feedback during transport operations
- CycleRange controls the looping behavior of the transport
- PrePostRoll provides timing controls for precise playback/recording
- TransportWindow orchestrates the other components and acts as the visual surface exposed to `AudioMaster::MainWindow`.
