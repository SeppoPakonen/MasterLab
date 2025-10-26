# MIDI Monitor Insert Stub

## Reference
- Inspired by: Cubase MIDI Monitor
- Category: Diagnostic/analysis tool
- Shared systems: Uses PluginSDK analyzer taps and common event buffering

## Summary
MidiMonitor captures live MIDI events for inspection, filtering, and export. It depends heavily on shared debugging utilities so every MIDI insert can report state consistently. The event buffer feeds both UI (ArrayCtrl) and optional log exporters; buffer sizing uses the same presets as the upcoming global diagnostics tools.

## Core Classes
- `MidiGraph::InputCollector` — Captures raw events from input path.
- `MidiDebug::EventBuffer` — Ring buffer storing timestamped events; shared with global diagnostics overlays.
- `MidiDebug::FilterMask` — Toggles filtering for Notes/Controllers/Pitchbend/etc.; reused by Transformer preview panel.
- `MidiDebug::LiveSwitch` — Controls recording/live toggles; shared with Density preview capture.
- `MidiDebug::Exporter` — Writes buffer to SMF file; same exporter planned for global logging.
- `MidiVisualization::TableModel` — Provides model for ArrayCtrl display (columns: Status, Value1..3, Channel, Length, Position, Comment).

## Graph Layout
Input → `InputCollector` → `FilterMask`
→ `EventBuffer`
→ Output (pass-through) + optional analyzer tap for UI.

## Implementation Notes
- Power/Live/Playback toggles update `LiveSwitch` state; when Off the buffer pauses but pass-through continues.
- Filter row uses `FilterMask` bitset to keep logic consistent with Transformer preview filters.
- Buffer size menu (100/1000/10000 events) dynamically resizes `EventBuffer` via shared capacity helper to avoid reallocations mid-playback.

## TODO
- Implement comment formatting (note names, CC labels) using shared helper dictionaries.
- Expose export hook to global log directory via `MidiDebug::Exporter`.
- Add analyser integration to render activity graphs in Diagnostics window.
