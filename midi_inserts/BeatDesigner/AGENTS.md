# Beat Designer MIDI Insert Stub

## Reference
- Inspired by: Steinberg Beat Designer
- Category: Drum step sequencer (MIDI only)
- Relation: Shares pattern engine with StepDesigner and ArpacheSX sequence mode

## Summary
Beat Designer provides a per-drum lane step grid (16x8) for live groove generation. It reuses the pattern sequencing infrastructure shared between StepDesigner, ArpacheSX, and Quantizer, enabling preset interchange and consistent swing/time-base handling. Instrument mapping leverages the same `MidiRouting::DrumMap` planned for future drum editors, ensuring kit changes propagate across inserts and editors.

## Core Classes
- `MidiSequencer::StepGrid` — Matrix storing active hits per instrument/step; shared with StepDesigner.
- `MidiSequencer::VelocityLane` — Per-column CC/velocity lane; reused by StepDesigner slider UI.
- `MidiSequencer::PatternMemory` — Pattern storage/preset management shared with ArpacheSX.
- `MidiTiming::SwingEngine` — Swing and groove offsets reused by Quantizer.
- `MidiRouting::DrumMap` — Maps logical instruments (Kick/Snare/etc.) to MIDI notes; also used by MidiController preset macros.
- `MidiGraph::PatternScheduler` — Emits timed note events from the grid; shared with StepDesigner.

## Graph Layout
Pattern editor (StepGrid + VelocityLane) → `PatternScheduler` → `SwingEngine` → Output. Instrument changes go through `DrumMap` before scheduling, while CC sliders route through `MidiRouting::ControllerMatrix` to emit velocity/modulation lanes.

## Implementation Notes
- Drum lane context menus reuse `MidiRouting::DrumLibrary`, allowing kit substitution consistent with Editors/Drum view.
- Per-lane CC slider uses `MidiSequencer::AutomationLane` (shared with StepDesigner) to drive dynamic colouring and value scaling.
- Pattern management exposes copy/paste/random hooks that call into `MidiSequencer::PatternOps`, enabling Transformer presets to import the same format.

## TODO
- Implement preset save/remove flow using shared `PatternMemory` serialization.
- Add support for four pattern banks with quick switch; share bank manager with StepDesigner.
- Expose velocity CC lane target configuration via shared dialog (same as StepDesigner “Setup”).
