# Density MIDI Insert Stub

## Reference
- Inspired by: Cubase Density
- Category: Velocity/density shaper
- Works with: MidiCompressor (dynamics) and Quantizer (timing)

## Summary
Density redistributes velocities (and optionally duplicates/removes notes) around beat emphasis targets. It reuses the same `MidiDynamics::VelocityCurve` and `MidiDynamics::GainStage` as MidiCompressor while adding probabilistic repetition via `MidiDynamics::DensityPlanner`. Beat awareness comes from `MidiTiming::BeatAnalyzer`, shared with Quantizer and MidiEcho for beat-aligned delays.

## Core Classes
- `MidiGraph::InputCollector` — Event intake.
- `MidiTiming::BeatAnalyzer` — Tags events with distance-from-beat metrics; used by Quantizer and MidiEcho.
- `MidiDynamics::DensityPlanner` — Computes keep/duplicate probabilities from density slider; reused later by StepDesigner randomisation.
- `MidiDynamics::VelocityCurve` — Applies velocity emphasis for on-beat vs off-beat notes (shared with MidiCompressor).
- `MidiRandom::DeterministicStream` — Provides seeded randomness (shared with MidiModifiers random slots).

## Graph Layout
Input → `InputCollector` → `BeatAnalyzer`
→ `DensityPlanner` (decide keep/duplicate) → `VelocityCurve` (scale velocities) → Output.

## Implementation Notes
- Density slider ranges 0–400% maps to planner probability curves stored in shared lookup tables.
- Beat analyzer uses host PPQ data via `ProcessContext::transport` to support swing interplay with Quantizer.
- Duplicate notes leverage `MidiGraph::EventMerger` to interleave with original stream while preserving ordering.

## TODO
- Expose advanced controls (beat bias, duplicate velocity falloff) via hidden panel for expert use.
- Allow density planner reuse inside Transformer via shared helper call.
- Add per-track global seed override for reproducible results across multiple instances.
