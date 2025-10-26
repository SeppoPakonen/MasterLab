# Chorder MIDI Insert Stub

## Reference
- Inspired by: Steinberg Chorder
- Category: Chord trigger & layering insert
- Integrates with: ArpacheSX poly-chord tracker and HarmonyPhraseStudio libraries

## Summary
Chorder maps single-note input to layered chord voicings drawn from preset libraries (Guitar, Jazz, Octaves, etc.). It reuses the shared `MidiHarmony::ChordPresetLibrary` and `MidiHarmony::VoicingEngine` that will also power HarmonyPhraseStudio and Transformer chord operations. Layer switching (velocity/interval/single) plugs directly into the same `MidiDynamics::LayerAllocator` used in ArpacheSX.

## Core Classes
- `MidiGraph::InputCollector` — Captures trigger notes, reused across arpeggiator inserts.
- `MidiHarmony::ChordPresetLibrary` — Stores chord templates with metadata for layers and play styles; shared with HarmonyPhraseStudio and Transformer.
- `MidiHarmony::VoicingEngine` — Generates voicings based on selected play style (simultaneous, fast up/down, random). Shares code with ArpacheSX order resolver.
- `MidiDynamics::LayerAllocator` — Handles layer selection and velocity splits consistent with ArpacheSX.
- `MidiGraph::PlayStyleScheduler` — Applies playstyle-specific timing offsets; reused by StepDesigner randomization and Arpache5 user patterns.
- `MidiVisualization::KeyboardOverlay` — Metadata for UI keyboard representation; also used by MicroTuner visualisation.

## Graph Layout
Input → `InputCollector` → `ChordPresetLibrary` → `VoicingEngine`
- Playstyle timing provided by `PlayStyleScheduler`
- Layer selection via `LayerAllocator`
Outputs merge into final MIDI note stream.

## Implementation Notes
- Preset browser reuses shared `PresetBrowserModel` with categories/tags (Guitar, Jazz, Octaves).
- Virtual keyboard overlay uses `MidiVisualization::KeyboardOverlay` enabling MicroTuner to reuse layout assets.
- Playstyle drop-down drives `PlayStyleScheduler` enumerations kept in sync with ArpacheSX sequence playback.

## TODO
- Implement preset import/export with HarmonyPhraseStudio chord packs.
- Add live learn mode to record chord into `ChordPresetLibrary` (shared with Transformer macros).
- Provide per-layer humanise depth parameters reusing MidiModifiers randomizer utilities.
