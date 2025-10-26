# Analog Drum Machine Instrument Stub

## Reference
- Inspired by: Classic analog drum synths with pattern sequencers
- Vendor analogues: Roland TR-808/TR-909, Elektron Analog Rytm, Arturia DrumBrute

## Summary
Analog-modelled drum synth with per-voice circuits and step sequencer. Provides performance macros, probability-based sequencing, and drag-and-drop pattern export.

## Implementation Plan
### Voice Circuits
- Category: drum synthesis
- Sidechain: External sidechain optional for accent modulation
- Processing blueprint: Dedicated circuit models for kick, snare, hats, toms, clap, etc., each with transient shaping and saturation.
- Key features:
  - Component-level modelling (bridged-T, noise generators, twin-T filters)
  - Velocity-to-decay and tone modulation
  - Voice layering with sample support for hybrid sounds
  - Macro controls for Punch, Boom, Air
- Core building blocks:
  - Synth::VoiceManager
  - Synth::AnalogDrumVoice (kick/snare/hat modules)
  - DSP::TransientDesigner
  - DSP::Saturator
  - DSP::MacroController
- Voice graph: Trigger → Voice circuit (osc/filter/noise) → Drive → Output mixer
- TODO:
  - Register per-voice parameters and map to PluginSDK graph nodes for visual UI
  - Provide factory kits referencing classic machines

### Pattern Sequencer & Performance
- Category: sequencing / performance
- Sidechain: Drag-and-drop MIDI import for pattern suggestions
- Processing blueprint: 64-step sequencer with probability, ratchets, flam, and automation lanes for per-step parameter locks.
- Key features:
  - Step probability, velocity, micro-timing, and accent lanes
  - Performance macros (Roll, Stutter, Fill) with latching
  - Bandmate input: analyze dropped MIDI to suggest kits/patterns
  - Drag-and-drop MIDI/audio export per pattern or song section
- Core building blocks:
  - Sequencer::PatternGrid
  - Sequencer::ProbabilityEngine
  - Sequencer::FillGenerator
  - UI::PerformancePads
  - PluginSDK::GraphVisualization for sequencer routing
- TODO:
  - Implement data model for parameter locks and expose via graph edges
  - Coordinate with midi_instruments for shared Bandmate analysis services
