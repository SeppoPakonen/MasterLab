# Auto LFO MIDI Insert Stub

## Reference
- Inspired by: Cubase Auto LFO insert
- Category: MIDI modulation generator
- Purpose: Emit tempo-synchronised controller curves

## Summary
Auto LFO generates tempo-aware MIDI CC streams and routes them to configurable destinations. It shares the common timing infrastructure (`MidiGraph::ClockDividerNode`, `MidiTiming::SwingEngine`) with Arpache and Quantizer, ensuring modulation aligns with note processing inserts. Controller routing and density handling reuse the `MidiRouting::ControllerMatrix` pieces that also serve MidiController and TrackControl.

## Core Classes
- `MidiGenerators::LfoOscillator` — Multi-wave LFO engine with sync-able phase; reused by Density (random intensity modulation) and MidiModifiers.
- `MidiGraph::ClockDividerNode` — Provides beat-length timing triggers; shared across AutoLFO, Arpache, Quantizer.
- `MidiTiming::PhaseAccumulator` — Maintains phase per LFO instance; reused by MidiEcho for tap scheduling.
- `MidiRouting::ControllerMatrix` — Maps generated CC values to output channels/controllers; shared with MidiController and NoteToCC.
- `MidiDynamics::ValueRange` — Normalises min/max output scaling; used also by MidiCompressor velocity mapping.

## Graph Layout
Transport clock → `ClockDividerNode` → `LfoOscillator` (wave + density) → `ValueRange` scaler → `ControllerMatrix` → Output CC stream.

## Implementation Notes
- Supports three PPQ density presets (29/119/239) implemented via `MidiTiming::PhaseAccumulator::SetResolution`.
- Controller Type parameter uses `MidiRouting::ControllerLibrary` shared metadata with MidiController and TrackControl.
- Value Min/Max clamp uses same `MidiDynamics::ValueRange` as Density to keep velocity/control scaling behaviour aligned.

## TODO
- Implement waveform enumeration using shared `PluginSDK::ParameterSet::AddEnum` helper.
- Add automation smoothing for density parameter to avoid abrupt PPQ changes mid-playback.
- Optionally expose modulation as automation lane metadata for UI curve preview.
