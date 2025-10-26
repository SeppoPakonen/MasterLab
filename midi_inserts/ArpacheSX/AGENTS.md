# Arpache SX MIDI Insert Stub

## Reference
- Inspired by: Steinberg Arpache SX
- Category: Advanced polyphonic arpeggiator / pattern programmer
- Relationship: Extends Arpache 5 feature set with multi-lane sequencing

## Summary
Arpache SX builds on the Arpache 5 chord capture but adds programmable step lanes, velocity layering, and polyphonic phrase recording. It reuses the shared `MidiGraph::LatchBuffer`, `MidiGraph::OrderResolver`, and `MidiGraph::ClockDividerNode` components to keep timing in lockstep with Arpache 5 and StepDesigner. Sequence mode feeds pre-authored steps via `MidiGraph::SequenceProgrammer`, while Classic mode mirrors Arpache 5 behaviour with added polyphony.

## Core Classes
- `MidiGraph::InputCollector` — Shared input normalisation for both Arpache inserts and Chorder.
- `MidiHarmony::PolyChordTracker` — Tracks voiced chords per channel and exposes them to the sequencer; reused by Chorder and Transformer chord macros.
- `MidiGraph::SequenceProgrammer` — Holds per-step pitch/velocity/rhythm lanes; shared with StepDesigner and BeatDesigner.
- `MidiGraph::PatternMemory` — Backs preset storage for Classic/Sequence modes; reused by BeatDesigner pattern lanes.
- `MidiGraph::OrderResolver` — Provides play order options identical to Arpache 5.
- `MidiDynamics::LayerAllocator` — Manages layer selection (velocity, interval, single); also used by Chorder layering and MidiModifiers range filters.
- `MidiTiming::SwingEngine` — Applies swing to tick stream; reused by Quantizer, BeatDesigner, and StepDesigner.

## Graph Layout
Input → `InputCollector` → `PolyChordTracker`
- Classic branch: `OrderResolver` → `ClockDividerNode` → `StepEmitter`
- Sequence branch: `SequenceProgrammer` (pitch/velocity/gate lanes) → `ClockDividerNode` → `StepEmitter`
Outputs merge and pass through `MidiDynamics::LayerAllocator` before final routing.

## Implementation Notes
- UI tabs (Classic / Sequence) map to enabling or bypassing the `SequenceProgrammer` node; parameters stored in shared pattern preset format with BeatDesigner.
- Sequence mode exposes up to four lanes per step (pitch, velocity, gate, controller) leveraging the same `MidiGraph::SequenceLane` data structure as StepDesigner.
- Humanisation uses `MidiModifiers::Randomizer` utilities for reproducible random offsets.

## TODO
- Define preset schema compatible with StepDesigner for copy/paste between inserts.
- Implement user-programmable play order macros via `MidiGraph::OrderResolver::CompileUserPattern`.
- Expose per-layer automation IDs for velocity/interval/single toggles.
