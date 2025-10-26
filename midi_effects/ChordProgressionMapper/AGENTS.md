# Chord Progression Mapper MIDI Effect Stub

## Reference
- Inspired by: Chord remapping / transposer MIDI FX
- Vendor analogues: Cthulhu, Scaler MIDI FX, Logic Pro Chord Trigger

## Summary
MIDI-only effect that maps incoming single notes or chords to user-defined progressions and voicings. Provides scale-aware transformations, humanised voicing, and graph visualisation of mapping paths.

## Implementation Plan
### Mapping Engine
- Category: MIDI effect
- Audio I/O: None (MIDI-through)
- Processing blueprint: Incoming MIDI triggers are analysed for scale degree, then remapped to target chord/voicing using preset or custom maps.
- Key features:
  - Scale detection with tonic/key locking
  - Custom progression slots with inversion and spread controls
  - Adaptive voice leading between successive chords
  - MIDI learn for quick remap
- Core building blocks:
  - Midi::ChordAnalyzer
  - Midi::ProgressionMap
  - Midi::VoiceLeadingEngine
  - PluginSDK::GraphVisualization (input → analyzer → mapper → output)
- Signal/graph flow: MIDI in → Analyzer → Mapping matrix → Humanise/voice lead → MIDI out
- TODO:
  - Allow graph to highlight active mapping path for visualization UI
  - Expose map presets via ParameterSet/PresetManager

### Performance & Modulation
- Category: workflow / macro control
- Audio I/O: None
- Processing blueprint: Macro controls modulate chord substitutions, tension levels, and alternate voicing probability. Includes strum generator for chord playback.
- Key features:
  - Macro knobs for Tension, Spread, Movement
  - Probability-based substitution engine (borrowed chords, secondary dominants)
  - Strum/delay humanisation for chord playback
  - Integration with HarmonyPhraseStudio for shared progression data
- Core building blocks:
  - DSP::MacroController
  - Midi::ChordSubstitutionEngine
  - Midi::StrumGenerator
  - DSP::RandomEventScheduler
- TODO:
  - Sync progression data between HarmonyPhraseStudio and ChordProgressionMapper modules
  - Provide API for external scripts to modify maps in real time
