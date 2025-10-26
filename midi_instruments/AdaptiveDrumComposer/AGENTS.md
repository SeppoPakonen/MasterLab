# Adaptive Drum Composer MIDI Instrument Stub

## Reference
- Inspired by: EZdrummer-style groove instrument
- Vendor analogues: Toontrack EZdrummer, Superior Drummer Grid Editor

## Summary
MIDI-only groove generator hosting drum loop library with style-aware adaptation. Analyses user-provided grooves (Bandmate view) and generates variations, fills, and transitions. Outputs MIDI events only.

## Implementation Plan
### Groove Library & Adaptation
- Category: MIDI instrument
- Audio I/O: None (MIDI only)
- Processing blueprint: Tagged groove database with metadata (style, feel, swing). Groove adapter matches target tempo/time signature and revoices patterns according to kit mapping.
- Key features:
  - Library browser with tap-to-find, filters, and audition
  - Velocity and timing humanisation tuned per articulation (snare, hat, kick)
  - Fill generator aware of preceding groove context
  - Drag-and-drop MIDI export per bar/phrase
- Core building blocks:
  - Midi::GrooveDatabase
  - Midi::GrooveAnalyzer
  - Midi::HumanizeProcessor
  - Midi::FillGenerator
  - PluginSDK::GraphVisualization representing groove → variation → output
- Signal/graph flow: Groove selection → Adaptation engine → Humanise/fill modules → MIDI out
- TODO:
  - Define graph nodes for groove selection, variation generator, and output ports
  - Provide mapping hooks for custom drum kits

### Bandmate Integration & Arrangement
- Category: AI assist / workflow
- Sidechain: Accepts dropped audio or MIDI for analysis
- Processing blueprint: Bandmate view analyses reference stems to suggest grooves, dynamic variations, and arrangement outlines.
- Key features:
  - Audio-to-groove analysis using onset detection and tempo extraction
  - Suggestion ranking with similarity/confidence metrics
  - Arrangement lane producing verse/chorus/bridge groove sequences
  - Export as MIDI clips or entire song structure
- Core building blocks:
  - DSP::AIRecommender
  - Midi::GrooveExtractor
  - Sequencer::ArrangementPlanner
  - UI::PerformancePads for triggering fills and transitions
- TODO:
  - Share Bandmate services with HarmonyPhraseStudio/BeatConstructorLab
  - Visualise arrangement graph (sections + transitions) in UI using PluginSDK graph metadata
