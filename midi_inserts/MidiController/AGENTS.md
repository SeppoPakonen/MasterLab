# MIDI Controller Insert Stub

## Reference
- Inspired by: Cubase MIDI Controller
- Category: Controller routing and gating
- Shared infrastructure: Same controller metadata as AutoLFO and TrackControl

## Summary
MidiController exposes eight assignable controller rows with on/off toggles to gate or remap incoming CC data. It serves as the core controller management component reused by TrackControl (for GS/XG macro panels) and AutoLFO destination routing.

## Core Classes
- `MidiRouting::ControllerMatrix` — Central map of source/destination CC routes; shared across TrackControl, AutoLFO, NoteToCC.
- `MidiRouting::ToggleLatch` — Maintains On/Off state for each row; reused by Transformer action presets that enable/disable controllers.
- `MidiRouting::ControllerLibrary` — Provides human-readable CC names; shared data with TrackControl UI.
- `MidiGraph::InputCollector` — Captures CC events.
- `MidiGraph::EventMerger` — Merges gated CC stream back into outgoing events, reused by NoteToCC.

## Graph Layout
Input CC stream → `InputCollector` → `ToggleLatch` (per-row gating) → `ControllerMatrix` (remapping) → `EventMerger` → Output CC stream.

## Implementation Notes
- Each row stores mapping preset using shared JSON schema so TrackControl can import/export macros.
- UI toggles update `ToggleLatch` and push state into global automation IDs for control surfaces.
- Provides optional learn mode hooking into `MidiFilters::LearningSession` (shared with ContextGate).

## TODO
- Implement latch visual feedback with LED style statuses using shared UI theme assets.
- Support per-row channel override leveraging `MidiRouting::ChannelRouter`.
- Add preset templates for common controllers (expression, modulation, cutoff) shared with AutoLFO.
