# AudioUI Package — Performance & Rack Interfaces

## Overview
AudioUI renders the interactive controls for effect racks, instrument macros, metering, and performance surfaces. It consumes descriptors from `AudioFX`, `AudioCore`, and `Devices` to create consistent user experiences across plug-ins and internal tooling.

## Macro & Rack Surfaces

- **`UI::RackView`** — Dynamic rack renderer. Accepts a rack descriptor (`RackDescriptor` struct) and instantiates module cards, macro knobs, and signal meters. Key functions: `Bind(const RackDescriptor&)`, `UpdateMeters(const MeterFrame&)`, `ToggleModule(int moduleId)`.
- **`UI::MacroSurface`** — Shared eight-macro panel providing `AssignMacro(int slot, const MacroBinding&)`, `SetValue(int slot, double value)`, and MIDI learn integration for live control.
- **`UI::SceneManager`** — Manages effect scenes (A/B, snapshots) with `StoreScene(int index)`, `RecallScene(int index)`, and `Interpolate(double morph)`; ties into `DSP::SceneMorph`.
- **`UI::XYPAD`** — XY performance pad with momentum and host automation output; exposes `SetTargetParameter(Axis axis, ParamRef ref)` and `ProcessDrag(const Point& pos)`.

## Performance Widgets

- **`UI::PerformancePads`** — Trigger grid for loop/instrument engines (Momentum Pro). Provides `SetPadLayout(int rows, int cols)`, `BindClip(int pad, ClipHandle)`, and `Trigger(int pad, TriggerMode mode)`.
- **`UI::KeySwitchPalette`** — Displays keyswitch assignments for sampled instruments, offering `BindArticulations(const Vector<Articulation>&)` and user labelling.
- **`UI::StrokeVisualizer`** — Shows slap bass stroke types (thumb/pop/etc.) with `AnimateStroke(StrokeEvent event)`.
- **`UI::PresetBrowser`** — Extensible preset list shared by StudioVerse/StudioRack, supporting search facets, cloud metadata, and `LoadSelection(const PresetId&)`.

## Metering & Monitoring

- **`UI::MeterBridge`** — Visualises loudness, true-peak, crest-factor, and surround metering data arriving from `AudioAnalysis::DSP::Analyzer`. Exposes `PushFrame(const MeterFrame&)` and handles hold/clip states.
- **`UI::StrobeDisplay`** — High-resolution tuner UI used by GTR3 Tuner; supports `SetPitchDeviation(double cents)` and glow/contrast adjustments for stage visibility.

## Integration Points

- Consumes rack descriptors emitted by `AudioFX::DSP::RackHost` and instrument macro definitions from `AudioCore::Synth::VoiceManager`.
- Publishes interaction events to automation/command layers (macro automation write, scene morph, pad triggers).
- Shares theming hooks with `Appearance` and `Theme` packages to maintain consistent styling across plug-in shells.
