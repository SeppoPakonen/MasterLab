# MIDI Echo Insert Stub

## Reference
- Inspired by: Cubase MIDI Echo
- Category: Delay/echo generator for MIDI notes
- Shares timing tools with: Density, Quantizer, AutoLFO

## Summary
MidiEcho clones incoming notes into echo taps with controllable velocity/pitch decay. Tap scheduling uses the shared `MidiTiming::BeatAnalyzer` and `MidiTiming::PhaseAccumulator` services, while decay envelopes employ the same `MidiDynamics::VelocityCurve` as MidiCompressor. Pitch offsets integrate with MicroTuner's tuning tables for advanced detune presets.

## Core Classes
- `MidiGraph::InputCollector` — Gathers incoming events.
- `MidiTiming::BeatAnalyzer` — Resolves beat align settings (PPQ fractions) consistent with Quantizer.
- `MidiTiming::PhaseAccumulator` — Drives delay taps based on Delay/Length parameters; reused by AutoLFO.
- `MidiDelay::EchoBank` — Manages repeat count, delay offsets, and decay envelopes; will also be used by Transformer macros for delay presets.
- `MidiDynamics::VelocityCurve` — Applies velocity decay; shared with Density/MidiCompressor.
- `MidiPitch::OffsetOperator` — Handles pitch offset per tap; integrates with MicroTuner for alternate scales.

## Graph Layout
Input → `InputCollector` → `BeatAnalyzer`
→ `EchoBank` (Delay, Beat Align, Repeats)
→ `VelocityCurve` (decay) & `OffsetOperator` (pitch/length adjustments)
→ Output (merged via `MidiGraph::EventMerger`).

## Implementation Notes
- Delay and Length drop-downs reuse the shared fraction table so values align with Quantizer/Arpache inserts.
- Decay sliders map to shared parameter smoothing utilities for consistent automation feel.
- Graph metadata distinguishes velocity/pitch/length branches, aiding UI to visualise multi-lane decay.

## TODO
- Implement beat-aligned pre-delay using host position from `ProcessContext::transport`.
- Add optional CC echo path (controller delays) leveraging `MidiDelay::EchoBank`.
- Provide presets (classic dotted 1/8, ping-pong) stored compatibly with audio delay presets.
