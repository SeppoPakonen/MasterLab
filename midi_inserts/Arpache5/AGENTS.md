# Arpache 5 MIDI Insert Stub

## Reference
- Inspired by: Steinberg Arpache 5
- Category: Real-time arpeggiator
- Primary goal: Fast monophonic arpeggio generator with deterministic play-orders

## Summary
Arpache 5 converts held chords into rhythmic arpeggios aligned to the host clock. The stub shares the common `MidiGraph::ClockDividerNode` and `MidiGraph::LatchBuffer` infrastructure with the other arpeggiator-derived inserts so timing and chord capture logic stay identical across products. Length management and key-range trimming reuse the same `MidiTiming::GateEnvelope` helper that Density and ContextGate rely upon.

## Core Classes
- `MidiGraph::InputCollector` — Captures live note-on/off events and normalises them into chord sets shared with ArpacheSX.
- `MidiGraph::LatchBuffer` — Holds active chord snapshots; reused by ArpacheSX and StepDesigner when chords drive patterns.
- `MidiGraph::OrderResolver` — Implements play-order strategies (normal, invert, up/down, random, user). Shared with Transformer presets that sort notes.
- `MidiGraph::ClockDividerNode` — Emits step ticks at the configured subdivision; also used by AutoLFO, Quantizer, and StepDesigner.
- `MidiGraph::StepEmitter` — Maps step ticks to note outputs while applying length scaling.
- `MidiDynamics::VelocityCurve` — Optional per-step velocity offsets, reusing the same curve utility as MidiCompressor and Density.

## Graph Layout
Input → `InputCollector` → `LatchBuffer` → `OrderResolver` → (`ClockDividerNode` provides trigger stream) → `StepEmitter` → Output.

## Implementation Notes
- Parameter set: play order enum, step size (fractions table shared with Quantizer), note length fraction, key range (min/max notes).
- Uses `PluginSDK::GraphVisualization` to expose node ordering for UI diagrams; nodes register under the `Arpeggiator` group.
- Shares random source and humanise helpers with MidiModifiers to keep randomness deterministic across inserts.

## TODO
- Bind step-length parameter to `MidiTiming::GateEnvelope` so release tails mirror Density behaviour.
- Persist user-defined play order sequences inside shared preset storage for reuse in ArpacheSX.
- Add automation hooks for step size and length with smoothing like AutoLFO modulation depth.
