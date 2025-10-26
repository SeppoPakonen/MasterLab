# Note To CC MIDI Insert Stub

## Reference
- Inspired by: Cubase Note to CC
- Category: Event converter (note velocity → controller value)
- Shared routing: Uses same controller matrix as MidiController and AutoLFO

## Summary
NoteToCC converts incoming note-on velocity values into controller events, optionally gating the original notes. It shares controller lookup and routing logic with MidiController/TrackControl to guarantee consistent CC labelling and channel assignment. Range limiting uses the same helpers as ContextGate so users can confine conversion to a pitch window.

## Core Classes
- `MidiGraph::InputCollector` — Captures note stream.
- `MidiRouting::NoteToControl` — Converts NoteOn velocity into CC values; also available as Transformer action.
- `MidiRouting::ControllerMatrix` — Routes generated CC events; shared with MidiController/AutoLFO.
- `MidiFilters::RangeLimiter` — Optional pitch gating; shared with MicroTuner and ContextGate.
- `MidiGraph::EventMerger` — Combines converted CC with original note stream (unless muted).

## Graph Layout
Input → `InputCollector`
→ `RangeLimiter`
→ `NoteToControl` (generates CC events)
→ `ControllerMatrix`
→ `EventMerger` → Output.

## Implementation Notes
- CC selection drop-down reuses `MidiRouting::ControllerLibrary` to display `CC 10 (Pan)` style names.
- Option to pass-through/not original notes uses `EventMerger` bypass toggle for quick gating.
- Deterministic seeding ensures repeated notes with identical velocity emit identical CC values for automation consistency.

## TODO
- Provide multi-note mapping (split keyboard to different CCs) aligning with MidiController row presets.
- Offer velocity scaling curves via shared `MidiDynamics::ValueRange`.
- Add visual meter for CC output to debug scaling alongside MidiMonitor.
