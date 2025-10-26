# Context Gate MIDI Insert Stub

## Reference
- Inspired by: Cubase Context Gate
- Category: Context-aware note/filter gate
- Modes: Poly Mode (polyphony/chord) and Mono Mode (channel/velocity)

## Summary
Context Gate filters MIDI events based on key range, polyphony, channel, and velocity conditions. It shares the filtering kernel with Transformer presets so logical expressions feel identical across tools. Auto gate timing leverages the same `MidiTiming::GateEnvelope` as MidiCompressor and Density, while panic/learn buttons reuse global MIDI learn infrastructure.

## Core Classes
- `MidiGraph::InputCollector` — Standardised event capture.
- `MidiFilters::PolyphonyGate` — Evaluates active note counts; reused by Density (percent modes) and Transformer conditions.
- `MidiFilters::ChordRecognizer` — Recognises chord clusters; shared with Chorder and ArpacheSX learn mode.
- `MidiFilters::RangeLimiter` — Enforces key range boundaries shared with MicroTuner and NoteToCC.
- `MidiFilters::ChannelGate` — Applies channel/velocity gating (Mono Mode); reused with MidiController toggle logic.
- `MidiTiming::GateEnvelope` — Provides auto-gate timeouts also used by MidiCompressor.

## Graph Layout
Input → `InputCollector`
- Poly branch: `PolyphonyGate` (polyphony/chord gate) → `RangeLimiter`
- Mono branch: `ChannelGate` (channel/velocity) → `RangeLimiter`
Both branches converge into `GateEnvelope` for auto gate timing before output.

## Implementation Notes
- UI tabs flip between Poly/Mono branches by enabling/disabling graph nodes.
- Learn buttons hook into shared `MidiFilters::LearningSession` used by MidiController to capture ranges quickly.
- Panic resets call global `PluginSDK::MidiUtilities::AllNotesOff` to maintain consistency with MidiMonitor.

## TODO
- Implement recognition modes (Normal/Simple) via `ChordRecognizer` heuristics.
- Add snapshot visualisation for chord detection using shared piano overlay assets (same as Chorder/MicroTuner).
- Support per-channel presets stored alongside Transformer logical templates.
