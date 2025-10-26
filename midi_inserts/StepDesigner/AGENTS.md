# Step Designer MIDI Insert Stub

## Reference
- Inspired by: Cubase Step Designer
- Category: Polyphonic step sequencer with CC lanes
- Shares DNA with: BeatDesigner and ArpacheSX sequence mode

## Summary
StepDesigner offers a 12x32 grid for melodic pattern programming with per-column CC lanes and pattern banks. It reuses the same `MidiSequencer::StepGrid` core as BeatDesigner but extends it with melodic voicing, octave shifts, copy/paste, and randomisation. Controller lanes rely on `MidiSequencer::AutomationLane`, enabling reuse with BeatDesigner velocity strips and AutoLFO preview curves.

## Core Classes
- `MidiSequencer::StepGrid` — Stores note activation matrix; shared with BeatDesigner.
- `MidiSequencer::AutomationLane` — Handles per-column controller values; reused by BeatDesigner slider strips.
- `MidiSequencer::PatternMemory` — Preset management shared with ArpacheSX and BeatDesigner.
- `MidiGraph::PatternScheduler` — Emits events according to note length/time base; same scheduler as BeatDesigner.
- `MidiTiming::SwingEngine` — Provides swing offsets for timing; shared widely.
- `MidiRandom::DeterministicStream` — Underpins Random button results compatible with Density and MidiModifiers.

## Graph Layout
Pattern editor (StepGrid + AutomationLane) → `PatternScheduler`
→ `SwingEngine`
→ `MidiRouting::ControllerMatrix` (for CC lanes)
→ Output.

## Implementation Notes
- Pattern length (1–32) updates `PatternScheduler` to shorten tick loops without reallocating grid memory.
- Note length fraction uses shared fraction table with Arpache/Quantizer ensuring consistent UI values.
- Copy/Paste/Random actions call into `MidiSequencer::PatternOps`, enabling preset exchange with BeatDesigner/ArpacheSX.

## TODO
- Implement pattern bank manager with up to 200 slots and quick navigation.
- Add setup dialog for User1/User2 CC mapping using shared `MidiRouting::ControllerLibrary`.
- Provide colour-coded velocity lane visualisation shared across sequencer-style inserts.
