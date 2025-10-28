# AudioCore Package — Synth & Voice Infrastructure

## Overview
AudioCore holds the low-level voice management, modulation, and synthesis primitives that power the instrument implementations described in `INSTRUMENTS.md`. It collaborates with `MediaPool` for sample playback, `AudioFX` for insert effects, and `AudioUI` for macro surfaces.

## Voice & Modulation Management

- **`Synth::VoiceManager`** — Allocates polyphonic voices, handles mono/legato modes, MPE zoning, and voice stealing. Core APIs: `NoteOn(const MidiNote& note)`, `NoteOff(int noteId)`, `StealVoice()`, and `ForEachActiveVoice(Function<void(VoiceState&)>)`.
- **`Synth::ModMatrix`** — Synth-specific modulation matrix separate from the effect variant. Supports `RegisterSource`, `RegisterDestination`, `Connect`, and `RenderFrame()` to compute per-sample modulation contributions.
- **`Synth::EnvelopeBank`** — Collection of envelopes (ADSR + multi-segment). Offers `CreateADSR(...)`, `CreateMSEG(...)`, `Advance(int samples)`, and `GetValue(int envId)`.
- **`Synth::LFOBank`** — Multi-shape LFO generators with phase offset, fade-in, and tempo sync. Provides `SetShape`, `SyncToTempo`, and `RenderBlock`.
- **`Synth::MacroController`** — Bridges macro knobs from UI into per-voice modulation slots (shared with AudioFX).

## Oscillator & Filter Engines

- **`Synth::WavetableOsc`** — Handles wavetable lookup, morphing, and anti-aliasing. Methods include `LoadTable(const Wavetable& table)`, `SetMorph(double morph)`, and `Render(int samples)`.
- **`Synth::OscillatorVA`** — Virtual-analog oscillator stack with drift, sync, and pulse-width modulation.
- **`Synth::UnisonStack`** — Spreads multiple oscillators with detune/spread settings; integrates with `OscillatorVA` and `WavetableOsc`.
- **`Synth::FilterCascade`** — Serial/parallel multimode filters with drive stages. API: `Configure(const FilterTopology&)`, `ProcessBlock(const BufferView&)`.
- **`Synth::FormantShaper`** — Applies formant EQ curves for vocal synths or transpose compensation.
- **`Synth::ZenPartial`** — Zen-Core compatible partial (PCM or virtual analog) hosting oscillator, pitch, filter, amp, and modulation routing per partial. Exposes `ProcessPartial(VoiceState&)`.
- **`Synth::FMOperator`** — FM block used by Flow Motion / Reaktor-style instruments with `SetAlgorithm`, `SetModIndex`, `Process`.

## Articulation & Performance Integration

- `Synth::ExpressionRouter` (planned) will translate MPE, poly-aftertouch, and macro automation into per-voice modulation lanes.
- Hooks into `Automation::MotionDesigner` (from AudioFX) for scene morphing and time-based parameter sweeps.
- Coordinates with `UI::MacroSurface` (AudioUI) to expose performance macros.

## Collaboration With Other Packages

- Requests sample playback via `MediaPool::Sample::StreamEngine`.
- Sends insert send/return paths through `AudioFX::DSP::SignalBus`.
- Publishes metering taps for `AudioAnalysis` (oscilloscope, tuner, loudness per voice).
- Provides **`MidiPreview`** (planned) so editors (Key, Drum, Score) can audition notes when Acoustic Feedback or Step Input is active. Exposes `PreviewNoteOn`, `PreviewNoteOff`, and `SetPreviewChannel`. Integrates with `Devices::AudioDeviceManager` for routing and obeys VST Connections click routing updates.

## Key Editor Data Services Plan
- **`MidiPartDocument`**: cached representation of the active MIDI part containing notes, controller lanes, articulation tags, and transpose offsets. Supports `LoadPart(partId)`, `GetNotes()`, `GetControllerLane(ctrlId)`, and `GetTransposeDelta()`. Emits change notifications consumed by Key/Drum/List editors.
- **`MidiAutomation` accessors**: unify per-lane CC/velocity/aftertouch data with helper methods (`BeginLaneEdit`, `CommitLaneEdit`, `CancelLaneEdit`) so controller painting can be grouped for undo.
- **`HarmonyAnalyzer`**: lightweight chord detector returning chord names and note spellings for the toolbar HUD. Reuses existing pitch-class math from `Math::PitchClass`.
- **`IndependentLoopBridge`**: cooperates with `TransportUI::LoopCoordinator` to limit playback to the active part when the editor loop is enabled, while still streaming other tracks through the main timeline.
