# Micro Tuner MIDI Insert Stub

## Reference
- Inspired by: Cubase Micro Tuner
- Category: Note retuning (global per pitch class)
- Shared visuals: Keyboard overlay reused by Chorder

## Summary
MicroTuner offsets notes per pitch class across all octaves, outputting pitch-bent MIDI events or retuned note-on values depending on mode. It shares the `MidiPitch::TuningTable` with TrackControl (for micro tuning in GS/XG profiles) and NoteToCC (to display note labels). The UI slider per key uses `MidiVisualization::KeyboardOverlay`, enabling reuse across chord-focused tools.

## Core Classes
- `MidiGraph::InputCollector` — Input capture.
- `MidiPitch::TuningTable` — Stores cent offsets per pitch class; shared with TrackControl.
- `MidiPitch::NoteDetuner` — Applies tuning offsets via pitch-bend or Poly Aftertouch; also used by Transformer tuning macros.
- `MidiFilters::RangeLimiter` — Ensures only selected key range is affected; reused with ContextGate.
- `MidiVisualization::KeyboardOverlay` — Provides slider layout and note labels reused by Chorder.

## Graph Layout
Input → `InputCollector` → `RangeLimiter`
→ `NoteDetuner` (consults `TuningTable`)
→ Output (note + optional pitch bend events).

## Implementation Notes
- Sliders update `TuningTable` entries; slider values displayed via inline TransparentEdit.
- Supports global reset and preset storage (Equal, Just, Custom) using shared tuning preset repository.
- Option to output Poly Aftertouch reuses `MidiRouting::ControllerMatrix` for channel assignment.

## TODO
- Implement host automation per key using parameter array (12 parameters) with smoothing.
- Provide import/export of Scala files via shared parser utility planned for TrackControl.
- Visualise detune amount on keyboard overlay using colour gradients consistent with Chorder.
