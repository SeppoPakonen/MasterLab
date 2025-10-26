# Harmony Phrase Studio MIDI Instrument Stub

## Reference
- Inspired by: EZkeys-style songwriting assistant
- Vendor analogues: Toontrack EZkeys, Scaler 2 (phrases)

## Summary
MIDI-only instrument hosting chord-aware phrase library. Provides intelligent chord substitution, humanised voicings, and Bandmate drag-and-drop engine to analyse external MIDI/audio and suggest matching phrases. Outputs MIDI only.

## Implementation Plan
### Phrase Library & Chord Intelligence
- Category: MIDI instrument
- Audio I/O: None (MIDI in/out only)
- Processing blueprint: Phrase database tagged with harmonic context. Engine adapts phrases to chosen chord progression using voice-leading and inversion rules.
- Key features:
  - Library organised by genre/groove with per-phrase chord metadata
  - Chord wheel and progression builder with substitutions, borrowed chords, modal interchange
  - Intelligent voice-leading adjusting inner notes to stay within playable ranges
  - Humanise engine for timing, velocity, and embellishments
- Core building blocks:
  - Midi::PhraseDatabase
  - Midi::ChordAnalyzer
  - Midi::VoiceLeadingEngine
  - Midi::HumanizeProcessor
  - PluginSDK::GraphVisualization for phrase flow (library → transformer → output)
- Signal/graph flow: MIDI chord triggers → Chord analyzer → Phrase transformer → Humaniser → MIDI out
- TODO:
  - Define graph nodes for chord detection, phrase adaptation, and output ports
  - Implement progression editor UI hooks once available

### Bandmate & Drag-and-Drop Integration
- Category: AI assist / workflow
- Audio I/O: Accepts MIDI or audio clips for analysis (audio via offline spectral service)
- Processing blueprint: Bandmate view ingests reference material and recommends compatible phrases or generates new variations.
- Key features:
  - Drag-and-drop MIDI/audio to extract key, tempo, groove
  - AI suggestion ranking with suitability scores
  - Phrase morph engine blending two patterns with weight control
  - Drag-and-drop MIDI export to DAW timeline or other plugins
- Core building blocks:
  - DSP::AIRecommender (shared with BeatConstructorLab)
  - Midi::GrooveExtractor
  - Midi::PhraseMorpher
  - UI::PerformancePads / Browser integration
- TODO:
  - Share Bandmate analysis services with BeatConstructorLab via common module
  - Surface suggestion graph edges (reference clip → recommended phrase) in visualization layer
