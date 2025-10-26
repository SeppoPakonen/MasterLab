# MIDI Compressor Insert Stub

## Reference
- Inspired by: Cubase MIDI Compressor
- Category: Dynamics processor for MIDI velocities/lengths
- Works alongside: Density (macro dynamics) and MidiModifiers (detailed transforms)

## Summary
MidiCompressor applies threshold/ratio/gain curves to note velocities and optionally shortens/lengthens notes. It shares the `MidiDynamics::VelocityCurve` and `MidiDynamics::GainStage` helpers with Density, ensuring both inserts react consistently to velocity scaling. Length processing builds on `MidiTiming::GateEnvelope`, also reused by Arpache5/ContextGate.

## Core Classes
- `MidiGraph::InputCollector` — Captures incoming notes for batch processing; reused widely.
- `MidiDynamics::VelocityCompressor` — Calculates gain reduction using threshold/ratio; shared with Density for percentage adjustments.
- `MidiDynamics::GainStage` — Applies make-up gain to velocities.
- `MidiTiming::GateEnvelope` — Adjusts note length while respecting key-off events; shared with Arpache inserts.
- `MidiAnalysis::PeakTracker` — Optional meter feed for UI; reused by MidiMonitor velocity column.

## Graph Layout
Input → `InputCollector` → `VelocityCompressor` → `GainStage` → `GateEnvelope` → Output.

## Implementation Notes
- Parameters: Threshold, Ratio, Gain reuse audio-style parameter descriptors so automation UI stays consistent across audio/MIDI processors.
- Routing map registers separate branches for note velocity and length transformations, allowing future per-channel compression.
- `VelocityCompressor` uses shared look-up tables for attack/release curves once envelope dynamics are added.

## TODO
- Add velocity histogram meter hooking into `MidiAnalysis::PeakTracker`.
- Implement optional sidechain support to react to other MIDI channels via shared `MidiRouting::ChannelRouter`.
- Provide preset templates (soft, hard, limiter) stored in global MIDI dynamics library.
