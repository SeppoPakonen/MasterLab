# Quantizer MIDI Insert Stub

## Reference
- Inspired by: Cubase Quantizer (MIDI insert)
- Category: Real-time quantisation with swing and delay
- Shares timing modules with: Arpache inserts, BeatDesigner, MidiEcho

## Summary
Quantizer aligns incoming notes to a tempo grid with configurable swing, strength, and delay. Quantisation uses the shared `MidiTiming::QuantizeGrid` infrastructure that will also drive the Editors/Key view quantise command, ensuring consistent math across the application. Swing blends with the same `MidiTiming::SwingEngine` used by pattern-based inserts.

## Core Classes
- `MidiGraph::InputCollector` — Standard intake path.
- `MidiTiming::QuantizeGrid` — Computes ideal landing positions; reused by Editors and Transformer.
- `MidiTiming::SwingEngine` — Adjusts grid for swing percentages; shared widely (BeatDesigner, ArpacheSX).
- `MidiDynamics::StrengthBlender` — Blends between original and quantised positions based on Strength parameter; also used by MidiModifiers.
- `MidiTiming::DelayOperator` — Applies final delay compensation (±50 ms) just like MidiModifiers delay parameter.
- `MidiHarmony::ScaleQuantizer` — Optional note-scale clamp when running in harmonic quantise mode (shared with MidiModifiers).

## Graph Layout
Input → `InputCollector`
→ `QuantizeGrid`
→ `SwingEngine`
→ `StrengthBlender`
→ `DelayOperator`
→ `ScaleQuantizer`
→ Output.

## Implementation Notes
- Grid resolution drop-down reuses shared fraction table so it stays in sync with Arpache/AutoLFO lists.
- Realtime quantize toggle bypasses the processing chain but keeps monitoring active for UI feedback.
- Delay parameter writes to the same automation lane as MidiModifiers to avoid duplicate automation IDs.

## TODO
- Implement adaptive strength curves (exponential vs linear) using shared parameter flags.
- Add optional per-channel quantise settings stored as part of preset schema.
- Integrate with MidiMonitor to visualise pre/post timing difference for debugging.
